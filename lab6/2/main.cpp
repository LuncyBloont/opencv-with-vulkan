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
    initializeVulkan();
    {
        const uint32_t width = 800;
        const uint32_t height = 600;

        cv::Mat waveBump = imreadRGB("../Noise1.png");
        GPUMat waveBumpTex(&waveBump);
        waveBumpTex.apply();
        cv::Mat bubble = imreadRGB("../Noise2.png");
        GPUMat bubbleTex(&bubble);
        bubbleTex.apply();
        cv::Mat bricks = imreadRGB("../bb.png");
        GPUMat bricksTex(&bricks);
        bricksTex.apply();

        StageProperties bufferAConfig {
            {}, {}, {}, {},
            "../shaders/waveWater/bufferA.spv"
        };

        StageProperties bufferBConfig {
            {}, {}, {}, {},
            "../shaders/waveWater/bufferB.spv"
        };

        StageProperties bufferCConfig {
            {}, { &waveBumpTex }, {}, {},
            "../shaders/waveWater/bufferC.spv"
        };

        StageProperties mainImageConfig {
            {}, { &bricksTex, &bubbleTex }, {}, {},
            "../shaders/waveWater/image.spv"
        };

        Stage bufferA(width, height, &bufferAConfig, true);
        Stage bufferB(width, height, &bufferBConfig, true);
        Stage bufferC(width, height, &bufferCConfig, true);
        Stage mainImage(width, height, &mainImageConfig);

        bufferAConfig.reference[0] = &bufferB;
        bufferBConfig.reference[0] = &bufferA;
        bufferCConfig.reference[0] = &bufferB;
        mainImageConfig.reference[0] = &bufferC;

        uint32_t age = 1;

        cv::namedWindow("Output");
        cv::setMouseCallback("Output", [](int event, int x, int y, int flags, void* data) {
            if (event == cv::EVENT_LBUTTONDOWN)
            {
                uiMouseX = x;
                uiMouseY = reinterpret_cast<GPUMat*>(data)->height() - y;
                uiMouseLBT = 1.0f;
            }
            else
            {
                uiMouseX = -100;
                uiMouseY = -100;
                uiMouseLBT = 0.0f;
            }
        }, mainImage.getGPUMat());
        
        float avgFPS = 0.0f;
        while (true) {
            markTime();
            mainImage.render(age);
            if (mainImage.show("Output") == 'q')
            {
                break;
            }
            age += 1;
            avgFPS = glm::mix(avgFPS, 1.0f / endMark(""), 0.3f);
        }
        Log("FPS: %f\n", avgFPS);
    }
    cleanupVulkan();
    return 0;
}