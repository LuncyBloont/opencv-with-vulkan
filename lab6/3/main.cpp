#include "glm/fwd.hpp"
#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "shader.h"
#include "stage.h"
#include "vkenv.h"

int main()
{
    initializeVulkan();

    {

        cv::Mat voronoi = imreadRGB("../voronoi.png");
        GPUMat voronoiTex(&voronoi);
        voronoiTex.apply();

        cv::Mat scene = imreadRGB("../bb.png");
        GPUMat sceneTex(&scene);
        sceneTex.apply();

        cv::Mat black = imreadRGB("../black.bmp");
        GPUMat blackTex(&black);
        blackTex.apply();

        StageProperties assets {
            {}, { &voronoiTex, &sceneTex, &blackTex },
            {}, {},
            "../shaders/ghostHead/mainImage.spv"
        };

        Stage frame(800, 450, &assets);

        uint32_t age = 1;

        cv::namedWindow("Output");

        cv::setMouseCallback("Output", [](int event, int x, int y, int flags, void* data) {
            static bool down;
            if (event == cv::EVENT_LBUTTONDOWN) { down = true; }
            if (event == cv::EVENT_LBUTTONUP) { down = false; }
            uiMouseX = x;
            uiMouseY = reinterpret_cast<GPUMat*>(data)->height() - y;
            uiMouseLBT = down ? 1.0f : 0.0f;

        }, frame.getGPUMat());

        float avgFPS = 0.0f;

        while (true) {
            markTime();
            frame.render(age);
            if (frame.show("Output") == 'q')
            {
                break;
            }

            age += 1;
            avgFPS = glm::mix(avgFPS, 1.0f / endMark(""), 0.5f);
        }

        Log("FPS: %f\n", avgFPS);
    }

    cleanupVulkan();
    return 0;
}