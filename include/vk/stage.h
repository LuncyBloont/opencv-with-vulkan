#ifndef CVVK_VK_STAGE_H
#define CVVK_VK_STAGE_H

#include "glm/fwd.hpp"
#include "gpuBuf.h"
#include "gpuMat.h"
#include "opencv2/core/mat.hpp"
#include "vkenv.h"
#include "vulkan/vulkan_core.h"
#include <array>
#include <stdint.h>
#include <string>
#include <vector>

namespace mltsg 
{

extern GPUBuffer* uniformSrcBuffer;

extern GPUBuffer* meshSrcBuffer;

extern int32_t uiMouseX, uiMouseY;
extern float uiMouseLBT, uiMouseRBT;

class Stage;

struct StageProperties
{
    std::array<Stage*, MLTSG_REFERENCE_COUNT> reference;
    std::array<GPUMat*, MLTSG_TEXTURES_COUNT> textures;

    std::array<glm::mat4x4, 8> uniMat;   
    std::array<glm::vec4, 8> uniVec; // custom vec4 x 8
    /* 
        system vec4 x (MLTSG_REFERENCE_COUNT + MLTSG_TEXTURES_COUNT + 1):
        0 to MLTSG_REFERENCE_COUNT - 1: reference[0 to MLTSG_REFERENCE_COUNT] info { width, height, mipmapLevel, 0.0 }    
        MLTSG_REFERENCE_COUNT to MLTSG_REFERENCE_COUNT + MLTSG_TEXTURES_COUNT - 1: textures[0 to MLTSG_TEXTURES_COUNT] info { width, height, mipmapLevel, 0.0 }   
        MLTSG_REFERENCE_COUNT + MLTSG_TEXTURES_COUNT: time { s, 1/2s, ms, freme count }
        MLTSG_REFERENCE_COUNT + MLTSG_TEXTURES_COUNT + 1: { frame width, frame height, age, 1/2age } 
        MLTSG_REFERENCE_COUNT + MLTSG_TEXTURES_COUNT + 2: { mouseX, mouseY, mouseLBT, mouseRBT }
    */

    std::string shaderPath;
    
    const std::string customVertexShader = "../defaultVS/screenRect.spv";
};

struct DefaultUniform
{
    alignas(16) glm::mat4 matrix[8];
    alignas(16) glm::vec4 vector[8 + MLTSG_REFERENCE_COUNT + MLTSG_TEXTURES_COUNT + 3];
};

struct ScreenMesh
{
    std::vector<glm::vec4> vertexData = {
        { -1.0f, -1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 1.0f },
        { 1.0f, -1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f },
        { -1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }
        // pos, uv
    };
    std::vector<uint32_t> index {
        0, 1, 2, 3,
        UINT32_MAX
    };
};

#define SCREEN_VERTEX_SIZE (sizeof(glm::vec4) * 2)

class Stage
{
private:
    GPUMat* frame;
    GPUMat* mirror;
    cv::Mat data;

    VkFramebuffer frameBuffer;

    VkRenderPass renderPass;
    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    
    VkDescriptorSet descriptorSet;

    VkShaderModule vertexShader;
    VkShaderModule fragmentShader;

    VkFence fence;

    GPUBuffer* uniformBuffer;
    GPUBuffer* vertexBuffer;
    GPUBuffer* indexBuffer;

    ScreenMesh mesh;

    DefaultUniform uniform;

    uint32_t width;
    uint32_t height;

    uint32_t age = 0;

    StageProperties* assets;

    std::string tag;

    float frameTime_self = 0.0f;
    float frameTime_all = 0.0f;

public:

    explicit Stage(uint32_t width, uint32_t height, StageProperties* assets, bool HDR = false);
    virtual ~Stage();

    Stage(const Stage& o) = delete;
    Stage(const Stage&& o) = delete;
    Stage& operator=(const Stage& o) = delete;
    Stage& operator=(const Stage&& o) = delete;

    void render(uint32_t newAge);

    /**
        @brief call for custom while loop. don't call it in any opencv callback (like: mouseCallback)
    */
    int show(const char* windowName) const;

    /**
        @brief call for opencv callback.
    */
    void applyAndShow(const char* windowName) const;

    GPUMat* getGPUMat();
    const GPUMat* getGPUMat() const;

    float realFrameTime() const;
    float treeFrameTime() const;

private:
    void createShader();
    void createPipelineLayout();
    void buildRenderPass();
    void createFramebuffer();
    void buildPipeline();
    void buildUniform();
    void updateUniform();
    void writeUniform();
    void createEtc();
    void cleanup();
};

void enableUnifromTransfer();
void disableUnifromTransfer();

void enableMeshTransfer();
void disableMeshTransfer();

}

#endif