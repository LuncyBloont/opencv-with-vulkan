#pragma once

#include "gpuMem.h"
#include "vk/vkinfo.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <iostream>
#include <cstdint>

#define VKINFO_DECLARE(type, name, ...) \
    const static struct name : type { name() { __VA_ARGS__ } } the_##name

#define DEFAULT_ALLOCATOR nullptr

#define ECHO_VULKAN_VERBOSE false

typedef std::uint32_t uint32_t;

VKINFO_DECLARE(VkApplicationInfo, DEFAULT_APPINFO, 
    this->applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    this->apiVersion = VK_API_VERSION_1_0;
    this->engineVersion = 0;
    this->pEngineName = "";
    this->pApplicationName = "Digital Image Processing";
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
);

VKINFO_DECLARE(VkInstanceCreateInfo, DEFAULT_VULKAN,
    this->enabledExtensionCount = 0;
    this->enabledLayerCount = 0;
    this->ppEnabledExtensionNames = nullptr;
    this->ppEnabledLayerNames = nullptr;
    this->flags = 0;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    this->pApplicationInfo = &the_DEFAULT_APPINFO;
);

VKINFO_DECLARE(VkImageCreateInfo, DEFAULT_IMAGE, 
    this->sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    this->imageType = VK_IMAGE_TYPE_2D;
    this->arrayLayers = 1;
    this->extent = { 64, 64, 1 };
    this->flags = 0;
    this->initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    this->mipLevels = 1;
    this->pNext = nullptr;
    this->pQueueFamilyIndices = nullptr;
    this->queueFamilyIndexCount = 0;
    this->samples = VK_SAMPLE_COUNT_1_BIT;
    this->sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    this->tiling = VK_IMAGE_TILING_OPTIMAL;
    this->usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
);

VKINFO_DECLARE(VkImageCreateInfo, CPU_IMAGE, 
    this->sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    this->imageType = VK_IMAGE_TYPE_2D;
    this->arrayLayers = 1;
    this->extent = { 64, 64, 1 };
    this->flags = 0;
    this->initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    this->mipLevels = 1;
    this->pNext = nullptr;
    this->pQueueFamilyIndices = nullptr;
    this->queueFamilyIndexCount = 0;
    this->samples = VK_SAMPLE_COUNT_1_BIT;
    this->sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    this->tiling = VK_IMAGE_TILING_LINEAR;
    this->usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
);

VKINFO_DECLARE(VkImageViewCreateInfo, DEFAULT_IMAGE_VIEW, 
    this->image = VK_NULL_HANDLE;
    this->viewType = VK_IMAGE_VIEW_TYPE_2D;
    this->sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    this->components = { 
        VK_COMPONENT_SWIZZLE_R, 
        VK_COMPONENT_SWIZZLE_G, 
        VK_COMPONENT_SWIZZLE_B, 
        VK_COMPONENT_SWIZZLE_A 
    };
    this->pNext = nullptr;
    this->subresourceRange = {
        VK_IMAGE_ASPECT_COLOR_BIT,
        0, 1,
        0, 1
    };
    this->flags = 0;
    this->format = VK_FORMAT_R8G8B8A8_SRGB;
);

VKINFO_DECLARE(VkDebugUtilsMessengerCreateInfoEXT, DEFAULT_DEBUGER,
    this->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    this->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    this->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
    this->pUserData = nullptr;
    this->pfnUserCallback = [](VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageTypes,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {

            switch (messageSeverity) {
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                    std::cerr << "VK::: error> \033[41;30m" << pCallbackData->pMessage << "\033[0m\n";
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                    std::cerr << "VK:::  warn> \033[44;30m" << pCallbackData->pMessage << "\033[0m\n";
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                    std::cerr << "VK:::  info> \033[32m" << pCallbackData->pMessage << "\033[0m\n";
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                    if (ECHO_VULKAN_VERBOSE)
                    {
                        std::cerr << "VK:::  verb> \033[32m" << pCallbackData->pMessage << "\033[0m\n";
                    }
                    break;
                default:
                    std::cerr << "VK::: other> \033[47;30m" << pCallbackData->pMessage << "\033[0m\n";
                    break;
            }

            return VK_FALSE;
    };
);

VKINFO_DECLARE(VkDeviceQueueCreateInfo, DEFAULT_GRAPHICS_QUEUE, 
    this->pQueuePriorities = nullptr;
    this->queueCount = 0;
    this->queueFamilyIndex = 0;
    this->flags = 0;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
);

VKINFO_DECLARE(VkDeviceCreateInfo, DEFAULT_DEVICE, 
    this->pQueueCreateInfos = nullptr;
    this->queueCreateInfoCount = 0;
    this->enabledExtensionCount = 0;
    this->enabledLayerCount = 0;
    this->ppEnabledExtensionNames = nullptr;
    this->ppEnabledLayerNames = nullptr;
    this->pEnabledFeatures = nullptr;
    this->flags = 0;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
);

VKINFO_DECLARE(VkMemoryAllocateInfo, DEFAULT_VKMEMORY_INFO, 
    this->allocationSize = 0;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    this->memoryTypeIndex = 0;
);

VKINFO_DECLARE(VkBufferCreateInfo, TRANSFER_BUFFER, 
    this->sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    this->flags = 0;
    this->pNext = nullptr;
    this->pQueueFamilyIndices = nullptr;
    this->queueFamilyIndexCount = 0;
    this->sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    this->size = 4096 * 4096 * 4;
    this->usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
);

VKINFO_DECLARE(VkMemoryAllocateInfo, TRANSFER_MEMORY,
    this->allocationSize = 0;
    this->pNext = nullptr;
    this->memoryTypeIndex = 0;
    this->sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
);

VKINFO_DECLARE(VkCommandPoolCreateInfo, DEFAULT_COMMAND_POOL, 
    this->flags = 0;
    this->pNext = nullptr;
    this->queueFamilyIndex = 0;
    this->sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
);

VKINFO_DECLARE(VkCommandBufferAllocateInfo, DEFAULT_COMMAND_BUFFER, 
    this->commandBufferCount = 1;
    this->commandPool = VK_NULL_HANDLE;
    this->level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
);

VKINFO_DECLARE(VkCommandBufferBeginInfo, ONE_TIME_CMD, 
    this->pInheritanceInfo = nullptr;
    this->flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
);

VKINFO_DECLARE(VkSubmitInfo, ONE_TIME_SUBMIT, 
    this->commandBufferCount = 0;
    this->pCommandBuffers = nullptr;
    this->signalSemaphoreCount = 0;
    this->pSignalSemaphores = nullptr;
    this->waitSemaphoreCount = 0;
    this->pWaitSemaphores = nullptr;
    this->pWaitDstStageMask = nullptr;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
);

#undef VKINFO_DECLARE