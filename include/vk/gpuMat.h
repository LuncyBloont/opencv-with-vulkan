#pragma once

#include "opencv2/core/mat.hpp"
#include "shader.h"
#include "vulkan/vulkan_core.h"
#include "vkinfo.h"
#include <stdint.h>
#include <glm/glm.hpp>

struct GPUMat
{
    VkImage image;
    VkImageView view;
    VkMemoryRequirements memoryRequirements;
    VkDeviceSize memory;
    cv::Mat* cpuData;
    bool readable;
    
    explicit GPUMat(cv::Mat* mat, bool readable = false);
    virtual ~GPUMat();

    void apply();

    GPUMat(const GPUMat&) = delete;
    GPUMat(const GPUMat&&) = delete;
    GPUMat& operator =(const GPUMat&) = delete;
    GPUMat& operator =(const GPUMat&&) = delete;
};

template <typename Int, int32_t MAX>
void createMatC4(cv::Mat& dst, const cv::Mat& src)
{
    dst.create(src.size(), CV_8UC4);
    multiProcess<Int, MAX, 32>(dst, [&](glm::vec2 uv) {
        return glm::vec4(_rgb(sample<Int, MAX>(src, uv, SampleUV::Clamp, SamplePoint::Point)), 1.0f);
    });
}

