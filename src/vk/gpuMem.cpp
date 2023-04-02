#include "vk/gpuMem.h"
#include "helper.h"
#include "vkHelper.h"
#include "vkenv.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <ios>
#include <iostream>
#include <stdexcept>
#include <stdint.h>

uint32_t mltsg::findMemoryIndex(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memoryProperties{};
    vkGetPhysicalDeviceMemoryProperties(mltsg::gVkPhysicalDevice, &memoryProperties);

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i)
    {
        if (((1 << i) & typeFilter) &&
            ((memoryProperties.memoryTypes[i].propertyFlags & properties) == properties))
        {
            return i;
        }
    }

    mltsg::LogErr("Couldn't find required memory index!\n");
    throw std::runtime_error("find memory index");
}

mltsg::GPUMem::MemSeg::MemSeg(VkDeviceSize start, VkDeviceSize size) : start(start), size(size) {}

bool mltsg::GPUMem::MemSeg::operator<(const GPUMem::MemSeg& other) const
{
    return start < other.start;
}


mltsg::GPUMem::GPUMem(VkDeviceSize size, const VkMemoryRequirements& requirements, VkMemoryPropertyFlags properties) :
    size(size), memoryType(requirements), properties(properties)
{
    assertVkEnv;

    DEFAULT_VKMEMORY_INFO memInfo{};
    memInfo.allocationSize = size;
    memInfo.memoryTypeIndex = findMemoryIndex(requirements.memoryTypeBits, properties);

    trydo(VK_SUCCESS) = vkAllocateMemory(gVkDevice, &memInfo, MLTSG_GVKALC, &memory);
}

mltsg::GPUMem::~GPUMem()
{
    vkFreeMemory(gVkDevice, memory, MLTSG_GVKALC);
}

bool mltsg::GPUMem::isCompatible(const VkMemoryRequirements& requirements, VkMemoryPropertyFlags properties) const
{
    return memoryType.memoryTypeBits == requirements.memoryTypeBits && 
        memoryType.alignment == requirements.alignment && 
        properties == this->properties;
}

bool mltsg::GPUMem::check() const
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

VkDeviceSize mltsg::GPUMem::alloc(VkDeviceSize size, VkDeviceSize alignment)
{
    VkDeviceSize ptr = 0;
    for (const auto& seg : used)
    {
        if (ptr + size <= seg.start) 
        {
            break;
        }
        ptr = seg.start + seg.size;
        if (ptr % alignment != 0)
        {
            ptr = (ptr / alignment + 1) * alignment;
        }
    }
    if (ptr + size > this->size)
    {
        mltsg::LogErr("Failed to alloc memory (need: %u)\n", size);
        throw std::runtime_error("alloc memory");
    }

    used.insert(MemSeg{ ptr, size });

    if (!check())
    {
        mltsg::LogErr("Memory error: broken...\n");
        throw std::runtime_error("memory broken");
    }

    return ptr;
}

bool mltsg::GPUMem::free(VkDeviceSize ptr)
{
    auto it = used.find(MemSeg{ ptr, 0 });
    if (it == used.end())
    {
        return false;
    }

    used.erase(it);

    if (!check())
    {
        mltsg::LogErr("Memory error: broken...\n");
        throw std::runtime_error("memory broken");
    }

    return true;
}

const VkDeviceMemory& mltsg::GPUMem::vulkanMemory() const
{
    return memory;
}
