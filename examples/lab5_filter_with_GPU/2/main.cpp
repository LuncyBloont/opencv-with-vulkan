#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "stage.h"
#include "vkenv.h"

using namespace mltsg;

int main()
{
    initializeVulkan();

    {
        cv::Mat input = imreadRGB("../images/abbbg.jpg");
        cv::imshow("Input", input);

        GPUMat tex0(&input);
        tex0.apply();

        StageProperties assets {
            {},
            { &tex0 },
            {}, {}, 
            "../shaders/distorting.spv"
        };

        Stage frame(input.cols, input.rows, &assets);

        markTime();
        frame.render(1);
        endMark("Filter with Vulkan speed: %fs\n");

        frame.show("Output");

        cv::waitKey();
    }

    cleanupVulkan();
    return 0;
}