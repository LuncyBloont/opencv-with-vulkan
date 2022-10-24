#pragma once

#include "gpuMem.h"
#include "helper.h"
#include "vk/vkinfo.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <iostream>
#include <cstdint>

#define VKINFO_DECLARE(type, name, ...) \
    const static struct name : type { name() { __VA_ARGS__ } } the_##name

#define GVKALC nullptr

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
    static const _Log_Type_ VkMoreLog({
        "* vulkan *",
        "\033[44;1m",
        "\033[30m",
        "\033[34m"
    }, stdout);

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
                    LogErr("VK::: error[%d]@%s> %s\n", pCallbackData->messageIdNumber, pCallbackData->pMessageIdName, pCallbackData->pMessage);
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                    LogWarn("VK::: warn[%d]@%s> %s\n", pCallbackData->messageIdNumber, pCallbackData->pMessageIdName, pCallbackData->pMessage);
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                    VkMoreLog("VK::: info[%d]@%s> %s\n", pCallbackData->messageIdNumber, pCallbackData->pMessageIdName, pCallbackData->pMessage);
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                    if (ECHO_VULKAN_VERBOSE)
                    {
                        VkMoreLog("VK::: verb[%d]@%s> %s\n", pCallbackData->messageIdNumber, pCallbackData->pMessageIdName, pCallbackData->pMessage);
                    }
                    break;
                default:
                    VkMoreLog("VK::: other[%d]@%s> %s\n", pCallbackData->messageIdNumber, pCallbackData->pMessageIdName, pCallbackData->pMessage);
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

VKINFO_DECLARE(VkImageMemoryBarrier, IMAGE_BARRIER, 
    this->image = VK_NULL_HANDLE;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    this->dstAccessMask = 0;
    this->srcAccessMask = 0;
    this->dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    this->srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    this->oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    this->newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    this->subresourceRange = VkImageSubresourceRange{
        VK_IMAGE_ASPECT_COLOR_BIT,
        0, 1, 0, 1
    };
);

VKINFO_DECLARE(VkBufferCreateInfo, DEFAULT_BUFFER,
    this->sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    this->pNext = nullptr;
    this->flags = 0;
    this->pQueueFamilyIndices = nullptr;
    this->queueFamilyIndexCount = 0;
    this->size = 0;
    this->sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    this->usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
);

VKINFO_DECLARE(VkRenderPassCreateInfo, DEFAULT_RENDERPASS,
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    this->attachmentCount = 0;
    this->pAttachments = nullptr;
    this->dependencyCount = 0;
    this->pDependencies = nullptr;
    this->subpassCount = 0;
    this->pSubpasses = nullptr;
    this->flags = 0;
);

VKINFO_DECLARE(VkGraphicsPipelineCreateInfo, GRAPHICS_PIPELINE, 
    this->basePipelineHandle = VK_NULL_HANDLE;
    this->basePipelineIndex = -1;
    this->flags = 0;
    this->layout = VK_NULL_HANDLE;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    this->stageCount = 0;
    this->pStages = nullptr;
    this->pColorBlendState = nullptr;
    this->pDepthStencilState = nullptr;
    this->pInputAssemblyState = nullptr;
    this->pVertexInputState = nullptr;
    this->pDynamicState = nullptr;
    this->pMultisampleState = nullptr;
    this->pRasterizationState = nullptr;
    this->pTessellationState = nullptr;
    this->pViewportState = nullptr;
    this->renderPass = VK_NULL_HANDLE;
    this->subpass = 0;
);

VKINFO_DECLARE(VkPipelineInputAssemblyStateCreateInfo, TRIANGLE_FAN_INPUT, 
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    this->flags = 0;
    this->pNext = nullptr;
    this->primitiveRestartEnable = VK_TRUE;
    this->topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
);

VKINFO_DECLARE(VkPipelineRasterizationStateCreateInfo, FILL_RASTERIZATION, 
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    this->flags = 0;
    this->lineWidth = 1.0f;
    this->cullMode = VK_CULL_MODE_NONE;
    this->polygonMode = VK_POLYGON_MODE_FILL;
    this->frontFace = VK_FRONT_FACE_CLOCKWISE;
    this->rasterizerDiscardEnable = VK_FALSE;
    this->depthBiasEnable = VK_FALSE;
    this->depthBiasClamp = 0.0f;
    this->depthClampEnable = VK_FALSE;
    this->depthBiasConstantFactor = 0.0f;
    this->depthBiasSlopeFactor = 0.0f;
);

VKINFO_DECLARE(VkSamplerCreateInfo, EMPTY_SAMPLER,
    this->addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;        // customize
    this->addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;        // customize
    this->addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;        // customize
    this->mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;                  // customize
    this->anisotropyEnable = VK_FALSE;
    this->compareEnable = VK_FALSE;
    this->compareOp = VK_COMPARE_OP_EQUAL;
    this->borderColor = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
    this->flags = 0;
    this->sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    this->unnormalizedCoordinates = VK_FALSE;
    this->pNext = nullptr;
    this->magFilter = VK_FILTER_LINEAR;                                // customize
    this->minFilter = VK_FILTER_LINEAR;                                // customize
    this->maxAnisotropy = 0.0f;
    this->maxLod = 12;
    this->minLod = 0;
    this->mipLodBias = 0.0f;
);

VKINFO_DECLARE(VkPipelineColorBlendStateCreateInfo, NO_BLEND_STATE, 
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    this->flags = 0;
    this->blendConstants[0] = 0.0f;
    this->blendConstants[1] = 0.0f;
    this->blendConstants[2] = 0.0f;
    this->blendConstants[3] = 0.0f;
    this->attachmentCount = 0;
    this->logicOp = VK_LOGIC_OP_AND;
    this->logicOpEnable = VK_FALSE;
    this->pAttachments = nullptr;
    this->pNext = nullptr;
);

VKINFO_DECLARE(VkPipelineDepthStencilStateCreateInfo, DEFAULT_DEPTHSTECNIL_STATE,
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    this->pNext = nullptr;
    this->depthBoundsTestEnable = VK_FALSE;
    this->depthTestEnable = VK_FALSE;
    this->depthWriteEnable = VK_FALSE;
    this->stencilTestEnable = VK_FALSE;
    this->maxDepthBounds = 1.0f;
    this->minDepthBounds = 0.0f;
    this->depthCompareOp = VK_COMPARE_OP_GREATER;
    this->back.compareMask = 0;
    this->back.compareOp = VK_COMPARE_OP_ALWAYS;
    this->back.writeMask = 0;
    this->back.depthFailOp = VK_STENCIL_OP_KEEP;
    this->back.reference = 0;
    this->back.failOp = VK_STENCIL_OP_KEEP;
    this->back.passOp = VK_STENCIL_OP_KEEP;
    this->front.compareMask = 0;
    this->front.compareOp = VK_COMPARE_OP_ALWAYS;
    this->front.writeMask = 0;
    this->front.depthFailOp = VK_STENCIL_OP_KEEP;
    this->front.reference = 0;
    this->front.failOp = VK_STENCIL_OP_KEEP;
    this->front.passOp = VK_STENCIL_OP_KEEP;
);

VKINFO_DECLARE(VkPipelineDynamicStateCreateInfo, DEFAULT_DYNAMIC_STATE, 
    this->dynamicStateCount = 0;
    this->flags = 0;
    this->pDynamicStates = nullptr;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
);

VKINFO_DECLARE(VkPipelineMultisampleStateCreateInfo, DEFAULT_MSAA, 
    this->alphaToCoverageEnable = VK_FALSE;
    this->alphaToOneEnable = VK_FALSE;
    this->sampleShadingEnable = VK_FALSE;
    this->minSampleShading = 0.0f;
    this->rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    this->flags = 0;
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    this->pNext = nullptr;
    this->pSampleMask = nullptr;
);

VKINFO_DECLARE(VkPipelineViewportStateCreateInfo, DEFAULT_VIEWPORT, 
    this->viewportCount = 0;
    this->pViewports = nullptr;
    this->scissorCount = 0;
    this->pScissors = nullptr;
    this->flags = 0;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
);

VKINFO_DECLARE(VkPipelineTessellationStateCreateInfo, NO_TESSELLATION, 
    this->flags = 0;
    this->patchControlPoints = 1;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
);

VKINFO_DECLARE(VkPipelineVertexInputStateCreateInfo, VERTEX_STATE_FOR_CV, 
    this->flags = 0;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    this->vertexAttributeDescriptionCount = 0;
    this->vertexBindingDescriptionCount = 0;
    this->pVertexAttributeDescriptions = nullptr;
    this->pVertexBindingDescriptions = nullptr;
);

VKINFO_DECLARE(VkPipelineShaderStageCreateInfo, SHADER_STAGES, 
    this->pSpecializationInfo = nullptr;
    this->stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    this->flags = 0;
    this->module = VK_NULL_HANDLE;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    this->pName = "main";
);

VKINFO_DECLARE(VkShaderModuleCreateInfo, SHADER_INFO, 
    this->codeSize = 0;
    this->pCode = nullptr;
    this->flags = 0;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
);

VKINFO_DECLARE(VkPipelineLayoutCreateInfo, PIPELINE_LAYOUT,
    this->setLayoutCount = 0;
    this->pSetLayouts = nullptr;
    this->flags = 0;
    this->pNext = nullptr;
    this->pushConstantRangeCount = 0;
    this->pPushConstantRanges = nullptr;
    this->sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
);

VKINFO_DECLARE(VkDescriptorSetLayoutCreateInfo, DESCRIPTOR_SET_LAYOUT,
    this->sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    this->pNext = nullptr;
    this->flags = 0;
    this->bindingCount = 0;
    this->pBindings = nullptr;
);

VKINFO_DECLARE(VkDescriptorPoolCreateInfo, DESCRIPTOR_POOL, 
    this->poolSizeCount = 0;
    this->pPoolSizes = nullptr;
    this->flags = 0;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    this->maxSets = 0;
);

VKINFO_DECLARE(VkDescriptorSetAllocateInfo, DESCRIPTOR_SET_ALLOCATOR, 
    this->descriptorPool = VK_NULL_HANDLE;
    this->descriptorSetCount = 0;
    this->pNext = nullptr;
    this->pSetLayouts = nullptr;
    this->sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
);

VKINFO_DECLARE(VkWriteDescriptorSet, WRITE_DESCCRIPTOR, 
    this->descriptorCount = 0;
    this->descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    this->pBufferInfo = nullptr;
    this->pImageInfo = nullptr;
    this->dstArrayElement = 0;
    this->dstBinding = 0;
    this->dstSet = VK_NULL_HANDLE;
    this->pNext = nullptr;
    this->pTexelBufferView = nullptr;
    this->sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
);

VKINFO_DECLARE(VkFenceCreateInfo, VKFENCE,
    this->flags = 0;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
);

VKINFO_DECLARE(VkRenderPassBeginInfo, RENDERPASS_BEGIN,
    this->renderPass = VK_NULL_HANDLE;
    this->renderArea = { { 0, 0 }, { 0, 0 } };
    this->clearValueCount = 0;
    this->pClearValues = nullptr;
    this->framebuffer = VK_NULL_HANDLE;
    this->pNext = nullptr;
    this->sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
);

VKINFO_DECLARE(VkFramebufferCreateInfo, FRAMEBUFFER_INFO,
    this->attachmentCount = 0;
    this->pAttachments = nullptr;
    this->flags = 0;
    this->height = 64;
    this->width = 64;
    this->layers = 1;
    this->pNext = nullptr;
    this->renderPass = VK_NULL_HANDLE;
    this->sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
);

#undef VKINFO_DECLARE