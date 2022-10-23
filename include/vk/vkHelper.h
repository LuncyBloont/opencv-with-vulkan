#pragma once

#include "glm/common.hpp"
#include "vulkan/vulkan_core.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <string>

#define U32 uint32_t

#define MAX_SHADER_SIZE (1024 * 1024 * 10)

template<typename T>
struct Try
{
    const T tmp;

    Try(const T& t) : tmp(t) {}

    inline Try& operator=(const T&& t) 
    { 
        if (t != tmp)
        {
            std::cerr << "\033[31mtry something error\033[0m\n";
            throw std::runtime_error("try error");
        }
        return *this;
    }
};

template<typename T>
Try<T> trydo(const T& t)
{
    return Try<T>{t};
}

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
