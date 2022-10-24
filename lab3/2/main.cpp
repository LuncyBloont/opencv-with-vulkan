#include <iostream>
#include <map>
#include <string>
#include "configMgr.hpp"
#include "glm/fwd.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "shader.h"
#include "stage.h"
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

        GPUMat ginput(&input);
        ginput.apply();

        StageProperties assets = {
            {}, { &ginput }, {}, {},
            "../shaders/distorting.spv"
        };

        Stage goutput(input.cols, input.rows, &assets);

        uint32_t age = 1;
        while (true) {

            goutput.render(age);

            goutput.show("Output");

            int key = cv::waitKey(5);

            if (key == 'q') break;

            age += 1;
        }

    }

    cleanupVulkan();

    return 0;
}