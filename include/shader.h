#pragma once

#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "shader.h"
#include <glm/glm.hpp>
#include <opencv2/core.hpp>
#include <stdint.h>
#include <sys/stat.h>
#include <thread>
#include <vector>

enum class SampleUV
{
    Clamp,
    Repeat,
    Mirror
};

enum class SamplePoint
{
    Point,
    Linear
};

template <typename Int, int32_t MAX> 
glm::vec4 getPixel(const cv::Mat& img, int x, int y, SampleUV uvtype)
{
    float limit = float(MAX);
    switch (uvtype) {
        case SampleUV::Repeat:
            x = (x % img.cols + img.cols) % img.cols;
            y = (y % img.rows + img.rows) % img.rows;
            break;
        case SampleUV::Clamp:
            x = glm::clamp(x, 0, img.cols - 1);
            y = glm::clamp(y, 0, img.rows - 1);
            break;
        case SampleUV::Mirror:
            x = (x % (2 * img.cols) + (2 * img.cols)) % (2 * img.cols);
            y = (y % (2 * img.rows) + (2 * img.rows)) % (2 * img.rows);
            x = x >= img.cols ? 2 * img.cols - x - 1 : x;
            y = y >= img.rows ? 2 * img.rows - y - 1 : y;
            break;
    }

    glm::vec4 res(0.0f, 0.0f, 0.0f, 1.0f);
    const Int* p = img.ptr<Int>(y) + x * img.channels();

    if (img.channels() >= 1)
    {
        res.x = p[0] / limit;
    }
    if (img.channels() >= 2)
    {
        res.y = p[1] / limit;
    }
    if (img.channels() >= 3)
    {
        res.z = p[2] / limit;
    }
    if (img.channels() >= 4)
    {
        res.w = p[3] / limit;
    }
    return res;
}

template <typename Int, int32_t MAX>
glm::vec4 sample(const cv::Mat& img, glm::vec2 uv, 
    SampleUV uvtype = SampleUV::Repeat, SamplePoint pointtype = SamplePoint::Linear)
{

    glm::vec2 near = glm::floor(uv * glm::vec2(img.cols, img.rows));
    int x = int(near.x);
    int y = int(near.y);

    if (pointtype == SamplePoint::Point)
    {
        return getPixel<Int, MAX>(img, x, y, uvtype);
    }
    
    glm::vec2 offset = glm::fract(uv * glm::vec2(img.cols, img.rows));
    return glm::mix(
        glm::mix(getPixel<Int, MAX>(img, x, y, uvtype), getPixel<Int, MAX>(img, x + 1, y, uvtype), offset.x), 
        glm::mix(getPixel<Int, MAX>(img, x, y + 1, uvtype), getPixel<Int, MAX>(img, x + 1, y + 1, uvtype), offset.x), offset.y);
}

template <typename Int, int32_t MAX>
glm::vec4 texelFetch(const cv::Mat& img, glm::vec2 uv, SampleUV uvtype = SampleUV::Repeat)
{
    glm::vec2 near = glm::floor(uv * glm::vec2(img.cols, img.rows));
    int x = int(near.x);
    int y = int(near.y);

    return getPixel<Int, MAX>(img, x, y, uvtype);
}

template <typename Int, int32_t MAX, typename Shader>
void unitDo(int r0, int r1, int c0, int c1, cv::Mat* img, const Shader* shader)
{
    float limit = float(MAX);
    for (int i = r0; i < r1; ++i)
    {
        Int* row = img->ptr<Int>(i);
        for (int j = c0; j < c1; ++j)
        {
            glm::vec2 uv = glm::vec2(float(j + 0.5f) / img->cols, float(i + 0.5f) / img->rows);
            glm::vec4 col = (*shader)(uv);
            for (int c = 0; c < img->channels(); ++c)
            {
                row[j * img->channels() + c] = static_cast<Int>(glm::clamp(col[c], 0.0f, 1.0f) * limit);
            }
        }
    }
}

template <typename Int, int32_t MAX, int THREAD_HOLD, typename Shader>
void multiProcess(cv::Mat& img, const Shader& shader)
{
    std::vector<std::thread*> threadGroup;

    for (int i = 0; i < img.rows; i += THREAD_HOLD)
    {
        int r0 = i;
        int r1 = std::min(img.rows, i + THREAD_HOLD);
        int c0 = 0;
        int c1 = img.cols;
        std::thread* t = new std::thread(unitDo<Int, MAX, Shader>, r0, r1, c0, c1, &img, &shader);
        threadGroup.push_back(t);
    }

    for (int i = 0; i < threadGroup.size(); ++i)
    {
        threadGroup[i]->join();
        delete threadGroup[i];
    }
}

template <typename Int, int32_t MAX, typename Shader>
void process(cv::Mat& img, const Shader& shader)
{
    float limit = float(MAX);
    for (int i = 0; i < img.rows; ++i)
    {
        Int* row = img.ptr<Int>(i);
        for (int j = 0; j < img.cols; ++j)
        {
            glm::vec2 uv = glm::vec2(float(j + 0.5f) / img.cols, float(i + 0.5f) / img.rows);
            glm::vec4 col = shader(uv);
            for (int c = 0; c < img.channels(); ++c)
            {
                row[j * img.channels() + c] = static_cast<Int>(glm::clamp(col[c], 0.0f, 1.0f) * limit);
            }
        }
    }
}

#include "glslStyle.hpp"
#include "helper.h"
