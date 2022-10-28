#include "glm/fwd.hpp"
#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "stage.h"
#include "vkenv.h"
#include <tuple>

int main()
{
    initializeVulkan();
    {
        cv::Mat input = cv::imread("../face.png");
        GPUMat tex0(&input);
        tex0.apply();

        StageProperties assets {
            {}, { &tex0 }, {}, 
            {
                glm::vec4(50.0f, 0.3f, 0.0f, 0.0f) // { sigmaSpace, sigmaColor } 
            },
            "../shaders/bilateralFilter.spv"
        };

        StageProperties assetsForBlit {
            {}, {}, {}, {},
            "../shaders/blit.spv"
        };

        Stage output(tex0.width(), tex0.height(), &assets);
        Stage blitBuf(tex0.width(), tex0.height(), &assetsForBlit);

        assets.reference[0] = &blitBuf;
        assetsForBlit.reference[0] = &output;

        cv::namedWindow("Output");

        cv::setMouseCallback("Output", [](int event, int x, int y, int flags, void* data) {
            uiMouseX = x;
            uiMouseY = y;
            uiMouseLBT = event == cv::EVENT_LBUTTONDOWN;
            uiMouseRBT = event == cv::EVENT_RBUTTONDOWN;
        }, nullptr);

        int age = 1;
        while (true) {

            output.render(age);

            output.show("Output");

            age += 1;
            
            if (cv::waitKey(5) == 'q')
            {
                break;
            }
        }

    }
    cleanupVulkan();
    return 0;
}