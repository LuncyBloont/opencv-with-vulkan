#ifndef CVVK_VK_VKENV_H
#define CVVK_VK_VKENV_H

#include "gpuMem.h"
#include "opencv2/core/mat.hpp"
#include "vulkan/vulkan_core.h"
#include <vulkan/vulkan.h>
#include <utility>

#define EXTENSIONS_CONFIG "./vulkanExtensions.ini"
#define LAYERS_CONFIG "./vulkanLayers.ini"
#define DEVICES_CONFIG "./deviceConfig.ini"

#define REFERENCE_COUNT 3
#define TEXTURES_COUNT 3

extern VkInstance gVkInstance;

extern VkPhysicalDevice gVkPhysicalDevice;
extern VkDevice gVkDevice;

extern VkPhysicalDeviceFeatures gVkPhysicalDeviceFeatures;
extern VkPhysicalDeviceProperties gVkPhysicalDeviceProperties;

extern VkDebugUtilsMessengerEXT gVkDebuger;

class GPUMem;
struct GPUMat;

extern GPUMem* gImgMemory;
extern GPUMem* gVertexMemory;
extern GPUMem* gIndexMemory;
extern GPUMem* gUniformMemory;
extern GPUMem* gFrameBufferMemory;
extern GPUMem* gTransMemory;
extern GPUMem* gReadMemory;

extern VkCommandPool gVkCommandPool;

extern uint32_t gVkGraphicsIndice;

extern VkQueue gVkGraphicsQueue;

extern GPUMat* noneRefTexture;

extern cv::Mat noneRefDate;

#define assertVkEnv trydo(true) = (gVkInstance != VK_NULL_HANDLE)

void initializeVulkan();

void cleanupVulkan();

VkCommandBuffer beginCommandOnce();
void endCommandOnce(VkCommandBuffer cmdBuf, VkFence fence = VK_NULL_HANDLE);

#endif