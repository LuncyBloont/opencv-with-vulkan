#include "glm/fwd.hpp"
#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "shader.h"
#include "stage.h"
#include "vkenv.h"
#include <tuple>

#define PATH "../p0.jpg"
using namespace glm;

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
        cv::bilateralFilter(input1, bFilterCV, 32, 65.0f, 6.0f);
        cv::imshow("Output1", bFilterCV);
        endMark("cv::bilateralFilter spend: %fs\n");

        cv::Mat output1;
        output1.create(input1.size(), input1.type());
        markTime();
        process<U8>(output1, [&](glm::vec2 uv)
        {
            vec3 col = _rgb(texelFetch<U8>(input1, uv));
            vec3 sumCol = vec3(0.0f);
            float sumFac = 0.0f;
            float size = 32.0f;
            float sigmaSpace = 6.0f;
            float sigmaColor = 65.0f;
            for (float i = -size; i <= size; i += 1.0f)
            {
                for (float j = -size; j <= size; j += 1.0f)
                {
                    vec2 spUVOff = vec2(i, j);
                    vec3 spCol = _rgb(texelFetch<U8>(input1, uv + spUVOff / vec2(input1.cols, input1.rows)));
                    
                    float p = exp(-dot(spUVOff, spUVOff) / 2.0f / pow(sigmaSpace, 2.0f));
                    
                    p *= exp(-dot((spCol - col) * 256.0f, (spCol - col) * 256.0f) * 3.0f / 2.0f / pow(sigmaColor, 2.0f));
                    sumCol += spCol * p;
                    sumFac += p;
                }
            }

            return vec4(sumCol / sumFac, 1.0f);
        });
        endMark("Bilateral filter spend: %fs\n");
        cv::imshow("Output0", output1);

        StageProperties assets {
            {}, { &tex0 }, {}, 
            {
                glm::vec4(6.0f, 65.0f, 1.0f, 16.0f) // { sigmaSpace, sigmaColor } 
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

            avgFPS = glm::mix(avgFPS, 1.0f / endMark(""), 0.4f);

            output.show("Output");

            age += 1;
            
            if (cv::waitKey(1) == 'q')
            {
                break;
            }

        }

        Log("bilateralFilter with vulkan spend: %fs\n", 1.0f / avgFPS);

    }
    cleanupVulkan();
    return 0;
}