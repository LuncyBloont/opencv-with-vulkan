#pragma once

#include "helper.h"
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <stdint.h>

#define U32 uint32_t

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
            LogErr("Try call vulkan function error...\n");
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
