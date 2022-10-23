#include "stage.h"
#include "gpuMat.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "vkHelper.h"
#include "vkenv.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <vcruntime.h>

Stage::Stage(uint32_t width, uint32_t height, const StageProperties& assets) : assets(assets)
{
    data = cv::Mat(height, width, CV_8UC4);
    frame = new GPUMat(&data, WRITE_MAT, USE_SRGB);

    createShader();

    buildRenderPass();

    buildUniform();

    createPipelineLayout();
    
    buildPipeline();
}

Stage::~Stage()
{
    cleanup();

    delete frame;
}

void Stage::render(uint32_t newAge)
{
    if (age < newAge)
    {
        age = newAge;
        for (size_t i = 0; i < assets.reference.size(); ++i)
        {
            if (assets.reference[i] != nullptr)
            {
                assets.reference[i]->render(newAge);
            }
        }
    }

    // TODO:
}

void Stage::show(const char* windowName) const
{
    frame->apply();
    cv::imshow(windowName, data);
}

void Stage::createShader()
{
    // readShader(vertexShader, assets.customVertexShader);
    // readShader(fragmentShader, assets.shaderPath);
}

void Stage::createPipelineLayout()
{

}

void Stage::buildUniform()
{

}

void Stage::buildRenderPass()
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
    
    trydo(VK_SUCCESS) = vkCreateRenderPass(gVkDevice, &renderPassInfo, GVKALC, &renderPass);
}

void Stage::buildPipeline()
{
    GRAPHICS_PIPELINE pipelineInfo{};

    pipelineInfo.pInputAssemblyState = &the_TRIANGLE_FAN_INPUT;

    pipelineInfo.pRasterizationState = &the_FILL_RASTERIZATION;

    NO_BLEND_STATE colorBlend{};

    VkPipelineColorBlendAttachmentState attachmentStates[1];
    attachmentStates[0].colorBlendOp = VK_BLEND_OP_ADD;
    attachmentStates[0].blendEnable = VK_FALSE;
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

    VkVertexInputAttributeDescription pos{};
    pos.binding = 0;
    pos.format = VK_FORMAT_R32G32B32A32_SFLOAT;
    pos.location = 0;
    pos.offset = 0;

    VkVertexInputBindingDescription posBinding{};
    posBinding.binding = 0;
    posBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    posBinding.stride = 3 * sizeof(float);

    vertexInfo.vertexBindingDescriptionCount = 1;
    vertexInfo.vertexAttributeDescriptionCount = 1;
    vertexInfo.pVertexAttributeDescriptions = &pos;
    vertexInfo.pVertexBindingDescriptions = &posBinding;

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
}

void Stage::cleanup()
{
    vkDestroyRenderPass(gVkDevice, renderPass, GVKALC);
}