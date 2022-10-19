#include "vk/gpuMem.h"
#include "vkenv.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <ios>
#include <iostream>
#include <stdexcept>
#include <stdint.h>

uint32_t findMemoryIndex(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memoryProperties{};
    vkGetPhysicalDeviceMemoryProperties(gVkPhysicalDevice, &memoryProperties);

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i)
    {
        if (((1 << i) & typeFilter) &&
            ((memoryProperties.memoryTypes[i].propertyFlags & properties) == properties))
        {
            return i;
        }
    }

    std::cerr << "\033[31mCouldn't find required memory index!\n";
    throw std::runtime_error("find memory index");
}

GPUMem::MemSeg::MemSeg(VkDeviceSize start, VkDeviceSize size) : start(start), size(size) {}

bool GPUMem::MemSeg::operator<(const GPUMem::MemSeg& other) const
{
    return start < other.start;
}


GPUMem::GPUMem(VkDeviceSize size, const VkMemoryRequirements& requirements, VkMemoryPropertyFlags properties) :
    size(size), memoryType(requirements), properties(properties)
{
    assertVkEnv;

    DEFAULT_VKMEMORY_INFO memInfo{};
    memInfo.allocationSize = size;
    memInfo.memoryTypeIndex = findMemoryIndex(requirements.memoryTypeBits, properties);

    trydo(VK_SUCCESS) = vkAllocateMemory(gVkDevice, &memInfo, DEFAULT_ALLOCATOR, &memory);
}

GPUMem::~GPUMem()
{
    vkFreeMemory(gVkDevice, memory, DEFAULT_ALLOCATOR);
}

bool GPUMem::isCompatible(const VkMemoryRequirements& requirements, VkMemoryPropertyFlags properties) const
{
    return memoryType.memoryTypeBits == requirements.memoryTypeBits && 
        memoryType.alignment == requirements.alignment && 
        properties == this->properties;
}

bool GPUMem::check() const
{
    VkDeviceSize preEnd = 0;
    for (const auto& seg : used)
    {
        if (seg.size == 0 || seg.start < preEnd)
        {
            return false;
        }
        preEnd = seg.start + seg.size;
        if (preEnd > size)
        {
            return false;
        }
    }
    return true;
}

VkDeviceSize GPUMem::alloc(VkDeviceSize size)
{
    VkDeviceSize ptr = 0;
    for (const auto& seg : used)
    {
        if (ptr + size <= seg.start) 
        {
            break;
        }
        ptr = seg.start + seg.size;
    }
    if (ptr + size > this->size)
    {
        std::cerr << "Failed to alloc memory (need: " << size << ")\n";
        throw std::runtime_error("alloc memory");
    }

    used.insert(MemSeg{ ptr, size });

    if (!check())
    {
        std::cerr << "Memory error!\n";
        throw std::runtime_error("memory broken");
    }

    return ptr;
}

bool GPUMem::free(VkDeviceSize ptr)
{
    auto it = used.find(MemSeg{ ptr, 0 });
    if (it == used.end())
    {
        return false;
    }

    used.erase(it);

    if (!check())
    {
        std::cerr << "Memory error!\n";
        throw std::runtime_error("memory broken");
    }

    return true;
}

const VkDeviceMemory& GPUMem::vulkanMemory() const
{
    return memory;
}


