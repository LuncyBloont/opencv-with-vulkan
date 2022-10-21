#include <iostream>
#include <map>
#include "configMgr.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "shader.h"
#include "vk/gpuMat.h"
#include "vk/vkenv.h"
#include "gpuMem.h"
#include "vulkan/vulkan_core.h"

using namespace glm;

int main()
{
    initializeVulkan();

    {
    
        cv::Mat input = cv::imread("../abbbg.jpg");
        cv::Mat output;
        output.create(input.size(), input.type());

        GPUMat ginput(&input);
        GPUMat goutput(&output, WRITE_MAT);

        ginput.apply();

        // TODO: run shader on gouput

        goutput.apply();

        cv::imshow("Input", input);
        cv::imshow("Output", output);

        cv::waitKey();

    }

    cleanupVulkan();

    return 0;
}