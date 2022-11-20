#include "helper.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

const bool blur = true;

int main()
{
    cv::Mat input = cv::imread(MLTSG_PATH("/images/PinkPig.jpg"));

    cv::Mat gray(input.size(), CV_8UC1);

    mltsg::multiProcess<MLTSG_U8, 32>(gray, [&](glm::vec2 uv) {
        glm::vec4 col = mltsg::texelFetch<MLTSG_U8>(input, uv);
        return glm::vec4(glm::vec3(glm::dot(mltsg::_xyz(col), glm::vec3(.3f, .6f, .1f))), 1.f);
    });

    // gray = input;

    cv::imshow("Input", gray);

    const int gaussionSize = 3;
    const float theta = 0.8f;
    float gaussian[gaussionSize];
    for (size_t i = 0; i < gaussionSize; ++i)
    {
        gaussian[i] = glm::exp(-.5f * i * i / theta / theta) / theta / glm::sqrt(2.f * glm::atan(0.f, -1.f));
    }

    for (const auto& it : gaussian)
    {
        mltsg::Log("%f\n", it);
    }

    if (blur)
    {
        cv::Mat pingpong(gray.size(), gray.type());
        bool HV = false;
        cv::Mat* toGaussion;
        auto&& gaussionFilter = [&](glm::vec2 uv) {
            glm::vec4 v(0.f);
            float base = 0.f;
            for (int u = -gaussionSize; u <= gaussionSize; ++u)
            {
                glm::vec2 offset = (HV ? glm::vec2(1.f, 0.f) : glm::vec2(0.f, 1.f)) * (float)u / glm::vec2(gray.cols, gray.rows);
                float p = gaussian[abs(u)];
                v += mltsg::texelFetch<MLTSG_U8>(*toGaussion, uv + offset) * p;
                base += p;
            }
            return v / base;
        };
        HV = true;
        toGaussion = &gray;
        mltsg::multiProcess<MLTSG_U8, 32>(pingpong, gaussionFilter);
        HV = false;
        toGaussion = &pingpong;
        mltsg::multiProcess<MLTSG_U8, 32>(gray, gaussionFilter);
    }

    cv::Mat sobelRes0;
    cv::Mat sobelRes1;
    cv::Mat sobelResMerged(gray.size(), gray.type());

    cv::Sobel(gray, sobelRes0, CV_16SC1, 1, 0);
    cv::Sobel(gray, sobelRes1, CV_16SC1, 0, 1);

    auto&& scaleToAbs = [&](glm::vec2 uv) {
        glm::vec4 col0 = mltsg::texelFetch<int16_t, 255>(sobelRes0, uv);
        glm::vec4 col1 = mltsg::texelFetch<int16_t, 255>(sobelRes1, uv);
        return .8f * glm::sqrt(glm::pow(col0, glm::vec4(2.f)) + glm::pow(col1, glm::vec4(2.f)));
    };
    mltsg::multiProcess<MLTSG_U8, 32>(sobelResMerged, scaleToAbs);

    cv::imshow("Result", sobelResMerged);

    cv::Mat gradient(gray.size(), CV_8UC3);
    mltsg::multiProcess<MLTSG_U8, 32>(gradient, [&](glm::vec2 uv) {
        float gx = mltsg::texelFetch<int16_t, 255>(sobelRes0, uv).x;
        float gy = mltsg::texelFetch<int16_t, 255>(sobelRes1, uv).x;
        float a = glm::atan(gy, gx);
        glm::vec2 res = glm::vec2(glm::cos(a), glm::sin(a));
        return glm::vec4(res * .5f + .5f, 0.f, 1.f);
    });
    cv::imshow("gradient", gradient);

    cv::Mat rawRes(gray.size(), gray.type());
    cv::Mat myRes(gray.size(), gray.type());
    mltsg::multiProcess<MLTSG_U8, 32>(rawRes, [&](glm::vec2 uv) {
        glm::vec2 dir = mltsg::texelFetch<MLTSG_U8>(gradient, uv);
        dir = dir * 2.f - 1.f;
        dir = dir / glm::vec2(gray.cols, gray.rows);
        float c = mltsg::sample<MLTSG_U8>(sobelResMerged, uv).r;
        float c0 = mltsg::sample<MLTSG_U8>(sobelResMerged, uv + dir).r;
        float c1 = mltsg::sample<MLTSG_U8>(sobelResMerged, uv - dir).r;
        if (c > c0 && c > c1)
        {
            if (c > .14f)
            {
                return glm::vec4(1.f);
            }
            else if (c > .05f)
            {
                return glm::vec4(.5f);
            }
        }
        return glm::vec4(0.f);
    });

    mltsg::multiProcess<MLTSG_U8, 32>(myRes, [&](glm::vec2 uv) {
        glm::vec4 c = mltsg::texelFetch<MLTSG_U8>(rawRes, uv);
        if (c.x < .1f) { return glm::vec4(0.f); }
        if (c.x > .6f) { return glm::vec4(1.f); }
        for (int u = -1; u <= 1; ++u)
        {
            for (int v = -1; v <= 1; ++v)
            {
                if (mltsg::texelFetch<MLTSG_U8>(rawRes, uv + glm::vec2(u, v) / glm::vec2(gray.cols, gray.rows)).x > .6f)
                {
                    return glm::vec4(.1f);
                }
            }
        }
        return glm::vec4(0.f);
    });

    cv::imshow("My Result", myRes);

    cv::Mat cannyRes;
    cv::Canny(input, cannyRes, 200., 50.);
    cv::imshow("canny", cannyRes);

    cv::waitKey();

    return 0;
}
