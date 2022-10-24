#pragma once

#include "vulkan/vulkan_core.h"

struct GPUBuffer
{
    VkBuffer buffer;
    VkMemoryRequirements memoryRequirements;
    VkDeviceSize memory;
    VkBufferUsageFlags usage;

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