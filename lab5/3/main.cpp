
#include "glm/fwd.hpp"
#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "stage.h"
#include "vkenv.h"

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        LogErr("At least 2 params (input, output)\n");
        return -1;
    }

    initializeVulkan();
    
    {
        cv::Mat input = imreadRGB(argv[1]);

        GPUMat tex0(&input);
        tex0.apply();

        StageProperties asset {
            {}, { &tex0 }, {}, 
            { glm::vec4(16.0f, 0.0f, 0.0f, 0.0f) },
            argv[3]
        };

        Stage frame(tex0.width(), tex0.height(), &asset);

        frame.render(1);

        frame.show("Output");

        cv::waitKey();

        cv::imwrite(argv[2], *frame.getGPUMat()->cpuData);
    }

    cleanupVulkan();
    
    return 0;
}