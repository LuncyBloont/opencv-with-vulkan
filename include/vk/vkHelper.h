#pragma once

#include <cstdint>
#include <iostream>
#include <stdexcept>

#define U32 uint32_t

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
