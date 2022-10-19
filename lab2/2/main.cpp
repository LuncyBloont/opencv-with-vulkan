#include <iostream>
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
    float biasMax;
};

int main()
{
    cv::Mat image = cv::imread("../08.jpg");
    cv::Mat background = cv::imread("../08_bg.jpg");
    
    assert(!image.empty());
    assert(!background.empty());

    cv::Mat output;
    output.create(image.size(), CV_8UC3);

    Data0 data0{ &image, &background, &output, static_cast<float>(image.cols) };

    auto&& onchange = [](int val, void* rawData0) {
        Data0* data0 = reinterpret_cast<Data0*>(rawData0);
        float bias = val / data0->biasMax;

        process<U8>(*data0->output, [&](vec2 uv) {
            vec3 raw = _rgb(sample<U8>(*data0->image, uv));
            vec3 bg = _rgb(sample<U8>(*data0->background, uv));
            return vec4(
                mix(vec3(0.0f), vec3(1.0f), sign(max(abs(raw - bg) - vec3(bias), vec3(0.0f)))),
                1.0f
            );
        });

        cv::imshow("Output", *data0->output);
    };

    cv::namedWindow("Input");
    cv::imshow("Input", image);
    
    cv::namedWindow("Background");
    cv::imshow("Background", background);

    cv::namedWindow("Output");
    int _tmp0;
    cv::createTrackbar("Bias", "Output", &_tmp0, static_cast<int>(data0.biasMax), onchange, &data0);
    onchange(_tmp0, &data0);

    cv::waitKey();

    return 0;
}