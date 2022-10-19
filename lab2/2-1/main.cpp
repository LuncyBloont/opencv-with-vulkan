#include <iostream>
#include "glm/common.hpp"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "shader.h"
#include "glm/glm.hpp"
#include "opencv2/core.hpp"

using namespace glm;

struct Data0
{
    cv::Mat* image;
    cv::Mat* background;
    cv::Mat* output;
    cv::Mat* tmp0;
    cv::Mat* tmp1;
    cv::Mat* tmp2;
    cv::Mat* tmp3;
    float biasMax;
};

template <length_t L>
vec<L, float> sigmoid(vec<L, float> x, vec<L, float> f)
{
    auto&& raw = [&](vec<L, float> x_, vec<L, float> f_) {
        vec<L, float> x__ = (x_ - 0.5f) * f_;
        return 1.0f / (1.0f + pow(vec<L, float>(2.71828f), -6.0f * x__));
    };

    return (raw(x, f) - 0.5f) * 0.5f / (raw(vec<L, float>(1.0f), f) - 0.5f) + 0.5f;
}

int main()
{
    cv::Mat image = cv::imread("../07.jpg");
    cv::Mat background = cv::imread("../07_bg.jpg");
    
    assert(!image.empty());
    assert(!background.empty());

    cv::Mat output;
    output.create(image.size(), CV_8UC3);

    cv::Mat tmp0;
    tmp0.create(image.size(), CV_8UC3);
    cv::Mat tmp1;
    tmp1.create(image.size(), CV_8UC3);
    cv::Mat tmp2;
    tmp2.create(image.size(), CV_8UC3);
    cv::Mat tmp3;
    tmp3.create(image.size(), CV_8UC3);

    Data0 data0{ &image, &background, &output, &tmp0, &tmp1, &tmp2, &tmp3, static_cast<float>(image.cols) };

    auto&& onchange = [](int val, void* rawData0) {
        Data0* data0 = reinterpret_cast<Data0*>(rawData0);
        float bias = val / data0->biasMax;

        cv::Mat* bgImg = data0->background;
        cv::Mat* fgImg = data0->image;
        auto&& mask = [&](vec2 uv) {
            vec3 raw = _rgb(sample<U8>(*fgImg, uv));
            vec3 bg = _rgb(sample<U8>(*bgImg, uv));
            return vec4(
                mix(vec3(0.0f), vec3(1.0f), sign(max(dot(abs(raw - bg), vec3(1.0f)) / 3.0f - vec3(bias), vec3(0.0f)))),
                1.0f
            );
        };

        cv::Mat* toBlur = data0->image;
        auto&& edgeBlur = [&](vec2 uv) {
            vec3 col(0.0f);
            float base = 0.0f;
            vec3 ct = _rgb(sample<U8>(*toBlur, uv, SampleUV::Clamp, SamplePoint::Point));
            const float size = 3.0f;
            for (float ddx = -size; ddx <= size + 0.1f; ddx += 1.0f)
            {
                for (float ddy = -size; ddy <= size + 0.1f; ddy += 1.0f)
                {
                    vec2 offset = vec2(ddx, ddy);
                    vec3 smp = _rgb(sample<U8>(*toBlur, uv + offset / vec2(toBlur->cols, toBlur->rows),
                        SampleUV::Clamp, SamplePoint::Point));

                    float p = 1.0f; // cos(length(offset) * 3.1415926f / size / pow(2.0f, 0.5f)) + 1.0f;
                    float diff = pow(dot(abs(smp - ct), vec3(1.0f)) / 3.0f, 0.05f);
                    p *= 1.0f - diff;
                    
                    col += smp * p;
                    base += p;
                }
            }
            return vec4(col / base, 1.0f);
        };

        cv::Mat* toCopy = data0->tmp0;
        auto&& copy = [&](vec2 uv) {
            return sample<U8>(*toCopy, uv, SampleUV::Repeat, SamplePoint::Point);
        };

        toCopy = data0->image;
        process<U8>(*data0->tmp0, copy);

        for (int i = 0; i < 4; ++i)
        {
            toBlur = i % 2 == 0 ? data0->tmp0 : data0->tmp1;
            process<U8>(i % 2 == 1 ? *data0->tmp0 : *data0->tmp1, edgeBlur);
        }

        toCopy = data0->background;
        process<U8>(*data0->tmp2, copy);

        for (int i = 0; i < 4; ++i)
        {
            toBlur = i % 2 == 0 ? data0->tmp2 : data0->tmp3;
            process<U8>(i % 2 == 1 ? *data0->tmp2 : *data0->tmp3, edgeBlur);
        }

        bgImg = data0->tmp3;
        fgImg = data0->tmp1;
        process<U8>(*data0->output, mask);

        bgImg = data0->background;
        fgImg = data0->image;
        process<U8>(*data0->tmp0, mask);

        cv::imshow("OutputF", *data0->tmp1);
        cv::imshow("OutputB", *data0->tmp3);
        cv::imshow("Output", *data0->output);
        cv::imshow("OutputOld", *data0->tmp0);
    };

    cv::namedWindow("Input");
    cv::imshow("Input", image);
    
    cv::namedWindow("Background");
    cv::imshow("Background", background);

    cv::namedWindow("Output");
    cv::namedWindow("OutputOld");
    cv::namedWindow("OutputF");
    cv::namedWindow("OutputB");
    int _tmp0 = 1 * static_cast<int>(data0.biasMax) / 10;
    cv::createTrackbar("Bias", "Output", &_tmp0, static_cast<int>(data0.biasMax), onchange, &data0);
    onchange(_tmp0, &data0);

    cv::waitKey();

    return 0;
}