#include "helper.h"
#include <opencv2/opencv.hpp>

const cv::Mat* rawImage;
float threshold0;
float threshold1;

template <typename Shader>
void toAlphaMask(cv::Mat& res, const cv::Mat& raw, const Shader& shader)
{
    rawImage = &raw;
    mltsg::multiProcess<MLTSG_U8, 128>(res, shader);
}

namespace lab10_shaders
{

const auto&& colDiff = [](glm::vec2 uv) {
    float a;
    glm::vec3 col = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(*rawImage, uv));
    float d = col.g - glm::max(col.r, col.b);
    if (d > threshold0) { a = 0.f; }
    else if (d < threshold0 - threshold1) { a = 1.f; }
    else { a = (threshold0 - d) / threshold1; }
    return glm::vec4(a);
};

const auto&& spcDiff = [](glm::vec2 uv) {
    float a;
    glm::vec3 col = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(*rawImage, uv));
    glm::vec3 s0 = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(*rawImage, glm::vec2(.15f, .15f)));
    glm::vec3 s1 = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(*rawImage, glm::vec2(.15f, .85f)));
    glm::vec3 s2 = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(*rawImage, glm::vec2(.85f, .85f)));
    glm::vec3 s3 = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(*rawImage, glm::vec2(.85f, .15f)));

    const auto&& calAplha = [](glm::vec3 c, glm::vec3 b) {
        float d = glm::distance(c, b) / pow(3.f, .5f);
        if (d > threshold0) { return 1.f; }
        else if (d < threshold0 - threshold1) { return 0.f; }
        else { return 1.f - (threshold0 - d) / threshold1; }
    };

    a = calAplha(col, s0);
    a = glm::min(a, calAplha(col, s1));
    a = glm::min(a, calAplha(col, s2));
    a = glm::min(a, calAplha(col, s3));
    return glm::vec4(a);
};

}

int main()
{
    cv::Mat bgimg = cv::imread(MLTSG_PATH("/images/bg.png"));
    cv::VideoCapture video("C:/Users/xhyma/Videos/media1.avi");
    assert(video.isOpened());
    cv::Mat raw;
    video >> raw;
    cv::Mat alpha(raw.size(), CV_8UC4);
    cv::Mat output(raw.size(), CV_8UC4);

    cv::namedWindow("Output");
    cv::createTrackbar("threshold0", "Output", nullptr, 255, [](int v, void*) {
        threshold0 = v * 1.f / 255;
    });
    cv::createTrackbar("threshold1", "Output", nullptr, 255, [](int v, void*) {
        threshold1 = v * 1.f / 255;
    });
    cv::setTrackbarPos("threshold0", "Output", 25);
    cv::setTrackbarPos("threshold1", "Output", 15);

    while (true) {

        toAlphaMask(alpha, raw, lab10_shaders::spcDiff);

        mltsg::multiProcess<MLTSG_U8, 128>(output, [&](glm::vec2 uv) {
            float a = mltsg::texelFetch<MLTSG_U8>(alpha, uv).x;
            glm::vec4 fg = mltsg::texelFetch<MLTSG_U8>(raw, uv);
            glm::vec4 bg = mltsg::sample<MLTSG_U8>(bgimg, uv);
            return glm::mix(bg, fg, a);
        });

        cv::imshow("Alpha", alpha);
        cv::imshow("Output", output);
    
        if (cv::pollKey() == 'q') { break; }

        video >> raw;
    }

    return 0;
}