#include "glm/fwd.hpp"
#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "stage.h"
#include "vkenv.h"
#include <tuple>

#define PATH "../face.png"

int main()
{
    initializeVulkan();
    {
        cv::Mat input = imreadRGB(PATH);
        GPUMat tex0(&input);
        tex0.apply();

        cv::Mat input1 = cv::imread(PATH);
        cv::Mat bFilterCV;
        bFilterCV.create(input1.size(), input1.type());
        cv::bilateralFilter(input1, bFilterCV, 32, 65.0f, 50.0f);
        cv::imshow("Output1", bFilterCV);
        endMark("cv::bilateralFilter speed: %fs\n");

        StageProperties assets {
            {}, { &tex0 }, {}, 
            {
                glm::vec4(50.0f, 65.0f, 1.0f, 16.0f) // { sigmaSpace, sigmaColor } 
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
            static bool ldown;
            if (event == cv::EVENT_LBUTTONDOWN)
            {
                ldown = true;
            }
            if (event == cv::EVENT_LBUTTONUP)
            {
                ldown = false;
            }
            uiMouseX = x;
            uiMouseY = reinterpret_cast<GPUMat*>(data)->height() - y;
            uiMouseLBT = ldown ? 1.0f : 0.0f;
            uiMouseRBT = 0.0f;
        }, output.getGPUMat());

        int age = 1;
        float avgFPS = 0.0f;
        while (true) {
            markTime();
            
            output.render(age);

            output.show("Output");

            age += 1;
            
            if (cv::waitKey(1) == 'q')
            {
                break;
            }

            avgFPS = glm::mix(avgFPS, 1.0f / endMark(""), 0.2f);
        }

        Log("bilateralFilter with vulkan FPS: %f; use %f s to complete one frame.\n", avgFPS, 1.0f / avgFPS);

    }
    cleanupVulkan();
    return 0;
}