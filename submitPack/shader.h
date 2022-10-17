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
    Repeat
};

enum class SamplePoint
{
    Point,
    Linear
};

glm::vec4 getPixel(const cv::Mat& img, int x, int y, SampleUV uvtype);

glm::vec4 sample(const cv::Mat& img, glm::vec2 uv, 
    SampleUV uvtype = SampleUV::Repeat, SamplePoint pointtype = SamplePoint::Linear);


template <typename Shader>
void unitDo(int r0, int r1, int c0, int c1, cv::Mat* img, const Shader* shader)
{
    for (int i = r0; i < r1; ++i)
    {
        uchar* row = img->ptr(i);
        for (int j = c0; j < c1; ++j)
        {
            glm::vec2 uv = glm::vec2(float(j + 0.5f) / img->cols, float(i + 0.5f) / img->rows);
            glm::vec4 col = (*shader)(uv);
            for (int c = 0; c < img->channels(); ++c)
            {
                row[j * img->channels() + c] = static_cast<uint8_t>(glm::clamp(col[c], 0.0f, 1.0f) * 255.0f);
            }
        }
    }
}

template <int THREAD_HOLD, typename Shader>
void multiProcess(cv::Mat& img, const Shader& shader)
{
    std::vector<std::thread*> threadGroup;

    for (int i = 0; i < img.rows; i += THREAD_HOLD)
    {
        int r0 = i;
        int r1 = std::min(img.rows, i + THREAD_HOLD);
        int c0 = 0;
        int c1 = img.cols;
        std::thread* t = new std::thread(unitDo<Shader>, r0, r1, c0, c1, &img, &shader);
        threadGroup.push_back(t);
    }

    for (int i = 0; i < threadGroup.size(); ++i)
    {
        threadGroup[i]->join();
        delete threadGroup[i];
    }
}

template <typename Shader>
void process(cv::Mat& img, const Shader& shader)
{
    for (int i = 0; i < img.rows; ++i)
    {
        uchar* row = img.ptr(i);
        for (int j = 0; j < img.cols; ++j)
        {
            glm::vec2 uv = glm::vec2(float(j + 0.5f) / img.cols, float(i + 0.5f) / img.rows);
            glm::vec4 col = shader(uv);
            for (int c = 0; c < img.channels(); ++c)
            {
                row[j * img.channels() + c] = static_cast<uint8_t>(glm::clamp(col[c], 0.0f, 1.0f) * 255.0f);
            }
        }
    }
}

#include "glslStyle.hpp"
#include "helper.h"
