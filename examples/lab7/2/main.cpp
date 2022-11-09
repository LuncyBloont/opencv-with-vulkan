#include "glm/common.hpp"
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
        cv::Mat heartTex = mltsg::imreadRGB(MLTSG_PATH("/images/Heart.png"));
        mltsg::GPUMat tex0(&heartTex);
        tex0.apply();

        mltsg::StageProperties assets = {
            {}, { &tex0 }, {}, {}, 
            MLTSG_PATH("/shaders/sweetHeart/sweetHear.spv")
        };

        mltsg::Stage frame(800, 600, &assets);

        cv::namedWindow("Sweet heart");

        cv::setMouseCallback("Sweet heart", [](int event, int x, int y, int flag, void* data) {
            static bool lbutDown;
            if (event == cv::EVENT_LBUTTONDOWN) { lbutDown = true; }
            if (event == cv::EVENT_LBUTTONUP) { lbutDown = false; }

            const mltsg::Stage& frame = *reinterpret_cast<mltsg::Stage*>(data);

            if (lbutDown)
            {
                mltsg::uiMouseX = x - frame.getGPUMat()->width() / 2;
                mltsg::uiMouseY = y - frame.getGPUMat()->height() / 2;
            }
            else
            {
                mltsg::uiMouseX = 0;
                mltsg::uiMouseY = 0;
            }
        }, &frame);

        int fac0 = 502;
        int fac1 = 335;
        int fac2 = 163;
        // cv::createTrackbar("Shape fac0", "Sweet heart", &fac0, 600);
        // cv::createTrackbar("Shape fac1", "Sweet heart", &fac1, 600);
        // cv::createTrackbar("Shape fac2", "Sweet heart", &fac2, 600);

        int age = 0;
        float fps = 1.0f;
        while (true) {
            mltsg::markTime();

            assets.uniVec[0].x = fac0 * 1.0f / 600.0f;
            assets.uniVec[0].y = fac1 * 1.0f / 600.0f;
            assets.uniVec[0].z = fac2 * 1.0f / 600.0f;
            
            frame.render(age);

            if (frame.show("Sweet heart") == 'q')
            {
                break;
            }

            age += 1;

            fps = glm::mix(fps, 1.0f / mltsg::endMark(""), 0.5f);

            if (age % 60 == 0)
            {
                mltsg::Log("FPS: %f\n", fps);
            }
        }

    }

    mltsg::cleanupVulkan();

    return 0;
}