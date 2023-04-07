#include "glm/common.hpp"
#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "stage.h"
#include "vkenv.h"

#define SIZE 800, 450
#define WIDTH 800
#define HEIGHT 450

void vkmain()
{
    cv::Mat noise = mltsg::imreadRGB(MLTSG_PATH("/images/Noise1G.png"));
    mltsg::GPUMat noiseTex0(&noise);
    noiseTex0.apply();

    cv::Mat noise1 = mltsg::imreadRGB(MLTSG_PATH("/images/Noise2G.png"));
    mltsg::GPUMat noiseTex1(&noise1);
    noiseTex1.apply();

    cv::Mat voronoi = mltsg::imreadRGB(MLTSG_PATH("/images/Cells2.png"));
    mltsg::GPUMat voronoiTex0(&voronoi);
    voronoiTex0.apply();

    mltsg::StageProperties assetsA
    {
        {}, { &voronoiTex0, &noiseTex0 }, {}, {},
        MLTSG_PATH("/shaders/Distrct13Final/main.spv")
    };

    mltsg::StageProperties assetsB
    {
        {}, { &noiseTex1 }, {}, {},
        MLTSG_PATH("/shaders/Distrct13Final/skybox.spv")
    };

    mltsg::StageProperties assetsC
    {
        {}, {}, {}, {},
        MLTSG_PATH("/shaders/Distrct13Final/blockFresh.spv")
    };

    mltsg::StageProperties assetsShow
    {
        {}, {}, {}, {},
        MLTSG_PATH("/shaders/Distrct13Final/show.spv")
    };

    mltsg::Stage bufferA(SIZE, &assetsA, true);
    mltsg::Stage bufferB(SIZE, &assetsB, true);
    mltsg::Stage bufferC(SIZE, &assetsC, true);
    mltsg::Stage bufferShow(SIZE, &assetsShow);

    assetsA.reference[0] = &bufferB;
    assetsC.reference[0] = &bufferC;
    assetsC.reference[1] = &bufferA;
    assetsShow.reference[0] = &bufferC;

    int age = 1;
    float FPS = 0.0f;
    while (true) {
        mltsg::markTime();
        cv::namedWindow("Show");
        cv::setMouseCallback("Show", [](int event, int x, int y, int flags, void*) {
            static bool bd;
            if (event == cv::EVENT_LBUTTONDOWN) { bd = true; }
            if (event == cv::EVENT_LBUTTONUP) { bd = false; }
            mltsg::uiMouseX = bd ? x : 0;
            mltsg::uiMouseY = bd ? y : 0;
        });

        bufferShow.render(age);

        if (bufferShow.show("Show") == 'q')
        {
            break;
        }

        FPS = glm::mix(FPS, 1.0f / (0.00001f + mltsg::endMark("")), 0.3f);
        age += 1;
        if (age % 180 == 0)
        {
            mltsg::Log("FPS: %f\n", FPS);
        }
    }

    bufferShow.render(age + 1);
    bufferShow.applyAndShow("Show");
    cv::imwrite("./Distrct13.png", *bufferShow.getGPUMat()->cpuData);
}

int main()
{
    mltsg::initializeVulkan();
    vkmain();
    mltsg::cleanupVulkan();
    return 0;
}