
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "lab1.h"

#define INPUT0 "../images/face.png"

int main()
{
    cv::Mat testImg = cv::imread(INPUT0, cv::IMREAD_UNCHANGED);
    assert(!testImg.empty());

    cv::Mat outputr;
    outputr.create(testImg.size(), CV_8UC1);
    cv::Mat outputg;
    outputg.create(testImg.size(), CV_8UC1);
    cv::Mat outputb;
    outputb.create(testImg.size(), CV_8UC1);
    cv::Mat outputa;
    outputa.create(testImg.size(), CV_8UC1);

    mltsg_getChannel(testImg.ptr(0), testImg.size().width, testImg.size().height, 1, 4, outputr.ptr(0), 1, 0);
    mltsg_getChannel(testImg.ptr(0), testImg.size().width, testImg.size().height, 1, 4, outputg.ptr(0), 1, 1);
    mltsg_getChannel(testImg.ptr(0), testImg.size().width, testImg.size().height, 1, 4, outputb.ptr(0), 1, 2);
    mltsg_getChannel(testImg.ptr(0), testImg.size().width, testImg.size().height, 1, 4, outputa.ptr(0), 1, 3);

    cv::namedWindow("Input");

    cv::namedWindow("Output R");
    
    cv::namedWindow("Output G");
    
    cv::namedWindow("Output B");
    
    cv::namedWindow("Output A");

    cv::imshow("Input", testImg);
    cv::imshow("Output R", outputr);
    cv::imshow("Output G", outputg);
    cv::imshow("Output B", outputb);
    cv::imshow("Output A", outputa);

    cv::waitKey();

    return 0;
}