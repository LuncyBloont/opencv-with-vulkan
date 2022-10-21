#pragma once

#include "glm/fwd.hpp"
#include "gpuMat.h"
#include "opencv2/core/mat.hpp"
#include "vulkan/vulkan_core.h"
#include <array>
#include <stdint.h>
#include <vector>

class Stage
{
private:
    GPUMat frame;
    cv::Mat Data;

    VkFramebuffer frameBuffer;

    VkRenderPass renderPass;
    VkPipeline pipeline;

    uint32_t width;
    uint32_t height;

    std::array<Stage*, 8> refeance;
    std::array<GPUMat*, 8> textures;

    std::array<glm::mat4x4, 8> uniMat;
    std::array<glm::vec4, 16> uniVec;

    uint32_t age = 0;

public:

    Stage(uint32_t width, uint32_t height, 
        const std::array<Stage*, 8>& refeance,
        const std::array<GPUMat*, 8>& textures,
        const std::array<glm::mat4x4, 8>& uniMat,
        const std::array<glm::vec4, 16>& uniVec);
    ~Stage();

    Stage(const Stage& o) = delete;
    Stage(const Stage&& o) = delete;
    Stage& operator=(const Stage& o) = delete;
    Stage& operator=(const Stage&& o) = delete;

    void render(uint32_t age);

    void show(const char* windowName) const;
};