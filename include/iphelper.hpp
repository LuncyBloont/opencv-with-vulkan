#ifndef CVVK_IPHELPER_HPP
#define CVVK_IPHELPER_HPP

#include "glm/fwd.hpp"
#include "opencv2/core/mat.hpp"
#include <cstdio>
#include <sstream>
#include <stdint.h>
#include <string>
#include <glm/glm.hpp>
#include "helper.h"
#include "gpuMat.h"
#include "opencv2/highgui.hpp"
#include "stage.h"

namespace mltsg 
{

template <typename Int, int32_t Limit>
cv::Mat genHistMap(const cv::Mat& input, bool combineChannels)
{
    cv::Mat res;
    res.create(1, Limit, CV_32SC(input.channels()));
    memset(res.data, 0, res.elemSize() * res.total());

    float* ptr = res.ptr<float>(0);

    for (int r = 0; r < input.rows; ++r)
    {
        const Int* line = input.ptr<Int>(r);
        for (int c = 0; c < input.cols; ++c)
        {
            const Int* vals = line + c * input.channels();
            if (combineChannels)
            {
                int br = 0;
                for (int i = 0; i < input.channels(); ++i)
                {
                    br += int(vals[i]);
                }
                br /= input.channels();

                for (int i = 0; i < input.channels(); ++i)
                {
                    ptr[br * input.channels() + i] += 1.0f / float(input.cols * input.rows);
                }
            }
            else 
            {
                for (int i = 0; i < input.channels(); ++i)
                {
                    ptr[int(vals[i] * input.channels() + i)] += 1.0f / float(input.cols * input.rows);
                }
            }
        }
    }

    return res;
}

template <typename Int, int32_t Limit>
cv::Mat equalizeHist(const cv::Mat& input)
{
    cv::Mat res(cv::Size(Limit, 1), input.type(), cv::Scalar(1.0f, 1.0f, 1.0f, 1.0f));

    glm::vec4 s = glm::vec4(0.0f);
    float* ptr = res.ptr<float>(0);
    const float* iptr = input.ptr<float>(0);
    for (int c = 0; c < Limit; ++c)
    {
        for (int i = 0; i < input.channels(); ++i)
        {
            s[i] += iptr[c * input.channels() + i];
            ptr[c * input.channels() + i] = s[i];
        }
    }
    
    return res;
}

template <uint32_t CoreSize, typename Int, int32_t Scale, typename Type>
cv::Mat genSDF2D(const cv::Mat& input, Type solid, float threshold, float disScale = 0.001f, int time = 1)
{
    float core[CoreSize][CoreSize];

    for (int x = 0; x < CoreSize; ++x)
    {
        for (int y = 0; y < CoreSize; ++y)
        {
            core[x][y] = glm::length(glm::vec2(float(x), float(y))) * disScale;
        }
    }

    cv::Mat res;
    res.create(input.size(), input.type());

    multiProcess<Int, Scale, 32>(res, [&](glm::vec2 uv) {
        Type col = Type(texelFetch<Int, Scale>(input, uv));
        if (glm::distance(solid, col) < threshold)
        {
            return glm::vec4(0.0f);
        }
        return glm::vec4(1.0f);
    });

    Scaler scaler { input.cols, input.rows };
    ToUV toUV { input.cols, input.rows };

    bool route = true;

    const auto shader = [&](glm::vec2 uv) {
        glm::vec2 pos = scaler(uv);
        Type old = Type(texelFetch<Int, Scale>(res, uv));
        for (int x = 0; x < CoreSize; ++x)
        {
            for (int y = 0; y < CoreSize; ++y)
            {
                glm::vec2 smpUV = toUV(pos - (route ? 1.0f : -1.0f) * glm::vec2(float(x), float(y)));
                Type smp = texelFetch<Int, Scale>(res, smpUV);
                float dis = core[x][y];
                old = glm::min(old, smp + dis);
            }
        }
        return glm::vec4(old.x);
    };

    for (int t = 0; t < time; ++t)
    {
        route = true;
        process<Int, Scale>(res, shader);
        route = false;
        process<Int, Scale, ProcessRoute::BB>(res, shader);
    }
    
    return res;
}

template <typename Int, int32_t Scale, typename Type>
cv::Mat genSDF2D_gpu(const cv::Mat& input, Type solid, float threshold, float disScale = 0.001f, int box = 9)
{
    int time = glm::min(Scale, glm::max(input.cols, input.rows)) / (box * 2 + 1);
    cv::Mat res;
    res.create(input.size(), input.type());

    multiProcess<Int, Scale, 32>(res, [&](glm::vec2 uv) {
        Type col = Type(texelFetch<Int, Scale>(input, uv));
        if (glm::distance(solid, col) < threshold)
        {
            return glm::vec4(0.0f);
        }
        return glm::vec4(1.0f);
    });

    bool HDR = Scale != 255;

    mltsg::GPUMat gm{ &res, MLTSG_READ_MAT, false, MLTSG_USE_RAW, HDR };
    gm.apply();

    mltsg::StageProperties assets{
        {}, { &gm }, {}, { glm::vec4(float(box), disScale, 0.0f, 0.0f) }, 
        MLTSG_PATH("/shaders/sdf.spv")
    };

    mltsg::Stage stage{ gm.width(), gm.height(), &assets, HDR };
    assets.reference[0] = &stage;

    float preScale = 1.0f / 255.0f;

    for (int age = 1; age < 1 + time; ++age)
    {
        assets.uniVec[0].y = (age == time ? disScale : glm::max(1.0f / 255.0f, disScale));
        assets.uniVec[0].z = preScale;
        stage.render(age);
        preScale = assets.uniVec[0].y;
        if (0)
        {
            stage.applyAndShow("O");
            cv::waitKey();
            cv::imwrite(MLTSG_PATH("/images/IGN_sdf.png"), *stage.getGPUMat()->cpuData);
        }
    }

    stage.getGPUMat()->apply();

    memcpy_s(res.data, res.elemSize() * res.cols * res.rows, stage.getGPUMat()->cpuData->data, res.elemSize() * res.cols * res.rows);

    return res;
}

}

#endif // CVVK_IPHELPER_HPP