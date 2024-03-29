#include "vk/imageHelper.h"
#include "vkHelper.h"
#include "vkenv.h"
#include "vulkan/vulkan_core.h"
#include <stdint.h>
#include "vkinfo.h"

mltsg::GPUBuffer* mltsg::imageTransferBuffer = nullptr;
mltsg::GPUBuffer* mltsg::imageReadFromGPUBuffer = nullptr;

void mltsg::transitionImageLayout(VkImage image, VkFormat format, uint32_t level, mltsg::ImageLayoutTransition transition)
{

    VkCommandBuffer cmd = mltsg::beginCommandOnce();

    mltsg::IMAGE_BARRIER barrier{};
    barrier.image = image;
    barrier.oldLayout = transition.first;
    barrier.newLayout = transition.second;
    barrier.subresourceRange.baseMipLevel = level;

    VkPipelineStageFlags sourceStage;
    VkPipelineStageFlags destinationStage;
    
    if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_NONE;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_NONE;
        barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    }
    else if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_NONE;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    }
    else if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    }
    else if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        sourceStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    }
    else if (transition == mltsg::ImageLayoutTransition{ VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL })
    {
        barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        sourceStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    }
    else
    {
        std::cerr << "\033[31munsupported layout transition!\n\033[0m";
        throw std::runtime_error("layout transition");
    }

    vkCmdPipelineBarrier(cmd, sourceStage, destinationStage, 
        0, 0, nullptr, 0, nullptr, 1, &barrier);

    mltsg::endCommandOnce(cmd);
}

void mltsg::copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t mipLevel)
{
    assert(imageTransferBuffer != nullptr);
    VkCommandBuffer cmd = mltsg::beginCommandOnce();

    width = mltsg::toMipmapSize(width, mipLevel);
    height = mltsg::toMipmapSize(height, mipLevel);

    VkBufferImageCopy copy{};
    copy.bufferOffset = 0;
    copy.bufferImageHeight = 0;
    copy.bufferRowLength = 0;
    copy.imageExtent = { width, height, 1 };
    copy.imageOffset = { 0, 0, 0 };
    copy.imageSubresource = { 
        VK_IMAGE_ASPECT_COLOR_BIT,
        mipLevel, 0, 1
    };

    vkCmdCopyBufferToImage(cmd, buffer, image, 
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy);

    mltsg::endCommandOnce(cmd);
}

void mltsg::copyImageToBuffer(VkImage image, uint32_t width, uint32_t height, uint32_t mipLevel, VkBuffer buffer)
{
    assert(imageTransferBuffer != nullptr);
    VkCommandBuffer cmd = mltsg::beginCommandOnce();

    width = mltsg::toMipmapSize(width, mipLevel);
    height = mltsg::toMipmapSize(height, mipLevel);

    VkBufferImageCopy copy{};
    copy.bufferOffset = 0;
    copy.bufferImageHeight = 0;
    copy.bufferRowLength = 0;
    copy.imageExtent = { width, height, 1 };
    copy.imageOffset = { 0, 0, 0 };
    copy.imageSubresource = {
        VK_IMAGE_ASPECT_COLOR_BIT,
        mipLevel, 0, 1
    };

    vkCmdCopyImageToBuffer(cmd, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &copy);

    mltsg::endCommandOnce(cmd);
}

void mltsg::copyBufferToBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size)
{
    VkCommandBuffer cmd = mltsg::beginCommandOnce();
    
    VkBufferCopy copy{};
    copy.dstOffset = 0;
    copy.srcOffset = 0;
    copy.size = size;

    vkCmdCopyBuffer(cmd, src, dst, 1, &copy);

    mltsg::endCommandOnce(cmd);
}

void mltsg::copyImageToImage(VkImage src, VkImage dst, VkImageLayout srcLayout, VkImageLayout dstLayout, VkExtent3D size, uint32_t level)
{
    VkCommandBuffer cmd = mltsg::beginCommandOnce();
    
    VkImageCopy copy{};

    copy.srcOffset = { 0, 0, 0 };
    copy.srcSubresource = {
        VK_IMAGE_ASPECT_COLOR_BIT,
        level, 0, 1
    };
    copy.dstOffset = { 0, 0, 0 };
    copy.dstSubresource = {
        VK_IMAGE_ASPECT_COLOR_BIT,
        level, 0, 1
    };
    copy.extent = size;

    vkCmdCopyImage(cmd, src, srcLayout, dst, dstLayout, 1, &copy);

    mltsg::endCommandOnce(cmd);
}