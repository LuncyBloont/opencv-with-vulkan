#include "glm/fwd.hpp"
#include "lab1.h"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include "shader.h"

#define FG_PATH "../e1.png"
#define BG_PATH "../bg.png"

int main()
{
    cv::Mat fg = cv::imread(FG_PATH, cv::IMREAD_UNCHANGED);
    cv::Mat bg = cv::imread(BG_PATH);

    assert(!fg.empty());
    assert(!bg.empty());

    cv::Mat alphaImg;
    alphaImg.create(fg.size(), CV_8UC1);

    getChannel(fg.ptr(), fg.size().width, fg.size().height, 1, 4, alphaImg.ptr(), 1, 3);

    cv::Mat result;
    result.create(bg.size(), bg.type());

    process(result, [&](glm::vec2 uv) {
        glm::vec4 fgcol = sample(fg, uv * glm::vec2(2.0f, 1.0f));
        return glm::mix(sample(bg, uv, SampleUV::Clamp, SamplePoint::Point), fgcol, fgcol.a);
    });

    cv::namedWindow("Input foreground");
    cv::namedWindow("Input background");
    cv::namedWindow("Output alpha");
    cv::namedWindow("Output result");

    cv::imshow("Input foreground", fg);
    cv::imshow("Input background", bg);
    cv::imshow("Output alpha", alphaImg);
    cv::imshow("Output result", result);

    cv::waitKey();

    return 0;
}


