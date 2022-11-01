#include <iostream>
#include "glm/detail/qualifier.hpp"
#include "glm/fwd.hpp"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "shader.h"
#include "opencv2/core.hpp"

using namespace glm;

using namespace mltsg;

struct UserData0
{
    cv::Mat* input;
    cv::Mat* output;
    float tmax;
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
    cv::Mat image = cv::imread("../images/dd.png");
    assert(!image.empty());
    cv::namedWindow("Input");
    cv::imshow("Input", image);

    cv::Mat output;
    output.create(image.size().height, image.size().width, CV_8UC3);

    cv::namedWindow("Output");

    float trackMax = image.cols;

    UserData0 data0 = UserData0{ &image, &output, trackMax };

    auto&& onchange = [](int val, void* data) {
        cv::Mat* output = reinterpret_cast<UserData0*>(data)->output;
        cv::Mat* image = reinterpret_cast<UserData0*>(data)->input;

        process<MLTSG_U8>(*output, [&](vec2 uv) {
            vec3 col = _xyz(sample<MLTSG_U8>(*image, uv));

            col = sigmoid(col, glm::vec3(val / reinterpret_cast<UserData0*>(data)->tmax) * 4.0f + 0.0001f);

            return glm::vec4(col, 1.0f);
        });
        cv::imshow("Output", *output);
    };

    int __tmp0;
    cv::createTrackbar("Contrast", "Output", &__tmp0, static_cast<int>(trackMax), onchange, &data0);
    onchange(__tmp0, &data0);
    
    cv::waitKey();

    return 0;
}