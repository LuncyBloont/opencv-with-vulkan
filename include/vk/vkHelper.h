#ifndef CVVK_VK_VKHELPER_H
#define CVVK_VK_VKHELPER_H

#include "helper.h"
#include "glm/common.hpp"
#include "vulkan/vulkan_core.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <string>

namespace mltsg 
{

#define MLTSG_U32 uint32_t

#define MLTSG_MAX_SHADER_SIZE (1024 * 1024 * 40)

template<typename T>
struct Try
{
    const T tmp;
    const char* filename;
    const char* function;
    const uint32_t line;

    Try(const T& t, const char* file, const char* func, const uint32_t line) :
        tmp(t), filename(file), function(func), line(line) 
    {}

    inline const Try& operator=(const T&& t) const
    { 
        if (t != tmp)
        {
            mltsg::LogErr("Try call vulkan function error...\n");
            throw std::runtime_error("try error");
        }
        return *this;
    }
};

template <typename T>
const Try<T> __trydo__(const T& t, const char* file, const char* func, const uint32_t line)
{
    return Try<T>(t, file, func, line);
}

#define trydo(t) __trydo__(t, __FILE__, __FUNCTION__, __LINE__)

inline uint32_t mipLevel(uint32_t width, uint32_t height)
{
    uint32_t longedge = glm::max(width, height);
    uint32_t level = 0;
    while (longedge) {
        level += 1;
        longedge = longedge >> 1;
    }

    return level;
}

inline uint32_t toMipmapSize(uint32_t size, uint32_t level)
{
    size = size >> level;
    return size ? size : 1;
}

void readShader(VkShaderModule& shader, std::string fname);

struct GPUMat;

void showMipmap(const GPUMat* mat);
void showMipmap(const std::vector<cv::Mat>* maps, bool HDR);

}

#endif