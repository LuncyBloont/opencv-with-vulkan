#ifndef CVVK_VK_GPU_MEME_H
#define CVVK_VK_GPU_MEME_H

#include "vulkan/vulkan_core.h"
#include <cstdint>
#include <set>
#include <stdint.h>
#include <vulkan/vulkan.h>
#include "vkHelper.h"

#define DEFAULT_T_MEM_SIZE (32 * 1024 * 1024 * 4 * 2)
#define DEFAULT_V_MEM_SIZE (10000 * 4 * 4 * 16 * 8 * 32)
#define DEFAULT_U_MEM_SIZE (16 * 128 * 256)
#define DEFAULT_TRANS_SIZE (8 * 4096 * 4096 * 4)
#define DEFAULT_I_MEM_SIZE (16 * 8 * 100000)

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
    VkDeviceSize alloc(VkDeviceSize size, VkDeviceSize alignment);
    bool free(VkDeviceSize ptr);
    const VkDeviceMemory& vulkanMemory() const;
    
};

inline void memoryEnable(GPUMem*& mem, const VkMemoryRequirements& requirements, VkMemoryPropertyFlags properties, VkDeviceSize size)
{
    if (mem == nullptr)
    {
        mem = new GPUMem(size, requirements, properties);
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

#endif