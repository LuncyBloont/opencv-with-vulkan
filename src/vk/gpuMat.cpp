#include "vk/gpuMat.h"
#include "gpuBuf.h"
#include "gpuMem.h"
#include "helper.h"
#include "shader.h"
#include "vk/vkenv.h"
#include "vk/vkinfo.h"
#include "vulkan/vulkan_core.h"
#include "vkHelper.h"
#include <vcruntime_string.h>

GPUBuffer* imageTransferBuffer = nullptr;

GPUMat::GPUMat(cv::Mat* mat, bool readable, bool srgb) : cpuData(mat), readable(readable), srgb(srgb)
{
    assertVkEnv;

    // create image

    DEFAULT_IMAGE imgInfo{};

    imgInfo.extent.width = mat->cols;
    imgInfo.extent.height = mat->rows;

    switch (mat->channels()) {
        case 1:
            imgInfo.format = srgb ? VK_FORMAT_R8_SRGB : VK_FORMAT_R8_UNORM;
            break;
        case 2:
            imgInfo.format = srgb ? VK_FORMAT_R8G8_SRGB : VK_FORMAT_R8G8_UNORM;
            break;
        case 3:
            imgInfo.format = srgb ? VK_FORMAT_R8G8B8A8_SRGB : VK_FORMAT_R8G8B8A8_UNORM;
            break;
        case 4:
            imgInfo.format = srgb ? VK_FORMAT_R8G8B8A8_SRGB : VK_FORMAT_R8G8B8A8_UNORM;
            break;
    }

    format = imgInfo.format;

    trydo(VK_SUCCESS) = vkCreateImage(gVkDevice, &imgInfo, DEFAULT_ALLOCATOR, &image);

    // allocate memory

    vkGetImageMemoryRequirements(gVkDevice, image, &memoryRequirements);

    memoryEnable(gImgMemory, memoryRequirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, DEFAULT_T_MEM_SIZE);

    memory = gImgMemory->alloc(memoryRequirements.size);

    vkBindImageMemory(gVkDevice, image, gImgMemory->vulkanMemory(), memory);

    // image view 

    DEFAULT_IMAGE_VIEW viewInfo{};
    viewInfo.image = image;
    viewInfo.format = imgInfo.format;

    trydo(VK_SUCCESS) = vkCreateImageView(gVkDevice, &viewInfo, DEFAULT_ALLOCATOR, &view);
}

GPUMat::~GPUMat()
{
    vkDestroyImageView(gVkDevice, view, DEFAULT_ALLOCATOR);
    vkDestroyImage(gVkDevice, image, DEFAULT_ALLOCATOR);
}


typedef std::pair<VkImageLayout, VkImageLayout> ImageLayoutTransition;

void transitionImageLayout(VkImage image, VkFormat format, ImageLayoutTransition transition)
{

    VkCommandBuffer cmd = beginCommandOnce();

    IMAGE_BARRIER barrier{};
    barrier.image = image;
    barrier.oldLayout = transition.first;
    barrier.newLayout = transition.second;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;
    
    if (transition == ImageLayoutTransition{ VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_NONE;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (transition == ImageLayoutTransition{ VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (transition == ImageLayoutTransition{ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (transition == ImageLayoutTransition{ VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    }
    else
    {
        LogErr("Unsupported layout transition!\n");
        throw std::runtime_error("layout transition");
    }

    vkCmdPipelineBarrier(cmd, sourceStage, destinationStage, 
        0, 0, nullptr, 0, nullptr, 1, &barrier);

    endCommandOnce(cmd);
}

void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
{
    assert(imageTransferBuffer != nullptr);
    VkCommandBuffer cmd = beginCommandOnce();

    VkBufferImageCopy copy{};
    copy.bufferOffset = 0;
    copy.bufferImageHeight = 0;
    copy.bufferRowLength = 0;
    copy.imageExtent = { width, height, 1 };
    copy.imageOffset = { 0, 0, 0 };
    copy.imageSubresource = { 
        VK_IMAGE_ASPECT_COLOR_BIT,
        0, 0, 1
    };

    vkCmdCopyBufferToImage(cmd, buffer, image, 
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy);

    endCommandOnce(cmd);
}

void copyImageToBuffer(VkImage image, uint32_t width, uint32_t height, VkBuffer buffer)
{
    assert(imageTransferBuffer != nullptr);
    VkCommandBuffer cmd = beginCommandOnce();

    VkBufferImageCopy copy{};
    copy.bufferOffset = 0;
    copy.bufferImageHeight = 0;
    copy.bufferRowLength = 0;
    copy.imageExtent = { width, height, 1 };
    copy.imageOffset = { 0, 0, 0 };
    copy.imageSubresource = {
        VK_IMAGE_ASPECT_COLOR_BIT,
        0, 0, 1
    };

    vkCmdCopyImageToBuffer(cmd, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &copy);

    endCommandOnce(cmd);
}

void GPUMat::apply()
{
    if (readable == READ_MAT)
    {
        transitionImageLayout(image, format, { VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL });

        imageTransferBuffer->mapMem();
        memcpy(imageTransferBuffer->data, cpuData->data, cpuData->total() * cpuData->elemSize());
        imageTransferBuffer->unmapMem();

        copyBufferToImage(imageTransferBuffer->buffer, image, cpuData->cols, cpuData->rows);

        transitionImageLayout(image, format, { VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
    }
    else
    {
        transitionImageLayout(image, format, { VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL });

        copyImageToBuffer(image, cpuData->cols, cpuData->rows, imageTransferBuffer->buffer);

        imageTransferBuffer->mapMem();
        memcpy(cpuData->data, imageTransferBuffer->data, cpuData->total() * cpuData->elemSize());
        imageTransferBuffer->unmapMem();
        
        transitionImageLayout(image, format, { VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
    }
}

void enableImageTransferBuffer()
{
    imageTransferBuffer = new GPUBuffer(4096 * 4256 * 4, VK_BUFFER_USAGE_TRANSFER_DST_BIT);
}

void disableImageTransferBuffer()
{
    delete imageTransferBuffer;
}

