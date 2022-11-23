#include "glm/fwd.hpp"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

int main()
{
    const char* path = MLTSG_PATH("/images/Heart.png");

    cv::Mat input = cv::imread(path);
    cv::Mat output = mltsg::genSDF2D<4, MLTSG_U8>(input, glm::vec3(1.0f), 0.8f, 0.01f, 2);

    cv::imshow("Input", input);
    cv::imshow("Output", output);

    cv::imwrite(MLTSG_PATH("/images/HeartSDF.png"), output);

    cv::waitKey();

    return 0;
}