#include "gpuMat.h"
#include "opencv2/highgui.hpp"
#include "stage.h"
#include "vkenv.h"

int main()
{
    mltsg::initializeVulkan();

    {
        cv::Mat sdf = mltsg::imreadRGB(MLTSG_PATH("/images/HeartSDF_gpu.png"));
        mltsg::GPUMat gm{ &sdf };
        gm.apply();

        mltsg::StageProperties assets{
            {}, { &gm }, {}, {}, MLTSG_PATH("/shaders/sdf2dlight.spv")
        };

        mltsg::Stage frame{ gm.width(), gm.height(), &assets };

        cv::namedWindow("Frame");
        cv::setMouseCallback("Frame", [](int event, int x, int y, int flag, void* d) {
            mltsg::uiMouseX = x;
            mltsg::uiMouseY = reinterpret_cast<mltsg::GPUMat*>(d)->height() - y - 1;

            if (event == cv::EVENT_LBUTTONDOWN)
            {
                mltsg::uiMouseLBT = 1.0f;
            }
            if (event == cv::EVENT_LBUTTONUP)
            {
                mltsg::uiMouseLBT = 0.0f;
            }

            if (event == cv::EVENT_RBUTTONDOWN)
            {
                mltsg::uiMouseRBT = 1.0f;
            }
            if (event == cv::EVENT_RBUTTONUP)
            {
                mltsg::uiMouseRBT = 0.0f;
            }
        }, &gm);

        int age = 1;

        while (true) {
            frame.render(age);
            age += 1;

            if (frame.show("Frame") == 'q')
            {
                break;
            }
        }

    }

    mltsg::cleanupVulkan();
    return 0;
}