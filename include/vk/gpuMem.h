#pragma once

#include "gpuMem.h"
#include "vulkan/vulkan_core.h"
#include <cstdint>
#include <set>
#include <stdint.h>
#include <vulkan/vulkan.h>
#include "vkHelper.h"
#include "vkinfo.h"

#define DEFAULT_MEM_SIZE (16 * 1024 * 1024 * 4)

class GPUMem
{
private:
    struct MemSeg
    {
        VkDeviceSize start = 0;
        VkDeviceSize size = 0;

        explicit MemSeg(VkDeviceSize start = 0, VkDeviceSize size = 0);

        bool operator<(const MemSeg& other) const;
    };

private:
    VkDeviceMemory memory;
    std::set<MemSeg> used;
    VkDeviceSize size;
    VkMemoryRequirements memoryType;
    VkMemoryPropertyFlags properties;

public: 
    explicit GPUMem(VkDeviceSize size, const VkMemoryRequirements& requirements, VkMemoryPropertyFlags properties);
    virtual ~GPUMem();

    GPUMem(const GPUMem&) = delete;
    GPUMem(const GPUMem&&) = delete;
    GPUMem& operator=(const GPUMem&&) = delete;
    GPUMem& operator=(const GPUMem&) = delete;

    bool isCompatible(const VkMemoryRequirements& requirements, VkMemoryPropertyFlags properties) const;
    bool check() const;
    VkDeviceSize alloc(VkDeviceSize size);
    bool free(VkDeviceSize ptr);
    const VkDeviceMemory& vulkanMemory() const;
    
};

inline void memoryEnable(GPUMem*& mem, const VkMemoryRequirements& requirements, VkMemoryPropertyFlags properties)
{
    if (mem == nullptr)
    {
        mem = new GPUMem(DEFAULT_MEM_SIZE, requirements, properties);
    }
    
    trydo(true) = mem->isCompatible(requirements, properties);
}

inline void memoryDisable(GPUMem*& mem)
{
    if (mem != nullptr)
    {
        delete mem;
        mem = nullptr;
    }
}

uint32_t findMemoryIndex(uint32_t typeFilter, VkMemoryPropertyFlags properties);