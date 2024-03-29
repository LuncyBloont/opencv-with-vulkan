#ifndef CVVK_VK_IMAGE_HELPER_H
#define CVVK_VK_IMAGE_HELPER_H

#include "gpuBuf.h"
#include "vulkan/vulkan_core.h"
#include <cassert>

namespace mltsg 
{

extern GPUBuffer* imageTransferBuffer;
extern GPUBuffer* imageReadFromGPUBuffer;

typedef std::pair<VkImageLayout, VkImageLayout> ImageLayoutTransition;

void transitionImageLayout(VkImage image, VkFormat format, uint32_t level, ImageLayoutTransition transition);

void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t mipLevel);

void copyImageToBuffer(VkImage image, uint32_t width, uint32_t height, uint32_t mipLevel, VkBuffer buffer);

void copyBufferToBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size);

void copyImageToImage(VkImage src, VkImage dst, VkImageLayout srcLayout, VkImageLayout dstLayout, VkExtent3D size, uint32_t level);

}

#endif