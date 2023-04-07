#include "glm/fwd.hpp"
#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "stage.h"
#include "vkenv.h"

int main()
{
    mltsg::initializeVulkan();

    {

        cv::Mat voronoi = mltsg::imreadRGB("../images/Cells2.png");
        mltsg::GPUMat voronoiTex(&voronoi);
        voronoiTex.apply();

        cv::Mat scene = mltsg::imreadRGB("../images/bb.png");
        mltsg::GPUMat sceneTex(&scene);
        sceneTex.apply();

        cv::Mat black = mltsg::imreadRGB("../images/black.bmp");
        mltsg::GPUMat blackTex(&black);
        blackTex.apply();

        mltsg::StageProperties assets {
            {}, { &voronoiTex, &sceneTex, &blackTex },
            {}, {},
            "../shaders/ghostHead/mainImage.spv"
        };

        mltsg::Stage frame(800, 450, &assets);

        uint32_t age = 1;

        cv::namedWindow("Output");

        cv::setMouseCallback("Output", [](int event, int x, int y, int flags, void* data) {
            static bool down;
            if (event == cv::EVENT_LBUTTONDOWN) { down = true; }
            if (event == cv::EVENT_LBUTTONUP) { down = false; }
            mltsg::uiMouseX = x;
            mltsg::uiMouseY = reinterpret_cast<mltsg::GPUMat*>(data)->height() - y;
            mltsg::uiMouseLBT = down ? 1.0f : 0.0f;

        }, frame.getGPUMat());

        float avgFPS = 0.0f;

        while (true) {
            mltsg::markTime();
            frame.render(age);
            if (frame.show("Output") == 'q')
            {
                break;
            }

            age += 1;
            avgFPS = glm::mix(avgFPS, 1.0f / mltsg::endMark(""), 0.5f);
        }

        mltsg::Log("FPS: %f\n", avgFPS);
    }

    mltsg::cleanupVulkan();
    return 0;
}