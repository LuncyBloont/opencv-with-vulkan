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

VkInstance mltsg::gVkInstance = VK_NULL_HANDLE;

VkPhysicalDevice mltsg::gVkPhysicalDevice;
VkDevice mltsg::gVkDevice;

VkPhysicalDeviceFeatures mltsg::gVkPhysicalDeviceFeatures;
VkPhysicalDeviceProperties mltsg::gVkPhysicalDeviceProperties;

VkDebugUtilsMessengerEXT mltsg::gVkDebuger;

mltsg::GPUMemsArray<3> mltsg::gImgMemory("Image Memory");
mltsg::GPUMemsArray<2> mltsg::gVertexMemory("Vertex Memory");
mltsg::GPUMemsArray<2> mltsg::gIndexMemory("Index Memory");
mltsg::GPUMemsArray<2> mltsg::gUniformMemory("Uniform Memory");
mltsg::GPUMemsArray<2> mltsg::gTransMemory("Trans Memory");
mltsg::GPUMemsArray<2> mltsg::gReadMemory("Read Memory");

VkCommandPool mltsg::gVkCommandPool = nullptr;

uint32_t mltsg::gVkGraphicsIndice = 0;

VkQueue mltsg::gVkGraphicsQueue = VK_NULL_HANDLE;

mltsg::GPUMat* mltsg::noneRefTexture = nullptr;

cv::Mat mltsg::noneRefDate;

void setupVkDebug()
{
    std::map<std::string, mltsg::ConfigItem> extensionsConfig;
    readConfig(extensionsConfig, MLTSG_EXTENSIONS_CONFIG);

    if (!extensionsConfig.at("VK_EXT_debug_utils").Boolean())
    {
        return;
    }

    auto setup = PFN_vkCreateDebugUtilsMessengerEXT(
        vkGetInstanceProcAddr(mltsg::gVkInstance, "vkCreateDebugUtilsMessengerEXT")
    );
    setup(mltsg::gVkInstance, &mltsg::the_DEFAULT_DEBUGER, MLTSG_GVKALC, &mltsg::gVkDebuger);
}

void cleanupVkDebug()
{
    std::map<std::string, mltsg::ConfigItem> extensionsConfig;
    readConfig(extensionsConfig, MLTSG_EXTENSIONS_CONFIG);

    if (!extensionsConfig.at("VK_EXT_debug_utils").Boolean())
    {
        return;
    }

    auto cleanup = PFN_vkDestroyDebugUtilsMessengerEXT(
        vkGetInstanceProcAddr(mltsg::gVkInstance, "vkDestroyDebugUtilsMessengerEXT")
    );
    cleanup(mltsg::gVkInstance, mltsg::gVkDebuger, MLTSG_GVKALC);
}

void setupInstance()
{
    mltsg::DEFAULT_VULKAN vulkanInfo{};

    // create default extensions config and read custom config:

    std::vector<VkExtensionProperties> extensions;
    uint32_t availableExtensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);
    extensions.resize(availableExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, extensions.data());

    std::vector<mltsg::ConfigItem> extensionsConfig(availableExtensionCount);
    for (size_t i = 0; i < availableExtensionCount; ++i) 
    { 
        extensionsConfig[i] = { extensions[i].extensionName, mltsg::ConfigType::Boolean, false };
    }

    makeConfig(MLTSG_EXTENSIONS_CONFIG, extensionsConfig);

    readConfig(extensionsConfig, MLTSG_EXTENSIONS_CONFIG);
    print("\033[34;47mvulkan extensions\033[0m", extensionsConfig);

    std::vector<const char*> usedExtensions;
    for (const auto& ext : extensionsConfig)
    {
        if (ext.Boolean())
        {
            usedExtensions.push_back(ext.key.c_str());
        }
    }

    vulkanInfo.enabledExtensionCount = MLTSG_U32(usedExtensions.size());
    vulkanInfo.ppEnabledExtensionNames = usedExtensions.data();

    // create default layers config and read custom config:

    std::vector<VkLayerProperties> layers;
    uint32_t availableLayerCount;
    vkEnumerateInstanceLayerProperties(&availableLayerCount, nullptr);
    layers.resize(availableLayerCount);
    vkEnumerateInstanceLayerProperties(&availableLayerCount, layers.data());

    std::vector<mltsg::ConfigItem> layerConfig(availableLayerCount);
    for (size_t i = 0; i < availableLayerCount; ++i) 
    { 
        layerConfig[i] = { layers[i].layerName, mltsg::ConfigType::Boolean, false };
    }

    makeConfig(MLTSG_LAYERS_CONFIG, layerConfig);

    readConfig(layerConfig, MLTSG_LAYERS_CONFIG);
    print("\033[34;47mvulkan layers\033[0m", layerConfig);

    std::vector<const char*> usedLayers;
    for (const auto& layer : layerConfig)
    {
        if (layer.Boolean())
        {
            usedLayers.push_back(layer.key.c_str());
        }
    }

    vulkanInfo.enabledLayerCount = MLTSG_U32(usedLayers.size());
    vulkanInfo.ppEnabledLayerNames = usedLayers.data();

    // create instance:

    mltsg::trydo(VK_SUCCESS) = vkCreateInstance(&vulkanInfo, MLTSG_GVKALC, &mltsg::gVkInstance);
}

void configDeviceFeatures(VkPhysicalDeviceFeatures* features)
{
    memset(features, 0, sizeof(VkPhysicalDeviceFeatures));
    if (mltsg::gVkPhysicalDeviceFeatures.samplerAnisotropy)
    {
        features->samplerAnisotropy = VK_TRUE;
    }
}

void setupDevice()
{
    // choose physical device:

    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(mltsg::gVkInstance, &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(mltsg::gVkInstance, &deviceCount, devices.data());

    std::vector<mltsg::ConfigItem> deviceConfig;
    std::map<std::string, VkPhysicalDevice> deviceSet;
    for (const auto& c : devices)
    {
        VkPhysicalDeviceProperties physicalDeviceProperties;
        vkGetPhysicalDeviceProperties(c, &physicalDeviceProperties);
        deviceConfig.push_back({ physicalDeviceProperties.deviceName, mltsg::ConfigType::String, MLTSG_CFG("Off") });
        deviceSet.insert({ physicalDeviceProperties.deviceName, c });

        mltsg::Log("\n%s: \n    type: %d\n    API version: %d\n    driver version: %d\n",
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

        mltsg::Log("    features count: %d/%d\n", featuresCount, allfeaturesCount);
    }

    makeConfig(MLTSG_DEVICES_CONFIG, deviceConfig, MLTSG_CFG("On"));

    readConfig(deviceConfig, MLTSG_DEVICES_CONFIG);
    print("\033[34;45mDevice use\033[0m", deviceConfig);

    for (const auto& devConfig : deviceConfig)
    {
        if (devConfig.String() == "On" || devConfig.String() == "on")
        {
            mltsg::gVkPhysicalDevice = deviceSet.at(devConfig.key);
            vkGetPhysicalDeviceFeatures(mltsg::gVkPhysicalDevice, &mltsg::gVkPhysicalDeviceFeatures);
            vkGetPhysicalDeviceProperties(mltsg::gVkPhysicalDevice, &mltsg::gVkPhysicalDeviceProperties);
            break;
        }
    }

    // ! create logical device

    VkPhysicalDeviceFeatures deviceFeatures = {};

    uint32_t queuefamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(mltsg::gVkPhysicalDevice, &queuefamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queuefamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(mltsg::gVkPhysicalDevice, &queuefamilyCount, queueFamilies.data());

    bool queueFound = false;
    mltsg::gVkGraphicsIndice = 0;
    for (size_t i = 0; i < queueFamilies.size(); ++i)
    {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            mltsg::gVkGraphicsIndice = MLTSG_U32(i);
            queueFound = true;
        }
    }

    if (!queueFound)
    {
        mltsg::LogErr("Failed to find graphics queue.\n");
        throw std::runtime_error("graphics queue");
    }

    mltsg::DEFAULT_GRAPHICS_QUEUE graphicsQueue{};
    graphicsQueue.queueCount = 1;
    graphicsQueue.queueFamilyIndex = mltsg::gVkGraphicsIndice;
    float graphicsPriority = 1.0f;
    graphicsQueue.pQueuePriorities = &graphicsPriority;
    
    mltsg::DEFAULT_DEVICE deviceInfo{};
    deviceInfo.pQueueCreateInfos = &graphicsQueue;
    deviceInfo.queueCreateInfoCount = 1;

    configDeviceFeatures(&deviceFeatures);

    deviceInfo.pEnabledFeatures = &deviceFeatures;

    mltsg::trydo(VK_SUCCESS) = vkCreateDevice(mltsg::gVkPhysicalDevice, &deviceInfo, MLTSG_GVKALC, &mltsg::gVkDevice);

    vkGetDeviceQueue(mltsg::gVkDevice, mltsg::gVkGraphicsIndice, 0, &mltsg::gVkGraphicsQueue);
}

void cleaupDevice()
{
    vkDestroyDevice(mltsg::gVkDevice, MLTSG_GVKALC);
}

void createCommandPool()
{
    mltsg::DEFAULT_COMMAND_POOL commandPoolInfo{};
    commandPoolInfo.queueFamilyIndex = mltsg::gVkGraphicsIndice;

    mltsg::trydo(VK_SUCCESS) = vkCreateCommandPool(mltsg::gVkDevice, &commandPoolInfo, MLTSG_GVKALC, &mltsg::gVkCommandPool);
}

void destoryCommandPool()
{
    vkDestroyCommandPool(mltsg::gVkDevice, mltsg::gVkCommandPool, MLTSG_GVKALC);
}

void mltsg::initializeVulkan()
{
    setupInstance();
    setupVkDebug();
    setupDevice();
    createCommandPool();

    mltsg::enableImageTransferBuffer();
    mltsg::enableUnifromTransfer();
    mltsg::enableMeshTransfer();

    mltsg::defaultLinearSampler = new mltsg::GSampler(mltsg::SampleUV::Repeat, mltsg::SamplePoint::Linear);

    // create default texture
    noneRefDate.create(512, 512, CV_8UC2);
    mltsg::process<MLTSG_U8>(noneRefDate, [&](glm::vec2 uv) {
        glm::vec4 c0 = glm::vec4(1.0f, 0.7f, 1.0f, 1.0f);
        glm::vec4 c1 = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
        glm::vec2 xy = uv * glm::vec2(noneRefDate.cols, noneRefDate.rows) / 32.0f;
        float lerp = float((int(xy.x) % 2 ^ (int(xy.y) % 2)));
        return glm::mix(c0, c1, lerp);
    });
    noneRefTexture = new mltsg::GPUMat(&noneRefDate, MLTSG_READ_MAT, true, MLTSG_USE_RAW);
    noneRefTexture->apply();
}

void mltsg::cleanupVulkan()
{
    delete noneRefTexture;

    delete mltsg::defaultLinearSampler;

    mltsg::disableMeshTransfer();
    mltsg::disableUnifromTransfer();
    mltsg::disableImageTransferBuffer();

    gImgMemory.memoryDisable();
    gVertexMemory.memoryDisable();
    gIndexMemory.memoryDisable();
    gUniformMemory.memoryDisable();
    gTransMemory.memoryDisable();
    gReadMemory.memoryDisable();

    destoryCommandPool();
    cleaupDevice();
    cleanupVkDebug();
    vkDestroyInstance(gVkInstance, MLTSG_GVKALC);
}

VkCommandBuffer mltsg::beginCommandOnce()
{
    VkCommandBuffer cmdBuf;

    mltsg::DEFAULT_COMMAND_BUFFER cmdBufferInfo{};
    cmdBufferInfo.commandPool = gVkCommandPool;

    mltsg::trydo(VK_SUCCESS) = vkAllocateCommandBuffers(gVkDevice, &cmdBufferInfo, &cmdBuf);

    vkBeginCommandBuffer(cmdBuf, &mltsg::the_ONE_TIME_CMD);

    return cmdBuf;
}

void mltsg::endCommandOnce(VkCommandBuffer cmdBuf, VkFence fence)
{
    vkEndCommandBuffer(cmdBuf);

    mltsg::ONE_TIME_SUBMIT submitInfo{};
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
