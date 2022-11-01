#include "stage.h"
#include "glm/fwd.hpp"
#include "gpuBuf.h"
#include "gpuMat.h"
#include "helper.h"
#include "imageHelper.h"
#include "opencv2/core.hpp"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "vkHelper.h"
#include "vkenv.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <stdint.h>
#include <string>
#include <vcruntime.h>
#include <vcruntime_string.h>

mltsg::GPUBuffer* mltsg::uniformSrcBuffer = nullptr;

mltsg::GPUBuffer* mltsg::meshSrcBuffer = nullptr;

int32_t mltsg::uiMouseX = -100, mltsg::uiMouseY = -100;
float mltsg::uiMouseLBT = 0.0f, mltsg::uiMouseRBT = 0.0f;

void mltsg::enableUnifromTransfer()
{
    uniformSrcBuffer = new mltsg::GPUBuffer(4096 * 32, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
}

void mltsg::disableUnifromTransfer()
{
    delete uniformSrcBuffer;
}

void mltsg::enableMeshTransfer()
{
    meshSrcBuffer = new mltsg::GPUBuffer(10000 * 4 * 4 * 8 * 3, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
}

void mltsg::disableMeshTransfer()
{
    delete meshSrcBuffer;
}

mltsg::Stage::Stage(uint32_t width, uint32_t height, StageProperties* assets, bool HDR) : width(width), height(height), assets(assets)
{
    static int idForTag;

    tag = std::string("Stage(") + std::to_string(idForTag) + ")";
    idForTag += 1;

    data = cv::Mat(height, width, HDR ? CV_32SC4 : CV_8UC4);
    
    frame = new GPUMat(&data, MLTSG_WRITE_MAT, false, MLTSG_USE_RAW, HDR);

    createShader();

    buildRenderPass();

    createFramebuffer();

    buildUniform();

    createPipelineLayout();
    
    buildPipeline();

    createEtc();
}

mltsg::Stage::~Stage()
{
    cleanup();

    delete frame;
}

void mltsg::Stage::render(uint32_t newAge)
{
    if (age >= newAge)
    {
        return;
    }

    age = newAge;
    for (size_t i = 0; i < assets->reference.size(); ++i)
    {
        if (assets->reference[i] != nullptr)
        {
            assets->reference[i]->render(newAge);
        }
    }
    
    transitionImageLayout(frame->image, frame->format, 0, {
        VK_IMAGE_LAYOUT_UNDEFINED,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    });

    updateUniform();

    VkCommandBuffer cmd = beginCommandOnce();

    RENDERPASS_BEGIN beginInfo{};
    beginInfo.renderPass = renderPass;
    beginInfo.renderArea = { { 0, 0 }, { width, height } };
    beginInfo.framebuffer = frameBuffer;
    beginInfo.clearValueCount = 1;
    
    VkClearValue clearValue{};
    clearValue.color = { { 0.0f, 0.0f, 0.0f, 0.0f } };

    beginInfo.pClearValues = &clearValue;

    vkCmdBeginRenderPass(cmd, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

    VkDeviceSize vertexBindingOffsets[1] = { 0 };

    vkCmdBindVertexBuffers(cmd, 0, 1, &vertexBuffer->buffer, vertexBindingOffsets);
    vkCmdBindIndexBuffer(cmd, indexBuffer->buffer, 0, VK_INDEX_TYPE_UINT32);

    vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, 
        pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);

    vkCmdDrawIndexed(cmd, MLTSG_U32(mesh.index.size()), 1, 0, 0, 0);

    vkCmdEndRenderPass(cmd);

    endCommandOnce(cmd, fence);

    transitionImageLayout(frame->image, frame->format, 0, {
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
    });
    
    MLTSG_LogDB("%s render complete at Age(\t%d\t)\n", tag.c_str(), newAge);
}

void mltsg::Stage::createFramebuffer()
{
    FRAMEBUFFER_INFO frameInfo{};
    frameInfo.attachmentCount = 1;
    frameInfo.pAttachments = &frame->view;
    frameInfo.width = width;
    frameInfo.height = height;
    frameInfo.layers = 1;
    frameInfo.renderPass = renderPass;

    trydo(VK_SUCCESS) = vkCreateFramebuffer(gVkDevice, &frameInfo, MLTSG_GVKALC, &frameBuffer);
}

void mltsg::Stage::createEtc()
{
    trydo(VK_SUCCESS) = vkCreateFence(gVkDevice, &the_VKFENCE, MLTSG_GVKALC, &fence);

    vertexBuffer = new GPUBuffer(SCREEN_VERTEX_SIZE * 4, 
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_BUFFER_USAGE_TRANSFER_DST_BIT);
    // componentCnt * 2 * vertexCnt * sizeofComponent
    meshSrcBuffer->mapMem();
    memcpy(meshSrcBuffer->data, mesh.vertexData.data(), mesh.vertexData.size() * SCREEN_VERTEX_SIZE);
    meshSrcBuffer->unmapMem();
    copyBufferToBuffer(meshSrcBuffer->buffer, vertexBuffer->buffer, SCREEN_VERTEX_SIZE * 4);

    indexBuffer = new GPUBuffer(sizeof(uint32_t) * mesh.index.size(), 
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_BUFFER_USAGE_TRANSFER_DST_BIT);
    meshSrcBuffer->mapMem();
    memcpy(meshSrcBuffer->data, mesh.index.data(), mesh.index.size() * sizeof(uint32_t));
    meshSrcBuffer->unmapMem();
    copyBufferToBuffer(meshSrcBuffer->buffer, indexBuffer->buffer, sizeof(uint32_t) * mesh.index.size());

}

int mltsg::Stage::show(const char* windowName) const
{
    struct Pack{
        const char* wname;
        int keyCode;
    } pack { windowName, 0 };

    if (frame->showAge < age)
    {
        frame->peek([](GPUMat* self, void* data) {
            Pack* pack = reinterpret_cast<Pack*>(data);
            cv::imshow(pack->wname, *self->cpuData);
            pack->keyCode = cv::pollKey();
        }, &pack);
        frame->showAge = age;
    }
    
    return pack.keyCode;
}

void mltsg::Stage::createShader()
{
    readShader(vertexShader, assets->customVertexShader);
    readShader(fragmentShader, assets->shaderPath);
}

mltsg::GPUMat* mltsg::Stage::getGPUMat() { return frame; }

void mltsg::Stage::createPipelineLayout()
{
    PIPELINE_LAYOUT layoutInfo{};

    layoutInfo.setLayoutCount = 1;
    layoutInfo.pSetLayouts = &descriptorSetLayout;
    
    trydo(VK_SUCCESS) = vkCreatePipelineLayout(gVkDevice, &layoutInfo, MLTSG_GVKALC, &pipelineLayout);
}

void mltsg::Stage::buildUniform()
{
    // create descriptor set layout

    DESCRIPTOR_SET_LAYOUT descriptorSetLayoutInfo{};
    
    VkDescriptorSetLayoutBinding bindings[3]; // one uniform object and six textures
    
    bindings[0].binding = 0;
    bindings[0].descriptorCount = 1;
    bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    bindings[0].pImmutableSamplers = nullptr;
    bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;

    bindings[1].descriptorCount = MLTSG_REFERENCE_COUNT;
    bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    bindings[1].binding = 1;
    bindings[1].pImmutableSamplers = nullptr;
    bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

    bindings[2].descriptorCount = MLTSG_TEXTURES_COUNT;
    bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    bindings[2].binding = 2;
    bindings[2].pImmutableSamplers = nullptr;
    bindings[2].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    
    descriptorSetLayoutInfo.bindingCount = 3;
    descriptorSetLayoutInfo.pBindings = bindings;

    trydo(VK_SUCCESS) = vkCreateDescriptorSetLayout(gVkDevice, &descriptorSetLayoutInfo, 
        MLTSG_GVKALC, &descriptorSetLayout);
    
    // create descriptor pool

    DESCRIPTOR_POOL descriptorPoolInfo{};

    VkDescriptorPoolSize poolSizes[2];
    
    poolSizes[0].descriptorCount = 1;
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

    poolSizes[1].descriptorCount = MLTSG_REFERENCE_COUNT + MLTSG_TEXTURES_COUNT;
    poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

    descriptorPoolInfo.poolSizeCount = 2;
    descriptorPoolInfo.pPoolSizes = poolSizes;
    descriptorPoolInfo.maxSets = 1;
    
    trydo(VK_SUCCESS) = vkCreateDescriptorPool(gVkDevice, 
        &descriptorPoolInfo, MLTSG_GVKALC, &descriptorPool);

    // allocate descriptor set

    DESCRIPTOR_SET_ALLOCATOR allocator{};

    allocator.descriptorPool = descriptorPool;
    allocator.descriptorSetCount = 1;
    allocator.pSetLayouts = &descriptorSetLayout;

    trydo(VK_SUCCESS) = vkAllocateDescriptorSets(gVkDevice, &allocator, &descriptorSet);

    uniformBuffer = new GPUBuffer(sizeof(DefaultUniform), 
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_BUFFER_USAGE_TRANSFER_DST_BIT);
}


void mltsg::Stage::updateUniform()
{
    float time = clock() * 1.0f / CLOCKS_PER_SEC;

    uniform.vector[8 + MLTSG_TEXTURES_COUNT + MLTSG_REFERENCE_COUNT] = {
        time,
        0.5f * time,
        time * 1000.0f,
        float(age - 1)
    };

    uniform.vector[8 + MLTSG_TEXTURES_COUNT + MLTSG_REFERENCE_COUNT + 1] = {
        width,
        height,
        age,
        age * 0.5f
    };

    uniform.vector[8 + MLTSG_TEXTURES_COUNT + MLTSG_REFERENCE_COUNT + 2] = {
        uiMouseX,
        uiMouseY,
        uiMouseLBT,
        uiMouseRBT
    };

    for (uint32_t i = 0; i < MLTSG_REFERENCE_COUNT; ++i)
    {
        if (assets->reference[i])
        {
            uniform.vector[8 + i] = {
                assets->reference[i]->width,
                assets->reference[i]->height,
                assets->reference[i]->frame->levels,
                0.0f
            };
        }
        else 
        {
            uniform.vector[8 + i] = { 0.0f, 0.0f, 0.0f, 0.0f };
        }
    }

    for (uint32_t i = 0; i < MLTSG_TEXTURES_COUNT; ++i)
    {
        if (assets->textures[i])
        {
            uniform.vector[8 + i + MLTSG_REFERENCE_COUNT] = {
                assets->textures[i]->width(),
                assets->textures[i]->height(),
                assets->textures[i]->levels,
                0.0f
            };
        }
        else 
        {
            uniform.vector[8 + i] = { 0.0f, 0.0f, 0.0f, 0.0f };
        }
    }

    for (uint32_t i = 0; i < 8; ++i)
    {
        uniform.vector[i] = assets->uniVec[i];
        uniform.matrix[i] = assets->uniMat[i];
    }

    writeUniform();
}

void mltsg::Stage::writeUniform()
{
    // update uniform

    WRITE_DESCCRIPTOR writeUniform{};
    writeUniform.descriptorCount = 1;
    writeUniform.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writeUniform.dstBinding = 0;
    writeUniform.dstArrayElement = 0;
    writeUniform.dstSet = descriptorSet;

    VkDescriptorBufferInfo uniformInfo{};
    uniformInfo.buffer = uniformBuffer->buffer;
    uniformInfo.offset = 0;
    uniformInfo.range = sizeof(DefaultUniform);

    writeUniform.pBufferInfo = &uniformInfo;

    uniformSrcBuffer->mapMem();
    memcpy(uniformSrcBuffer->data, &uniform, sizeof(DefaultUniform));
    uniformSrcBuffer->unmapMem();

    copyBufferToBuffer(uniformSrcBuffer->buffer, uniformBuffer->buffer, sizeof(DefaultUniform));

    vkUpdateDescriptorSets(gVkDevice, 1, &writeUniform, 0, nullptr);

    // update reference

    WRITE_DESCCRIPTOR writeReference{};
    writeReference.descriptorCount = MLTSG_REFERENCE_COUNT;
    writeReference.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeReference.dstBinding = 1;
    writeReference.dstArrayElement = 0;
    writeReference.dstSet = descriptorSet;
    
    VkDescriptorImageInfo referenceInfos[MLTSG_REFERENCE_COUNT];
    for (uint32_t i = 0; i < MLTSG_REFERENCE_COUNT; i++)
    {
        referenceInfos[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        referenceInfos[i].imageView = assets->reference[i] ? assets->reference[i]->frame->view : noneRefTexture->view;
        referenceInfos[i].sampler = assets->reference[i] ? assets->reference[i]->frame->sampler->sampler : noneRefTexture->sampler->sampler;
    }

    writeReference.pImageInfo = referenceInfos;

    vkUpdateDescriptorSets(gVkDevice, 1, &writeReference, 0, nullptr);

    // update textures

    WRITE_DESCCRIPTOR writeTextures{};
    writeTextures.descriptorCount = MLTSG_TEXTURES_COUNT;
    writeTextures.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writeTextures.dstBinding = 2;
    writeTextures.dstArrayElement = 0;
    writeTextures.dstSet = descriptorSet;

    VkDescriptorImageInfo texturesInfo[MLTSG_TEXTURES_COUNT];
    for (uint32_t i = 0; i < MLTSG_TEXTURES_COUNT; i++)
    {
        texturesInfo[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        texturesInfo[i].imageView = assets->textures[i] ? assets->textures[i]->view : noneRefTexture->view;
        texturesInfo[i].sampler = assets->textures[i] ? assets->textures[i]->sampler->sampler : noneRefTexture->sampler->sampler;
    }

    writeTextures.pImageInfo = texturesInfo;

    vkUpdateDescriptorSets(gVkDevice, 1, &writeTextures, 0, nullptr);
}

void mltsg::Stage::buildRenderPass()
{
    VkAttachmentDescription attachments[1];
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachments[0].format = frame->format;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].flags = 0;
    attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;

    VkAttachmentReference attachment0References[1];
    attachment0References[0].attachment = 0;
    attachment0References[0].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpasses[1];
    subpasses[0].colorAttachmentCount = 1;
    subpasses[0].inputAttachmentCount = 0;
    subpasses[0].preserveAttachmentCount = 0;
    subpasses[0].pColorAttachments = attachment0References;
    subpasses[0].pInputAttachments = nullptr;
    subpasses[0].pPreserveAttachments = nullptr;
    subpasses[0].pResolveAttachments = nullptr;
    subpasses[0].pDepthStencilAttachment = nullptr;
    subpasses[0].flags = 0;
    subpasses[0].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

    VkSubpassDependency subpassDependencies[2];
    subpassDependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
    subpassDependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[0].dstSubpass = 0;
    subpassDependencies[0].srcAccessMask = VK_ACCESS_NONE;
    subpassDependencies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[0].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    
    subpassDependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;
    subpassDependencies[1].srcSubpass = 0;
    subpassDependencies[1].dstSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependencies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    subpassDependencies[1].dstAccessMask = VK_ACCESS_NONE;
    subpassDependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependencies[1].dstStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

    DEFAULT_RENDERPASS renderPassInfo{};
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = subpasses;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = attachments;
    renderPassInfo.dependencyCount = 2;
    renderPassInfo.pDependencies = subpassDependencies;
    
    trydo(VK_SUCCESS) = vkCreateRenderPass(gVkDevice, &renderPassInfo, MLTSG_GVKALC, &renderPass);
}

void mltsg::Stage::buildPipeline()
{
    GRAPHICS_PIPELINE pipelineInfo{};

    pipelineInfo.pInputAssemblyState = &the_TRIANGLE_FAN_INPUT;

    pipelineInfo.pRasterizationState = &the_FILL_RASTERIZATION;

    NO_BLEND_STATE colorBlend{};

    VkPipelineColorBlendAttachmentState attachmentStates[1];
    attachmentStates[0].colorBlendOp = VK_BLEND_OP_ADD;
    attachmentStates[0].blendEnable = VK_FALSE;
    attachmentStates[0].alphaBlendOp = VK_BLEND_OP_ADD;
    attachmentStates[0].srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    attachmentStates[0].dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    attachmentStates[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    attachmentStates[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    attachmentStates[0].colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
        VK_COLOR_COMPONENT_G_BIT |
        VK_COLOR_COMPONENT_B_BIT |
        VK_COLOR_COMPONENT_A_BIT;

    colorBlend.attachmentCount = 1;
    colorBlend.pAttachments = attachmentStates;
    
    pipelineInfo.pColorBlendState = &colorBlend;

    pipelineInfo.pDepthStencilState = &the_DEFAULT_DEPTHSTECNIL_STATE;

    pipelineInfo.pDynamicState = &the_DEFAULT_DYNAMIC_STATE;

    pipelineInfo.pMultisampleState = &the_DEFAULT_MSAA;

    DEFAULT_VIEWPORT viewportState{};

    viewportState.viewportCount = 1;
    viewportState.scissorCount = 1;

    VkViewport viewport{};
    viewport.width = float(width);
    viewport.height = float(height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    viewport.x = 0.0f;
    viewport.y = 0.0f;

    VkRect2D scissor{};
    scissor.offset = { 0, 0 };
    scissor.extent = { width, height };

    viewportState.pViewports = &viewport;
    viewportState.pScissors = &scissor;

    pipelineInfo.pViewportState = &viewportState;

    pipelineInfo.pTessellationState = &the_NO_TESSELLATION;
    
    VERTEX_STATE_FOR_CV vertexInfo{};

    VkVertexInputAttributeDescription inputAttributes[2];
    inputAttributes[0].binding = 0;
    inputAttributes[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
    inputAttributes[0].location = 0;
    inputAttributes[0].offset = 0;
    inputAttributes[1].binding = 0;
    inputAttributes[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
    inputAttributes[1].location = 1;
    inputAttributes[1].offset = sizeof(glm::vec4);

    VkVertexInputBindingDescription inputBindings[1];
    inputBindings[0].binding = 0;
    inputBindings[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    inputBindings[0].stride = SCREEN_VERTEX_SIZE;

    vertexInfo.vertexBindingDescriptionCount = 1;
    vertexInfo.vertexAttributeDescriptionCount = 2;
    vertexInfo.pVertexAttributeDescriptions = inputAttributes;
    vertexInfo.pVertexBindingDescriptions = inputBindings;

    pipelineInfo.pVertexInputState = &vertexInfo;

    pipelineInfo.subpass = 0;
    pipelineInfo.renderPass = renderPass;
    pipelineInfo.layout = pipelineLayout;
    
    pipelineInfo.stageCount = 2;

    SHADER_STAGES shaderStages[2];

    shaderStages[0].module = vertexShader;
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;

    shaderStages[1].module = fragmentShader;
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;

    pipelineInfo.pStages = shaderStages;

    trydo(VK_SUCCESS) = vkCreateGraphicsPipelines(gVkDevice, VK_NULL_HANDLE, 
        1, &pipelineInfo, MLTSG_GVKALC, &pipeline);
}

void mltsg::Stage::cleanup()
{
    delete uniformBuffer;
    delete vertexBuffer;
    delete indexBuffer;

    // vkFreeDescriptorSets(gVkDevice, descriptorPool, 1, &descriptorSet);
    /*
        It is invalid to call vkFreeDescriptorSets() with a pool created without setting VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT.
        https://vulkan.lunarg.com/doc/view/1.3.216.0/windows/1.3-extensions/vkspec.html#VUID-vkFreeDescriptorSets-descriptorPool-00312
    */
    vkDestroyFence(gVkDevice, fence, MLTSG_GVKALC);
    vkDestroyShaderModule(gVkDevice, vertexShader, MLTSG_GVKALC);    
    vkDestroyShaderModule(gVkDevice, fragmentShader, MLTSG_GVKALC);    
    vkDestroyPipeline(gVkDevice, pipeline, MLTSG_GVKALC);    
    vkDestroyPipelineLayout(gVkDevice, pipelineLayout, MLTSG_GVKALC);
    vkDestroyDescriptorSetLayout(gVkDevice, descriptorSetLayout, MLTSG_GVKALC);
    vkDestroyDescriptorPool(gVkDevice, descriptorPool, MLTSG_GVKALC);
    vkDestroyFramebuffer(gVkDevice, frameBuffer, MLTSG_GVKALC);
    vkDestroyRenderPass(gVkDevice, renderPass, MLTSG_GVKALC);
}