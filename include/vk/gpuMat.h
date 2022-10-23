#pragma once

#include "gpuMat.h"
#include "opencv2/core/mat.hpp"
#include "shader.h"
#include "vulkan/vulkan_core.h"
#include "vkinfo.h"
#include <stdint.h>
#include <glm/glm.hpp>
#include <vector>

#define READ_MAT true
#define WRITE_MAT false
#define USE_SRGB true
#define USE_RAW false

struct GSampler 
{
    VkSampler sampler;
    SampleUV uvType;
    SamplePoint filterType;

    explicit GSampler(SampleUV uvType, SamplePoint filterType);
    virtual ~GSampler();

    GSampler(const GSampler& other) = delete;
    GSampler(const GSampler&& other) = delete;
    GSampler& operator=(const GSampler& other) = delete;
    GSampler& operator=(const GSampler&& other) = delete;
};

extern GSampler* defaultLinearSampler;

struct GPUMat
{
    VkImage image;
    VkImageView view;
    VkMemoryRequirements memoryRequirements;
    VkDeviceSize memory;
    cv::Mat* cpuData;
    std::vector<cv::Mat> mipmaps;
    bool readable;
    bool srgb;
    GSampler* sampler = defaultLinearSampler;
    uint32_t levels;

    VkFormat format;
    
    explicit GPUMat(cv::Mat* mat, bool readable = READ_MAT, bool genMip = true, bool srgb = USE_RAW);
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

void enableImageTransferBuffer();
void disableImageTransferBuffer();

