#include "helper.h"
#include <opencv2/opencv.hpp>

const cv::Mat* rawImage;
float threshold0;
float threshold1;

glm::vec2 bgpot0 = glm::vec2(.05f, .05f);
glm::vec2 bgpot1 = glm::vec2(.05f, .95f);
glm::vec2 bgpot2 = glm::vec2(.95f, .05f);
glm::vec2 bgpot3 = glm::vec2(.95f, .95f);

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
    glm::vec3 s0 = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(*rawImage, bgpot0));
    glm::vec3 s1 = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(*rawImage, bgpot1));
    glm::vec3 s2 = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(*rawImage, bgpot2));
    glm::vec3 s3 = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(*rawImage, bgpot3));

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

    bool showRaw = false;
    bool rgb3dkey = false;
    int frame = 0;
    const int allframe = (int)video.get(cv::CAP_PROP_FRAME_COUNT);

    cv::namedWindow("Output");
    cv::namedWindow("Alpha");

    cv::createTrackbar("threshold0", "Alpha", nullptr, 255, [](int v, void*) {
        threshold0 = v * 1.f / 255;
    });
    cv::createTrackbar("threshold1", "Alpha", nullptr, 255, [](int v, void*) {
        threshold1 = v * 1.f / 255;
    });
    cv::createTrackbar("frame", "Output", nullptr, 1000, [](int val, void* ptr) {
        *reinterpret_cast<int*>(ptr) = val;
    }, &frame);
    cv::createTrackbar("show raw", "Output", nullptr, 1, [](int val, void* ptr) {
        *reinterpret_cast<bool*>(ptr) = val > 0;
    }, &showRaw);
    cv::createTrackbar("key type", "Alpha", nullptr, 1, [](int val, void* ptr) {
        *reinterpret_cast<bool*>(ptr) = val > 0;
    }, &rgb3dkey);

    cv::setTrackbarPos("threshold0", "Alpha", 25);
    cv::setTrackbarPos("threshold1", "Alpha", 15);

    struct MouseCBData
    {
        glm::vec2* vs;
        int width;
        int height;
    } mdbdata { &bgpot0, raw.cols, raw.rows };

    cv::setMouseCallback("Output", [](int event, int x, int y, int flag, void* ptr) {
        static bool down = false;
        static int draging = -1;

        MouseCBData& data = *reinterpret_cast<MouseCBData*>(ptr);

        if (event == cv::EVENT_LBUTTONDOWN) 
        { 
            down = true; 
            glm::vec2* ps = data.vs;
            for (int i = 0; i < 4; ++i)
            {
                if (glm::distance(ps[i] * glm::vec2(data.width, data.height), glm::vec2(x, y)) < 8.f)
                {
                    draging = i;
                    break;
                }
            }
        }
        if (event == cv::EVENT_LBUTTONUP) { down = false; draging = -1; }

        if (down && draging >= 0)
        {
            data.vs[draging].x = x * 1.f / data.width;
            data.vs[draging].y = y * 1.f / data.height;
        }

    }, &mdbdata);

    while (true) {
        video.set(cv::CAP_PROP_POS_FRAMES, frame / 1000. * allframe);

        video >> raw;

        if (!rgb3dkey)
        {
            toAlphaMask(alpha, raw, lab10_shaders::colDiff);
        }
        else
        {
            toAlphaMask(alpha, raw, lab10_shaders::spcDiff);
        }

        mltsg::multiProcess<MLTSG_U8, 128>(output, [&](glm::vec2 uv) {
            float a = mltsg::texelFetch<MLTSG_U8>(alpha, uv).x;
            glm::vec4 fg = mltsg::texelFetch<MLTSG_U8>(raw, uv);
            glm::vec4 bg = mltsg::sample<MLTSG_U8>(bgimg, uv);
            glm::vec4 col = showRaw ? fg : glm::mix(bg, fg, a);

            glm::vec2 ps[] = { bgpot0, bgpot1, bgpot2, bgpot3 };
            for (int i = 0; i < 4; ++i)
            {
                if (glm::length((uv - ps[i]) * glm::vec2(raw.cols, raw.rows)) < 8.f)
                {
                    return col * .5f;
                }
            }
            return col;
        });

        bool allClose = true;

        if (cv::getWindowProperty("Alpha", cv::WND_PROP_VISIBLE))
        {
            cv::imshow("Alpha", alpha);
            allClose = false;
        }

        if (cv::getWindowProperty("Output", cv::WND_PROP_VISIBLE))
        {
            cv::imshow("Output", output);
            allClose = false;
        }
    
        if (cv::waitKey(15) == 'q' || allClose) { break; }

    }

    return 0;
}