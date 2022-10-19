#include "vk/gpuMat.h"
#include "gpuMem.h"
#include "shader.h"
#include "vk/vkenv.h"
#include "vk/vkinfo.h"
#include "vulkan/vulkan_core.h"
#include "vkHelper.h"


GPUMat::GPUMat(cv::Mat* mat, bool readable) : cpuData(mat), readable(readable)
{
    assertVkEnv;

    // create image

    DEFAULT_IMAGE imgInfo{};

    imgInfo.extent.width = mat->cols;
    imgInfo.extent.height = mat->rows;

    switch (mat->channels()) {
        case 1:
            imgInfo.format = VK_FORMAT_R8_SRGB;
            break;
        case 2:
            imgInfo.format = VK_FORMAT_R8G8_SRGB;
            break;
        case 3:
            imgInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
            break;
        case 4:
            imgInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
            break;
    }

    trydo(VK_SUCCESS) = vkCreateImage(gVkDevice, &imgInfo, DEFAULT_ALLOCATOR, &image);

    // allocate memory

    vkGetImageMemoryRequirements(gVkDevice, image, &memoryRequirements);

    memoryEnable(gImgMemory, memoryRequirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    memory = gImgMemory->alloc(memoryRequirements.size);

    vkBindImageMemory(gVkDevice, image, gImgMemory->vulkanMemory(), memory);

    // image view 

    DEFAULT_IMAGE_VIEW viewInfo{};
    viewInfo.image = image;
    viewInfo.format = imgInfo.format;

    trydo(VK_SUCCESS) = vkCreateImageView(gVkDevice, &viewInfo, DEFAULT_ALLOCATOR, &view);
}

GPUMat::~GPUMat()
{
    vkDestroyImageView(gVkDevice, view, DEFAULT_ALLOCATOR);
    vkDestroyImage(gVkDevice, image, DEFAULT_ALLOCATOR);
}

void GPUMat::apply()
{
    if (readable)
    {

    }
    else
    {
        
    }
}


