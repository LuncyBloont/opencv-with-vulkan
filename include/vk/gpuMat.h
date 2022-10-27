#ifndef CVVK_VK_GPUMAT_H
#define CVVK_VK_GPUMAT_H

#include "helper.h"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "shader.h"
#include "vulkan/vulkan_core.h"
#include "vkinfo.h"
#include <stdexcept>
#include <stdint.h>
#include <glm/glm.hpp>
#include <vector>

#define READ_MAT true
#define WRITE_MAT false
#define USE_SRGB true
#define USE_RAW false

#define HDR_MAX (255 * 2200000)

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
    bool HDR;

    VkFormat format;
    
    explicit GPUMat(cv::Mat* mat, bool readable = READ_MAT, bool genMip = true, bool srgb = USE_RAW, bool HDR = false);
    virtual ~GPUMat();

    void apply();

    GPUMat(const GPUMat&) = delete;
    GPUMat(const GPUMat&&) = delete;
    GPUMat& operator =(const GPUMat&) = delete;
    GPUMat& operator =(const GPUMat&&) = delete;

    uint32_t width() const;
    uint32_t height() const;
};

template <typename Int, int32_t MAX>
void createMatC4(cv::Mat& dst, const cv::Mat& src)
{
    int type = CV_8UC4;
    switch (src.type()) {
        case CV_8UC1:
        case CV_8UC2:
        case CV_8UC3:
        case CV_8UC4:
            type = CV_8UC4;
            break;
        case CV_16UC1:
        case CV_16UC2:
        case CV_16UC3:
        case CV_16UC4:
            type = CV_16UC4;
            break;
        case CV_32FC1:
        case CV_32FC2:
        case CV_32FC3:
        case CV_32FC4:
            type = CV_32FC4;
            break;
        case CV_32SC1:
        case CV_32SC2:
        case CV_32SC3:
        case CV_32SC4:
            type = CV_32SC4;
            break;
        default:
            LogErr("Unknown type\n");
            throw std::runtime_error("unknown type");
    }
    dst.create(src.size(), type);
    multiProcess<Int, MAX, 32>(dst, [&](glm::vec2 uv) {
        return glm::vec4(_rgb(sample<Int, MAX>(src, uv, SampleUV::Clamp, SamplePoint::Point)), 1.0f);
    });
}

void enableImageTransferBuffer();
void disableImageTransferBuffer();

#endif