#include "vk/gpuMat.h"
#include "glm/fwd.hpp"
#include "gpuBuf.h"
#include "gpuMem.h"
#include "helper.h"
#include "imageHelper.h"
#include "opencv2/core/mat.hpp"
#include "shader.h"
#include "vk/vkenv.h"
#include "vk/vkinfo.h"
#include "vulkan/vulkan_core.h"
#include "vkHelper.h"
#include <stdint.h>
#include <vcruntime_string.h>
#include <vector>
#include "glslStyle.hpp"

mltsg::GSampler* mltsg::defaultLinearSampler = nullptr;

void generateMipmaps(const cv::Mat& level0, std::vector<cv::Mat>& mipmaps, uint32_t levels, bool HDR)
{
    mipmaps.clear();
    mipmaps.resize(levels - 1);
    for (uint32_t i = 1; i < levels; ++i)
    {
        mipmaps[i - 1].create(
            mltsg::toMipmapSize(level0.rows, i), 
            mltsg::toMipmapSize(level0.cols, i), 
            level0.type());
        const cv::Mat& ref = i == 1 ? level0 : mipmaps[i - 2];
        glm::vec2 offset = glm::vec2(-.5f, .5f);
        glm::vec2 sc = glm::vec2(1.f / ref.cols, 1.f / ref.rows);
        
        if (HDR)
        {
            auto shader = [&](glm::vec2 uv) {
                return (
                    mltsg::sample<float, MLTSG_HDR_MAX>(ref, uv + mltsg::_xx(offset) * sc) +
                    mltsg::sample<float, MLTSG_HDR_MAX>(ref, uv + mltsg::_xy(offset) * sc) + 
                    mltsg::sample<float, MLTSG_HDR_MAX>(ref, uv + mltsg::_yy(offset) * sc) + 
                    mltsg::sample<float, MLTSG_HDR_MAX>(ref, uv + mltsg::_yx(offset) * sc)
                ) * 0.25f;
            };
            mltsg::process<float, MLTSG_HDR_MAX>(mipmaps[i - 1], shader);
        }
        else  
        {
            auto shader = [&](glm::vec2 uv) {
                return (
                    mltsg::sample<MLTSG_U8>(ref, uv + mltsg::_xx(offset) * sc) +
                    mltsg::sample<MLTSG_U8>(ref, uv + mltsg::_xy(offset) * sc) + 
                    mltsg::sample<MLTSG_U8>(ref, uv + mltsg::_yy(offset) * sc) + 
                    mltsg::sample<MLTSG_U8>(ref, uv + mltsg::_yx(offset) * sc)
                ) * 0.25f;
            };
            mltsg::process<MLTSG_U8>(mipmaps[i - 1], shader);
        }
    }
}

mltsg::GPUMat::GPUMat(cv::Mat* mat, int readable, bool genMip , bool srgb, bool HDR) : 
    cpuData(mat), readable(readable), srgb(srgb), HDR(HDR)
{
    assertVkEnv;

    // create image

    DEFAULT_IMAGE imgInfo{};

    imgInfo.extent.width = mat->cols;
    imgInfo.extent.height = mat->rows;
    levels = genMip ? mipLevel(mat->cols, mat->rows) : 1;
    imgInfo.mipLevels = levels;

    if (!HDR)
    {
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
    }
    else
    {
        switch (mat->channels()) {
            case 1:
                imgInfo.format = VK_FORMAT_R32_SFLOAT;
                break;
            case 2:
                imgInfo.format = VK_FORMAT_R32G32_SFLOAT;
                break;
            case 3:
                imgInfo.format = VK_FORMAT_R32G32B32A32_SFLOAT;
                break;
            case 4:
                imgInfo.format = VK_FORMAT_R32G32B32A32_SFLOAT;
                break;
        }
    }

    if (readable == MLTSG_READ_MAT)
    {
        imgInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    }
    else
    {
        imgInfo.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    }

    format = imgInfo.format;

    trydo(VK_SUCCESS) = vkCreateImage(gVkDevice, &imgInfo, MLTSG_GVKALC, &image);

    // allocate memory

    vkGetImageMemoryRequirements(gVkDevice, image, &memoryRequirements);

    memory = gImgMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, MLTSG_DEFAULT_T_MEM_SIZE, 
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    vkBindImageMemory(gVkDevice, image, memory.area->vulkanMemory(), memory.ptr);

    // image view 

    DEFAULT_IMAGE_VIEW viewInfo{};
    viewInfo.image = image;
    viewInfo.format = imgInfo.format;
    viewInfo.subresourceRange.levelCount = levels;

    trydo(VK_SUCCESS) = vkCreateImageView(gVkDevice, &viewInfo, MLTSG_GVKALC, &view);

    if (readable == MLTSG_WRITE_MAT)
    {
        transitionImageLayout(image, format, 0, { VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
    }
}

mltsg::GPUMat::~GPUMat()
{
    vkDestroyImageView(gVkDevice, view, MLTSG_GVKALC);
    vkDestroyImage(gVkDevice, image, MLTSG_GVKALC);
}

typedef std::pair<VkImageLayout, VkImageLayout> ImageLayoutTransition;

void transitionImageLayout(VkImage image, VkFormat format, ImageLayoutTransition transition)
{
    VkCommandBuffer cmd = mltsg::beginCommandOnce();

    mltsg::IMAGE_BARRIER barrier{};
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
        mltsg::LogErr("Unsupported layout transition!\n");
        throw std::runtime_error("layout transition");
    }

    vkCmdPipelineBarrier(cmd, sourceStage, destinationStage, 
        0, 0, nullptr, 0, nullptr, 1, &barrier);

    mltsg::endCommandOnce(cmd);
}

uint32_t mltsg::GPUMat::width() const { return uint32_t(cpuData->cols); }
uint32_t mltsg::GPUMat::height() const { return uint32_t(cpuData->rows); }

void mltsg::GPUMat::makeValid()
{
    if (cpuData->channels() == 3)
    {
        cv::Mat tmp;
        if (!HDR)
        {
            createMatC4<MLTSG_U8>(tmp, *cpuData);
        }
        else
        {
            createMatC4<float, MLTSG_HDR_MAX>(tmp, *cpuData);
        }
        *cpuData = tmp;
    }
}

void mltsg::GPUMat::apply()
{
    makeValid();

    generateMipmaps(*cpuData, mipmaps, levels, HDR);

    if (readable == MLTSG_READ_MAT)
    {
        transitionImageLayout(image, format, 0, { VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL });

        imageTransferBuffer->mapMem();
        memcpy(imageTransferBuffer->data, cpuData->data, cpuData->total() * cpuData->elemSize());
        imageTransferBuffer->unmapMem();

        copyBufferToImage(imageTransferBuffer->buffer, image, width(), height(), 0);

        transitionImageLayout(image, format, 0, { VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });

        
        for (uint32_t i = 1; i < levels; ++i)
        {
            transitionImageLayout(image, format, i, { VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL });

            imageTransferBuffer->mapMem();
            memcpy(imageTransferBuffer->data, mipmaps[i - 1].data, mipmaps[i - 1].total() * mipmaps[i - 1].elemSize());
            imageTransferBuffer->unmapMem();

            copyBufferToImage(imageTransferBuffer->buffer, image, width(), height(), i);

            transitionImageLayout(image, format, i, { VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL });
        }
    }
    else
    {
        copyImageToBuffer(image, cpuData->cols, cpuData->rows, 0, imageReadFromGPUBuffer->buffer);

        imageReadFromGPUBuffer->mapMem();
        memcpy(cpuData->data, imageReadFromGPUBuffer->data, cpuData->total() * cpuData->elemSize());
        imageReadFromGPUBuffer->unmapMem();
        
    }
}

void mltsg::GPUMat::peek(void (*func)(GPUMat* self, void* userData), void* data)
{
    makeValid();
    if (readable == MLTSG_WRITE_MAT)
    {
        copyImageToBuffer(image, cpuData->cols, cpuData->rows, 0, imageReadFromGPUBuffer->buffer);

        imageReadFromGPUBuffer->mapMem();
        
        uint8_t* old = cpuData->data;
        cpuData->data = reinterpret_cast<uint8_t*>(imageReadFromGPUBuffer->data);
        func(this, data);
        cpuData->data = old;

        imageReadFromGPUBuffer->unmapMem();
    }
}

void mltsg::enableImageTransferBuffer()
{
    mltsg::imageTransferBuffer = new mltsg::GPUBuffer(4096 * 4256 * 4, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
    mltsg::imageReadFromGPUBuffer = new mltsg::GPUBuffer(4096 * 4256 * 4, VK_BUFFER_USAGE_TRANSFER_DST_BIT);
}

void mltsg::disableImageTransferBuffer()
{
    delete mltsg::imageTransferBuffer;
    delete mltsg::imageReadFromGPUBuffer;
}

mltsg::GSampler::GSampler(SampleUV uvType, SamplePoint filterType) : uvType(uvType), filterType(filterType)
{
    EMPTY_SAMPLER samplerInfo{};

    switch (uvType) {
        case SampleUV::Clamp:
            samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
            break;
        case SampleUV::Mirror:
            samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
            break;
        case SampleUV::Repeat:
            samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
            break;
    }
    samplerInfo.addressModeV = samplerInfo.addressModeU;
    samplerInfo.addressModeW = samplerInfo.addressModeU;

    switch (filterType) {
        case SamplePoint::Linear:
            samplerInfo.magFilter = VK_FILTER_LINEAR;
            samplerInfo.minFilter = VK_FILTER_LINEAR;
            samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
            break;
        case SamplePoint::Point:
            samplerInfo.magFilter = VK_FILTER_NEAREST;
            samplerInfo.minFilter = VK_FILTER_NEAREST;
            samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
            break;
    }

    if (gVkPhysicalDeviceFeatures.samplerAnisotropy)
    {
        samplerInfo.anisotropyEnable = VK_TRUE;
        samplerInfo.maxAnisotropy = gVkPhysicalDeviceProperties.limits.maxSamplerAnisotropy;
    }

    trydo(VK_SUCCESS) = vkCreateSampler(gVkDevice, &samplerInfo, MLTSG_GVKALC, &sampler);
}

mltsg::GSampler::~GSampler()
{
    vkDestroySampler(gVkDevice, sampler, MLTSG_GVKALC);
}

cv::Mat* mltsg::GPUMat::levelToMat(int level)
{
    assert(level >= 0 && level < (int)levels);
    return level == 0 ? cpuData : &mipmaps[level - 1];
}

const cv::Mat* mltsg::GPUMat::levelToMat(int level) const
{
    assert(level >= 0 && level < (int)levels);
    return level == 0 ? cpuData : &mipmaps[level - 1];
}
