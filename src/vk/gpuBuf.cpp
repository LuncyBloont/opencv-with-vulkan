#include "gpuBuf.h"
#include "gpuMem.h"
#include "helper.h"
#include "vkHelper.h"
#include "vkenv.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <stdexcept>

mltsg::GPUBuffer::GPUBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBufferUsageFlags transferUsage)
{
    DEFAULT_BUFFER bufInfo{};
    bufInfo.size = size;
    bufInfo.usage = usage | transferUsage;

    this->usage = usage;

    trydo(VK_SUCCESS) = vkCreateBuffer(gVkDevice, &bufInfo, MLTSG_GVKALC, &buffer);

    vkGetBufferMemoryRequirements(gVkDevice, buffer, &memoryRequirements);

    switch (usage) {
        case VK_BUFFER_USAGE_VERTEX_BUFFER_BIT:
            memory = gVertexMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, MLTSG_DEFAULT_V_MEM_SIZE,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            break;
        case VK_BUFFER_USAGE_TRANSFER_SRC_BIT:
            memory = gTransMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, MLTSG_DEFAULT_TRANS_SIZE,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
            break;
        case VK_BUFFER_USAGE_TRANSFER_DST_BIT:
            memory = gReadMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, MLTSG_DEFAULT_TRANS_SIZE,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            break;
        case VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT:
            memory = gUniformMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, MLTSG_DEFAULT_U_MEM_SIZE,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            break;
        case VK_BUFFER_USAGE_INDEX_BUFFER_BIT:
            memory = gIndexMemory.memoryAllocate(memoryRequirements, memoryRequirements.size, MLTSG_DEFAULT_I_MEM_SIZE,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            break;
        default:
            mltsg::LogErr("Unknown buffer usage...\n");
            throw std::runtime_error("buffer usage");
    }
    vkBindBufferMemory(gVkDevice, buffer, memory.area->vulkanMemory(), memory.ptr);
}

mltsg::GPUBuffer::~GPUBuffer()
{
    vkDestroyBuffer(gVkDevice, buffer, MLTSG_GVKALC);
}

void mltsg::GPUBuffer::mapMem()
{
    MLTSG_LogDB("Memory (obj %llx) will map (%d)\n", this, lockStatus);
    try 
    {
        lock.lock();
    } 
    catch (std::runtime_error err)
    {
        LogErr("mutex.lock(): %s\n", err.what());
        exit(-1);
    }
    lockStatus += 1;
    MLTSG_LogDB("Memory (obj %llx) maped (%d)\n", this, lockStatus);

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
        mltsg::LogErr("Device local memory buffer can't be maped.\n");
        lock.unlock();
        throw std::runtime_error("map device local memory");
    }
}

void mltsg::GPUBuffer::unmapMem()
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
        mltsg::LogErr("Device local memory buffer can't be unmaped.\n");
        lock.unlock();
        throw std::runtime_error("unmap device local memory");
    }
    MLTSG_LogDB("Memory (obj %llx) will unmap (%d)\n", this, lockStatus);
    lockStatus -= 1;
    lock.unlock();
    MLTSG_LogDB("Memory (obj %llx) unmaped (%d)\n", this, lockStatus);
}


