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

void copyMat2GPUMat(const cv::Mat& mat, GPUMat& gmat)
{
    const cv::Mat* cvmat = &mat;
    cv::Mat matfor3;
    if (mat.channels() == 3)
    {
        createMatC4(matfor3, mat);
        cvmat = &matfor3;
    }

    void* data;
    vkMapMemory(gVkDevice, transferMemory, 0, gmat.memoryRequirements.size, 0, &data);
    memcpy(data, cvmat->data, U32(cvmat->dataend - cvmat->datastart));
    vkUnmapMemory(gVkDevice, transferMemory);

    
}
