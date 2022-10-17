#pragma once

#include "opencv2/core/mat.hpp"
#include "vulkan/vulkan_core.h"
#include "vkinfo.h"

struct GPUMat
{
    VkImage image;
    VkImageView view;
    VkMemoryRequirements memoryRequirements;
    uint32_t memory;
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

void createMatC4(cv::Mat& dst, const cv::Mat& src);

