#include "vk/gpuTrans.h"
#include "gpuMat.h"
#include "gpuMem.h"
#include "opencv2/core/mat.hpp"
#include "vkenv.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <vcruntime_string.h>

VkBuffer transferBuffer;
VkDeviceMemory transferMemory;
VkMemoryRequirements transferBufferRequirements;

void initializeMemoryTransfer()
{
    assertVkEnv;
    
    trydo(VK_SUCCESS) = vkCreateBuffer(gVkDevice, &the_TRANSFER_BUFFER, DEFAULT_ALLOCATOR, &transferBuffer);

    vkGetBufferMemoryRequirements(gVkDevice, transferBuffer, &transferBufferRequirements);

    TRANSFER_MEMORY transMemoryInfo{};
    transMemoryInfo.allocationSize = transferBufferRequirements.size;
    transMemoryInfo.memoryTypeIndex = findMemoryIndex(transMemoryInfo.memoryTypeIndex, 
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
    
    trydo(VK_SUCCESS) = vkAllocateMemory(gVkDevice, &transMemoryInfo, DEFAULT_ALLOCATOR, &transferMemory);
}
