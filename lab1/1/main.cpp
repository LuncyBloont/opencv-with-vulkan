#include "opencv2/core/matx.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <opencv2/core.hpp>
#include <stdint.h>

#define FILE_PATH "../dd.png"

int main(int argc, char** argv)
{
    cv::Mat img = cv::imread(FILE_PATH);
    assert(!img.empty());

    cv::namedWindow("Lab1-1");
    cv::imshow("Lab1-1", img);
    cv::waitKey();

    return 0;
}