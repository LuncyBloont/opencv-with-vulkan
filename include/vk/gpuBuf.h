#ifndef CVVK_VK_GPUBUF_H
#define CVVK_VK_GPUBUF_H

#include "gpuMem.h"
#include "vulkan/vulkan_core.h"
#include <mutex>

namespace mltsg 
{

struct GPUBuffer
{
    VkBuffer buffer;
    VkMemoryRequirements memoryRequirements;
    GPUPtr memory;
    VkBufferUsageFlags usage;
    std::mutex lock;

    void* data;

    explicit GPUBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBufferUsageFlags transferUsage = 0);
    virtual ~GPUBuffer();

    void mapMem();
    void unmapMem();

    GPUBuffer(const GPUBuffer& other) = delete;
    GPUBuffer(const GPUBuffer&& other) = delete;
    GPUBuffer& operator=(const GPUBuffer& other) = delete;
    GPUBuffer& operator=(const GPUBuffer&& other) = delete;
};

}

#endif