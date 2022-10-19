#pragma once

#include "gpuMat.h"
#include "opencv2/core/mat.hpp"
#include "vkenv.h"
#include <stdint.h>

extern VkBuffer transferBuffer;
extern VkDeviceMemory transferMemory;
extern VkMemoryRequirements transferBufferRequirements;

void initializeMemoryTransfer();

template <typename Int, int32_t MAX>
void copyMat2GPUMat(const cv::Mat& mat, GPUMat& gmat)
{
    const cv::Mat* cvmat = &mat;
    cv::Mat matfor3;
    if (mat.channels() == 3)
    {
        createMatC4<Int, MAX>(matfor3, mat);
        cvmat = &matfor3;
    }

    void* data;
    vkMapMemory(gVkDevice, transferMemory, 0, gmat.memoryRequirements.size, 0, &data);
    memcpy(data, cvmat->data, U32(cvmat->dataend - cvmat->datastart));
    vkUnmapMemory(gVkDevice, transferMemory);

    
}

void copyGPUMat2Mat(GPUMat& gmat, cv::Mat& mat);