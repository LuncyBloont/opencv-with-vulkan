#include <cmath>
#include <iostream>
#include <stdint.h>
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glslStyle.hpp"
#include "helper.h"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/matx.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "shader.h"

constexpr int K = 255 * 2200000; 

int main()
{
    cv::Mat input = cv::imread("../bb.png");

    cv::Mat integral;
    integral.create(input.size(), CV_32SC3);

    cv::Mat output;
    output.create(input.size(), CV_8UC3);

    /* for (int i = 0; i < input.rows; ++i)
    {
        uint8_t* rd = input.ptr(i);
        int32_t* wt = integral.ptr<int32_t>(i);
        int32_t* pwt = i > 0 ? integral.ptr<int32_t>(i - 1) : nullptr;
        for (int j = 0; j < input.cols; ++j)
        {
            for (int c = 0; c < integral.channels(); ++c)
            {
                wt[j * integral.channels() + c] = 
                    rd[j * input.channels() + c] + 
                    (j > 0 ? wt[(j - 1) * integral.channels() + c] : 0) +
                    (pwt ? pwt[j * integral.channels() + c] : 0) - 
                    (i > 0 && j > 0 ? pwt[(j - 1) * integral.channels() + c] : 0);
            }
        }
    } */

    float filterSize = 32.0f;

    markTime();

    process<int32_t, K>(integral, [&](glm::vec2 uv) {
        glm::vec3 c = _rgb(texelFetch<uint8_t, 255>(input, uv)) * float(255.0f / K);
        glm::vec3 cu = uv.y > 0.5f / input.rows ? 
            _rgb(texelFetch<int32_t, K>(integral, uv - glm::vec2(0.0f, 1.0f / input.rows))) : 
            glm::vec3(0.0f);
        glm::vec3 cl = uv.x > 0.5f / input.cols ? 
            _rgb(texelFetch<int32_t, K>(integral, uv - glm::vec2(1.0f / input.cols, 0.0f))) : 
            glm::vec3(0.0f);
        glm::vec3 cp = (uv.y > 0.5f / input.rows && uv.x > 0.5f / input.cols) ? 
            _rgb(texelFetch<int32_t, K>(integral, uv - glm::vec2(1.0f / input.cols, 1.0f / input.rows))) : 
            glm::vec3(0.0f);
        
        return glm::vec4(c + cu + cl - cp, 1.0f);
    });

    multiProcess<uint8_t, 255, 32>(output, [&](glm::vec2 uv) {
        glm::vec2 offsetScale = glm::vec2(1.0f / input.cols, 1.0f / input.rows);
        glm::vec2 offset = glm::vec2(1.0f, -1.0f);

        glm::vec2 realArea = glm::clamp(uv + filterSize * offsetScale * _xx(offset), 0.0f, 1.0f) - 
            glm::clamp(uv + filterSize * offsetScale * _yy(offset), 0.0f, 1.0f);
        realArea *= glm::vec2(input.cols, input.rows);

        glm::vec3 t11 = _rgb(texelFetch<int32_t, K>(integral, uv + filterSize * offsetScale * _xx(offset), SampleUV::Clamp));
        glm::vec3 t00 = _rgb(texelFetch<int32_t, K>(integral, uv + filterSize * offsetScale * _yy(offset), SampleUV::Clamp));
        glm::vec3 t01 = _rgb(texelFetch<int32_t, K>(integral, uv + filterSize * offsetScale * _yx(offset), SampleUV::Clamp));
        glm::vec3 t10 = _rgb(texelFetch<int32_t, K>(integral, uv + filterSize * offsetScale * _xy(offset), SampleUV::Clamp));

        return glm::vec4((t11 - t10 - t01 + t00) * float(K) / 255.0f / realArea.x / realArea.y, 1.0f);
    });

    endMark("积分图均值滤波用时：%f秒\n");

    cv::Mat output2;
    output2.create(input.size(), CV_8UC3);

    markTime();

    multiProcess<uint8_t, 255, 32>(output2, [&](glm::vec2 uv) {
        glm::vec3 col{ 0.0f };
        float base = 0.0f;
        for (float i = -filterSize; i < filterSize; i += 1.0f)
        {
            for (float j = -filterSize; j < filterSize; j += 1.0f)
            {
                glm::vec2 offset = glm::vec2(i / input.cols, j / input.rows);
                col += _rgb(texelFetch<uint8_t, 255>(input, uv + offset, SampleUV::Clamp));
                base += 1.0f;
            }
        }

        return glm::vec4(col / base, 1.0f);
    });

    endMark("普通均值滤波用时：%f秒\n");

    markTime();

    cv::Mat output3;
    output3.create(input.size(), CV_8UC3);
    cv::boxFilter(input, output3, -1, cv::Size(filterSize * 2, filterSize * 2));

    endMark("OpenCV boxFilter用时：%f秒\n");

    cv::imshow("Input", input); 
    cv::imshow("Output: 积分图均值滤波", output);
    cv::imshow("Output2: 普通均值滤波", output2);
    cv::imshow("Output3: boxFilter均值滤波", output3);

    cv::waitKey();

    return 0;
}