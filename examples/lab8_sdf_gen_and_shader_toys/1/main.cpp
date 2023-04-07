#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "iphelper.hpp"
#include <ctime>

int main()
{
    mltsg::initializeVulkan();

    const char* path = MLTSG_PATH("/images/Heart.png");

    cv::Mat input = cv::imread(path);
    clock_t beg;

    beg = clock();
    cv::Mat output = mltsg::genSDF2D<4, MLTSG_U8>(input, glm::vec3(1.0f), 0.8f, 0.01f, 2);
    std::cout << "spend on CPU: " << clock() - beg << std::endl;

    beg = clock();
    cv::Mat output2 = mltsg::genSDF2D_gpu<MLTSG_U8>(input, glm::vec3(1.0f), 0.8f, 0.01f, 6);
    std::cout << "spend on GPU: " << clock() - beg << std::endl;

    cv::imshow("Input", input);
    cv::imshow("Output", output);
    cv::imshow("Output2", output2);

    cv::imwrite(MLTSG_PATH("/images/HeartSDF.png"), output);
    cv::imwrite(MLTSG_PATH("/images/HeartSDF_gpu.png"), output2);

    cv::waitKey();

    mltsg::cleanupVulkan();

    return 0;
}