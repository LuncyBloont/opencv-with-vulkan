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

using namespace mltsg;

int main()
{
    initializeVulkan();

    {
        cv::VideoCapture video("../images/0.webm");
        
        cv::Mat input;
        video >> input;

        GPUMat ginput(&input, MLTSG_READ_MAT, false, MLTSG_USE_RAW);
        ginput.apply();

        StageProperties assets = {
            {}, { &ginput }, {}, {},
            "../shaders/scaleVideo.spv"
        };

        Stage goutput(input.cols, input.rows, &assets);

        uint32_t age = 1;
        while (true) {
            video >> input;
            ginput.apply();

            goutput.render(age);

            if (goutput.show("Output") == 'q')
            {
                break;
            }

            age += 1;
        }

    }

    cleanupVulkan();

    return 0;
}