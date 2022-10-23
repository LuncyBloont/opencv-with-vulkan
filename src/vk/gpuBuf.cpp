#include "gpuBuf.h"
#include "gpuMem.h"
#include "helper.h"
#include "vkenv.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <stdexcept>

GPUBuffer::GPUBuffer(VkDeviceSize size, VkBufferUsageFlags usage)
{
    DEFAULT_BUFFER bufInfo{};
    bufInfo.size = size;
    bufInfo.usage = usage;

    this->usage = usage;

    trydo(VK_SUCCESS) = vkCreateBuffer(gVkDevice, &bufInfo, GVKALC, &buffer);

    vkGetBufferMemoryRequirements(gVkDevice, buffer, &memoryRequirements);

    switch (usage) {
        case VK_BUFFER_USAGE_VERTEX_BUFFER_BIT:
            memoryEnable(gVertexMemory, memoryRequirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, DEFAULT_V_MEM_SIZE);
            memory = gVertexMemory->alloc(memoryRequirements.size, memoryRequirements.alignment);
            vkBindBufferMemory(gVkDevice, buffer, gVertexMemory->vulkanMemory(), memory);
            break;
        case VK_BUFFER_USAGE_TRANSFER_SRC_BIT:
            memoryEnable(gTransMemory, memoryRequirements, 
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, DEFAULT_TRANS_SIZE);
            memory = gTransMemory->alloc(memoryRequirements.size, memoryRequirements.alignment);
            vkBindBufferMemory(gVkDevice, buffer, gTransMemory->vulkanMemory(), memory);
            break;
        case VK_BUFFER_USAGE_TRANSFER_DST_BIT:
            memoryEnable(gReadMemory, memoryRequirements, 
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, DEFAULT_TRANS_SIZE);
            memory = gReadMemory->alloc(memoryRequirements.size, memoryRequirements.alignment);
            vkBindBufferMemory(gVkDevice, buffer, gReadMemory->vulkanMemory(), memory);
            break;
        case VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT:
            memoryEnable(gUniformMemory, memoryRequirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, DEFAULT_U_MEM_SIZE);
            memory = gUniformMemory->alloc(memoryRequirements.size, memoryRequirements.alignment);
            vkBindBufferMemory(gVkDevice, buffer, gUniformMemory->vulkanMemory(), memory);
            break;
        case VK_BUFFER_USAGE_INDEX_BUFFER_BIT:
            memoryEnable(gIndexMemory, memoryRequirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, DEFAULT_I_MEM_SIZE);
            memory = gIndexMemory->alloc(memoryRequirements.size, memoryRequirements.alignment);
            vkBindBufferMemory(gVkDevice, buffer, gIndexMemory->vulkanMemory(), memory);
            break;
        default:
            LogErr("Unknown buffer usage...\n");
            throw std::runtime_error("buffer usage");
    }
}

GPUBuffer::~GPUBuffer()
{
    vkDestroyBuffer(gVkDevice, buffer, GVKALC);
}

void GPUBuffer::mapMem()
{
    if (usage == VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
    {
        vkMapMemory(gVkDevice, gTransMemory->vulkanMemory(), memory, memoryRequirements.size, 0, &data);
    }
    else if (usage == VK_BUFFER_USAGE_TRANSFER_DST_BIT)
    {
        vkMapMemory(gVkDevice, gReadMemory->vulkanMemory(), memory, memoryRequirements.size, 0, &data);
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
        vkUnmapMemory(gVkDevice, gTransMemory->vulkanMemory());
    }
    else if (usage == VK_BUFFER_USAGE_TRANSFER_DST_BIT)
    {
        vkUnmapMemory(gVkDevice, gReadMemory->vulkanMemory());
    }
    else 
    {
        LogErr("Device local memory buffer can't be unmaped.\n");
        throw std::runtime_error("unmap device local memory");
    }
}


