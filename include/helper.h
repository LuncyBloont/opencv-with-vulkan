#pragma once

#include "glm/glm.hpp"

#define MULTI_PASS(times, _src, _dst, resultPtr, ...) { for (int i##times = 0; i##times < times; ++i##times) \
    { \
        cv::Mat* src = i##times % 2 == 0 ? _src : _dst; \
        cv::Mat* dst = i##times % 2 == 1 ? _src : _dst; \
        __VA_ARGS__ \
    } \
    resultPtr = (times + 2 - 1) % 2 == 1 ? _src : _dst; \
}

void markTime();
void endMark(const char* msg);

float areaOfTriangle(glm::vec2 A, glm::vec2 B, glm::vec2 C);
float disToLine(glm::vec2 p, glm::vec2 A, glm::vec2 B);

#define U8 uint8_t, 255
