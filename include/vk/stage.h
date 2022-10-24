#pragma once

#include "glm/fwd.hpp"
#include "gpuBuf.h"
#include "gpuMat.h"
#include "opencv2/core/mat.hpp"
#include "vulkan/vulkan_core.h"
#include <array>
#include <stdint.h>
#include <string>
#include <vector>

extern GPUBuffer* uniformSrcBuffer;

extern GPUBuffer* meshSrcBuffer;

class Stage;

struct StageProperties
{
    std::array<Stage*, 3> reference;
    std::array<GPUMat*, 3> textures;

    std::array<glm::mat4x4, 8> uniMat;   
    std::array<glm::vec4, 8> uniVec; // custom vec4 x 8
/* 
system vec4 x 8:
0 to 2: reference[0 to 2] info { width, height, mipmapLevel, 0.0 }    
3 to 5: textures[0 to 2] info { width, height, mipmapLevel, 0.0 }   
6: time { s, 1/2s, ms, 1/2ms }
7: 
*/

    const std::string shaderPath;
    
    const std::string customVertexShader = "../defaultVS/screenRect.spv";
};

struct DefaultUniform
{
    alignas(16) glm::mat4 matrix[8];
    alignas(16) glm::vec4 vector[16];
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

public:

    explicit Stage(uint32_t width, uint32_t height, StageProperties* assets);
    virtual ~Stage();

    Stage(const Stage& o) = delete;
    Stage(const Stage&& o) = delete;
    Stage& operator=(const Stage& o) = delete;
    Stage& operator=(const Stage&& o) = delete;

    void render(uint32_t newAge);
    void show(const char* windowName) const;

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