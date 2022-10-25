#include "vk/vkenv.h"
#include "configMgr.hpp"
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "gpuMat.h"
#include "gpuMem.h"
#include "helper.h"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "shader.h"
#include "stage.h"
#include "vk/vkHelper.h"
#include "vk/vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <stdexcept>
#include <stdint.h>
#include <string>
#include <utility>
#include <vcruntime.h>
#include <vcruntime_string.h>
#include <vector>

VkInstance gVkInstance = VK_NULL_HANDLE;

VkPhysicalDevice gVkPhysicalDevice;
VkDevice gVkDevice;

VkPhysicalDeviceFeatures gVkPhysicalDeviceFeatures;
VkPhysicalDeviceProperties gVkPhysicalDeviceProperties;

VkDebugUtilsMessengerEXT gVkDebuger;

GPUMem* gImgMemory = nullptr;
GPUMem* gVertexMemory = nullptr;
GPUMem* gIndexMemory = nullptr;
GPUMem* gUniformMemory = nullptr;
GPUMem* gFrameBufferMemory = nullptr;
GPUMem* gTransMemory = nullptr;
GPUMem* gReadMemory = nullptr;

VkCommandPool gVkCommandPool = nullptr;

uint32_t gVkGraphicsIndice = 0;

VkQueue gVkGraphicsQueue = VK_NULL_HANDLE;

GPUMat* noneRefTexture = nullptr;

cv::Mat noneRefDate;

void setupVkDebug()
{
    std::map<std::string, ConfigItem> extensionsConfig;
    readConfig(extensionsConfig, EXTENSIONS_CONFIG);

    if (!extensionsConfig.at("VK_EXT_debug_utils").Boolean())
    {
        return;
    }

    auto setup = PFN_vkCreateDebugUtilsMessengerEXT(
        vkGetInstanceProcAddr(gVkInstance, "vkCreateDebugUtilsMessengerEXT")
    );
    setup(gVkInstance, &the_DEFAULT_DEBUGER, GVKALC, &gVkDebuger);
}

void cleanupVkDebug()
{
    std::map<std::string, ConfigItem> extensionsConfig;
    readConfig(extensionsConfig, EXTENSIONS_CONFIG);

    if (!extensionsConfig.at("VK_EXT_debug_utils").Boolean())
    {
        return;
    }

    auto cleanup = PFN_vkDestroyDebugUtilsMessengerEXT(
        vkGetInstanceProcAddr(gVkInstance, "vkDestroyDebugUtilsMessengerEXT")
    );
    cleanup(gVkInstance, gVkDebuger, GVKALC);
}

void setupInstance()
{
    DEFAULT_VULKAN vulkanInfo{};

    // create default extensions config and read custom config:

    std::vector<VkExtensionProperties> extensions;
    uint32_t availableExtensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);
    extensions.resize(availableExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, extensions.data());

    std::vector<ConfigItem> extensionsConfig(availableExtensionCount);
    for (size_t i = 0; i < availableExtensionCount; ++i) 
    { 
        extensionsConfig[i] = { extensions[i].extensionName, ConfigType::Boolean, false };
    }

    makeConfig(EXTENSIONS_CONFIG, extensionsConfig);

    readConfig(extensionsConfig, EXTENSIONS_CONFIG);
    print("\033[34;47mvulkan extensions\033[0m", extensionsConfig);

    std::vector<const char*> usedExtensions;
    for (const auto& ext : extensionsConfig)
    {
        if (ext.Boolean())
        {
            usedExtensions.push_back(ext.key.c_str());
        }
    }

    vulkanInfo.enabledExtensionCount = U32(usedExtensions.size());
    vulkanInfo.ppEnabledExtensionNames = usedExtensions.data();

    // create default layers config and read custom config:

    std::vector<VkLayerProperties> layers;
    uint32_t availableLayerCount;
    vkEnumerateInstanceLayerProperties(&availableLayerCount, nullptr);
    layers.resize(availableLayerCount);
    vkEnumerateInstanceLayerProperties(&availableLayerCount, layers.data());

    std::vector<ConfigItem> layerConfig(availableLayerCount);
    for (size_t i = 0; i < availableLayerCount; ++i) 
    { 
        layerConfig[i] = { layers[i].layerName, ConfigType::Boolean, false };
    }

    makeConfig(LAYERS_CONFIG, layerConfig);

    readConfig(layerConfig, LAYERS_CONFIG);
    print("\033[34;47mvulkan layers\033[0m", layerConfig);

    std::vector<const char*> usedLayers;
    for (const auto& layer : layerConfig)
    {
        if (layer.Boolean())
        {
            usedLayers.push_back(layer.key.c_str());
        }
    }

    vulkanInfo.enabledLayerCount = U32(usedLayers.size());
    vulkanInfo.ppEnabledLayerNames = usedLayers.data();

    // create instance:

    trydo(VK_SUCCESS) = vkCreateInstance(&vulkanInfo, GVKALC, &gVkInstance);
}

void configDeviceFeatures(VkPhysicalDeviceFeatures* features)
{
    memset(features, 0, sizeof(VkPhysicalDeviceFeatures));
    if (gVkPhysicalDeviceFeatures.samplerAnisotropy)
    {
        features->samplerAnisotropy = VK_TRUE;
    }
}

void setupDevice()
{
    // choose physical device:

    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(gVkInstance, &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(gVkInstance, &deviceCount, devices.data());

    std::vector<ConfigItem> deviceConfig;
    std::map<std::string, VkPhysicalDevice> deviceSet;
    for (const auto& c : devices)
    {
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(c, &physicalDeviceProperties);
        deviceConfig.push_back({ physicalDeviceProperties.deviceName, ConfigType::String, CFG("Off") });
        deviceSet.insert({ physicalDeviceProperties.deviceName, c });

        Log("\n%s: \n    type: %d\n    API version: %d\n    driver version: %d\n",
            physicalDeviceProperties.deviceName,
            physicalDeviceProperties.deviceType,
            physicalDeviceProperties.apiVersion,
            physicalDeviceProperties.driverVersion);

        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(c, &deviceFeatures);

        int featuresCount = 0;
        int allfeaturesCount = 0;
        for (size_t i = 0; i < sizeof(deviceFeatures); i += 4)
        {
            if (*(reinterpret_cast<VkBool32*>(reinterpret_cast<char*>(&deviceFeatures) + i)) == VK_TRUE)
            {
                featuresCount += 1;
            }
            allfeaturesCount += 1;
        }

        Log("    features count: %d/%d\n", featuresCount, allfeaturesCount);
    }

    makeConfig(DEVICES_CONFIG, deviceConfig, CFG("On"));

    readConfig(deviceConfig, DEVICES_CONFIG);
    print("\033[34;45mDevice use\033[0m", deviceConfig);

    for (const auto& devConfig : deviceConfig)
    {
        if (devConfig.String() == "On" || devConfig.String() == "on")
        {
            gVkPhysicalDevice = deviceSet.at(devConfig.key);
            vkGetPhysicalDeviceFeatures(gVkPhysicalDevice, &gVkPhysicalDeviceFeatures);
            vkGetPhysicalDeviceProperties(gVkPhysicalDevice, &gVkPhysicalDeviceProperties);
            break;
        }
    }

    // ! create logical device

    VkPhysicalDeviceFeatures deviceFeatures = {};

    uint32_t queuefamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(gVkPhysicalDevice, &queuefamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queuefamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(gVkPhysicalDevice, &queuefamilyCount, queueFamilies.data());

    bool queueFound = false;
    gVkGraphicsIndice = 0;
    for (size_t i = 0; i < queueFamilies.size(); ++i)
    {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            gVkGraphicsIndice = U32(i);
            queueFound = true;
        }
    }

    if (!queueFound)
    {
        LogErr("Failed to find graphics queue.\n");
        throw std::runtime_error("graphics queue");
    }

    DEFAULT_GRAPHICS_QUEUE graphicsQueue{};
    graphicsQueue.queueCount = 1;
    graphicsQueue.queueFamilyIndex = gVkGraphicsIndice;
    float graphicsPriority = 1.0f;
    graphicsQueue.pQueuePriorities = &graphicsPriority;
    
    DEFAULT_DEVICE deviceInfo{};
    deviceInfo.pQueueCreateInfos = &graphicsQueue;
    deviceInfo.queueCreateInfoCount = 1;

    configDeviceFeatures(&deviceFeatures);

    deviceInfo.pEnabledFeatures = &deviceFeatures;

    trydo(VK_SUCCESS) = vkCreateDevice(gVkPhysicalDevice, &deviceInfo, GVKALC, &gVkDevice);

    vkGetDeviceQueue(gVkDevice, gVkGraphicsIndice, 0, &gVkGraphicsQueue);
}

void cleaupDevice()
{
    vkDestroyDevice(gVkDevice, GVKALC);
}

void createCommandPool()
{
    DEFAULT_COMMAND_POOL commandPoolInfo{};
    commandPoolInfo.queueFamilyIndex = gVkGraphicsIndice;

    trydo(VK_SUCCESS) = vkCreateCommandPool(gVkDevice, &commandPoolInfo, GVKALC, &gVkCommandPool);
}

void destoryCommandPool()
{
    vkDestroyCommandPool(gVkDevice, gVkCommandPool, GVKALC);
}

void initializeVulkan()
{
    setupInstance();
    setupVkDebug();
    setupDevice();
    createCommandPool();

    enableImageTransferBuffer();
    enableUnifromTransfer();
    enableMeshTransfer();

    defaultLinearSampler = new GSampler(SampleUV::Repeat, SamplePoint::Linear);

    // create default texture
    noneRefDate.create(512, 512, CV_8UC2);
    process<U8>(noneRefDate, [&](glm::vec2 uv) {
        glm::vec4 c0 = glm::vec4(1.0f, 0.2f, 1.0f, 1.0f);
        glm::vec4 c1 = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
        glm::vec2 xy = uv * glm::vec2(noneRefDate.cols, noneRefDate.rows) / 32.0f;
        float lerp = float((int(xy.x) % 2 ^ (int(xy.y) % 2)));
        return glm::mix(c0, c1, lerp);
    });
    noneRefTexture = new GPUMat(&noneRefDate, READ_MAT, true, USE_RAW);
    noneRefTexture->apply();
}

void cleanupVulkan()
{
    delete noneRefTexture;

    delete defaultLinearSampler;

    disableMeshTransfer();
    disableUnifromTransfer();
    disableImageTransferBuffer();

    memoryDisable(gImgMemory);
    memoryDisable(gVertexMemory);
    memoryDisable(gIndexMemory);
    memoryDisable(gUniformMemory);
    memoryDisable(gFrameBufferMemory);
    memoryDisable(gTransMemory);
    memoryDisable(gReadMemory);

    destoryCommandPool();
    cleaupDevice();
    cleanupVkDebug();
    vkDestroyInstance(gVkInstance, GVKALC);
}

VkCommandBuffer beginCommandOnce()
{
    VkCommandBuffer cmdBuf;

    DEFAULT_COMMAND_BUFFER cmdBufferInfo{};
    cmdBufferInfo.commandPool = gVkCommandPool;

    trydo(VK_SUCCESS) = vkAllocateCommandBuffers(gVkDevice, &cmdBufferInfo, &cmdBuf);

    vkBeginCommandBuffer(cmdBuf, &the_ONE_TIME_CMD);

    return cmdBuf;
}

void endCommandOnce(VkCommandBuffer cmdBuf, VkFence fence)
{
    vkEndCommandBuffer(cmdBuf);

    ONE_TIME_SUBMIT submitInfo{};
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &cmdBuf;
    
    if (fence != VK_NULL_HANDLE)
    {
        vkQueueSubmit(gVkGraphicsQueue, 1, &submitInfo, fence);
        vkWaitForFences(gVkDevice, 1, &fence, VK_TRUE, UINT64_MAX);
        vkResetFences(gVkDevice, 1, &fence);
    }
    else
    {
        vkQueueSubmit(gVkGraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(gVkGraphicsQueue);
    }

    vkFreeCommandBuffers(gVkDevice, gVkCommandPool, 1, &cmdBuf);
}
