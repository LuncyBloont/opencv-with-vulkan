#include "gpuBuf.h"
#include "gpuMem.h"
#include "helper.h"
#include "vkenv.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <stdexcept>

GPUBuffer::GPUBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBufferUsageFlags transferUsage)
{
    DEFAULT_BUFFER bufInfo{};
    bufInfo.size = size;
    bufInfo.usage = usage | transferUsage;

    this->usage = usage;

    trydo(VK_SUCCESS) = vkCreateBuffer(gVkDevice, &bufInfo, GVKALC, &buffer);

    vkGetBufferMemoryRequirements(gVkDevice, buffer, &memoryRequirements);

    switch (usage) {
        case VK_BUFFER_USAGE_VERTEX_BUFFER_BIT:
            memory = gVertexMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, DEFAULT_V_MEM_SIZE,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            break;
        case VK_BUFFER_USAGE_TRANSFER_SRC_BIT:
            memory = gTransMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, DEFAULT_TRANS_SIZE,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
            break;
        case VK_BUFFER_USAGE_TRANSFER_DST_BIT:
            memory = gReadMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, DEFAULT_TRANS_SIZE,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            break;
        case VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT:
            memory = gUniformMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, DEFAULT_U_MEM_SIZE,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            break;
        case VK_BUFFER_USAGE_INDEX_BUFFER_BIT:
            memory = gIndexMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, DEFAULT_I_MEM_SIZE,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            break;
        default:
            LogErr("Unknown buffer usage...\n");
            throw std::runtime_error("buffer usage");
    }
    vkBindBufferMemory(gVkDevice, buffer, memory.area->vulkanMemory(), memory.ptr);
}

GPUBuffer::~GPUBuffer()
{
    vkDestroyBuffer(gVkDevice, buffer, GVKALC);
}

void GPUBuffer::mapMem()
{
    if (usage == VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
    {
        vkMapMemory(gVkDevice, memory.area->vulkanMemory(), memory.ptr, memoryRequirements.size, 0, &data);
    }
    else if (usage == VK_BUFFER_USAGE_TRANSFER_DST_BIT)
    {
        vkMapMemory(gVkDevice, memory.area->vulkanMemory(), memory.ptr, memoryRequirements.size, 0, &data);
    }
    else 
    {
        LogErr("Device local memory buffer can't be maped.\n");
        throw std::runtime_error("map device local memory");
    }
}

void GPUBuffer::unmapMem()
{
    if (usage == VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
    {
        vkUnmapMemory(gVkDevice, memory.area->vulkanMemory());
    }
    else if (usage == VK_BUFFER_USAGE_TRANSFER_DST_BIT)
    {
        vkUnmapMemory(gVkDevice, memory.area->vulkanMemory());
    }
    else 
    {
        LogErr("Device local memory buffer can't be unmaped.\n");
        throw std::runtime_error("unmap device local memory");
    }
}


