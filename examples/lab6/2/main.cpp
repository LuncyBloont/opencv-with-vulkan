#include "glm/common.hpp"
#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "stage.h"
#include "vkenv.h"
#include <stdint.h>

/*
    ShaderToy page: https://www.shadertoy.com/view/DslGDX
*/

int main()
{
    mltsg::initializeVulkan();
    {
        const uint32_t width = 800;
        const uint32_t height = 600;

        cv::Mat waveBump = mltsg::imreadRGB("../images/Noise1.png");
        mltsg::GPUMat waveBumpTex(&waveBump);
        waveBumpTex.apply();
        cv::Mat bubble = mltsg::imreadRGB("../images/Noise2.png");
        mltsg::GPUMat bubbleTex(&bubble);
        bubbleTex.apply();
        cv::Mat bricks = mltsg::imreadRGB("../images/bb.png");
        mltsg::GPUMat bricksTex(&bricks);
        bricksTex.apply();

        mltsg::StageProperties bufferAConfig {
            {}, {}, {}, {},
            "../shaders/waveWater/bufferA.spv"
        };

        mltsg::StageProperties bufferBConfig {
            {}, {}, {}, {},
            "../shaders/waveWater/bufferB.spv"
        };

        mltsg::StageProperties bufferCConfig {
            {}, { &waveBumpTex }, {}, {},
            "../shaders/waveWater/bufferC.spv"
        };

        mltsg::StageProperties mainImageConfig {
            {}, { &bricksTex, &bubbleTex }, {}, {},
            "../shaders/waveWater/image.spv"
        };

        mltsg::Stage bufferA(width, height, &bufferAConfig, true);
        mltsg::Stage bufferB(width, height, &bufferBConfig, true);
        mltsg::Stage bufferC(width, height, &bufferCConfig, true);
        mltsg::Stage mainImage(width, height, &mainImageConfig);

        bufferAConfig.reference[0] = &bufferB;
        bufferBConfig.reference[0] = &bufferA;
        bufferCConfig.reference[0] = &bufferB;
        mainImageConfig.reference[0] = &bufferC;

        uint32_t age = 1;

        cv::namedWindow("Output");
        cv::setMouseCallback("Output", [](int event, int x, int y, int flags, void* data) {
            if (event == cv::EVENT_LBUTTONDOWN)
            {
                mltsg::uiMouseX = x;
                mltsg::uiMouseY = reinterpret_cast<mltsg::GPUMat*>(data)->height() - y;
                mltsg::uiMouseLBT = 1.0f;
            }
            else
            {
                mltsg::uiMouseX = -100;
                mltsg::uiMouseY = -100;
                mltsg::uiMouseLBT = 0.0f;
            }
        }, mainImage.getGPUMat());
        
        float avgFPS = 0.0f;
        while (true) {
            mltsg::markTime();
            mainImage.render(age);
            if (mainImage.show("Output") == 'q')
            {
                break;
            }
            age += 1;
            avgFPS = glm::mix(avgFPS, 1.0f / mltsg::endMark(""), 0.3f);
        }
        mltsg::Log("FPS: %f\n", avgFPS);
    }
    mltsg::cleanupVulkan();
    return 0;
}