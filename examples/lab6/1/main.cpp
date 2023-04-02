#include "glm/fwd.hpp"
#include "glslStyle.hpp"
#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "shader.h"
#include "stage.h"
#include "vkenv.h"
#include <tuple>

#define PATH "../images/p0.jpg"
using namespace glm;

int main()
{
    mltsg::initializeVulkan();
    {
        cv::Mat input = mltsg::imreadRGB(PATH);
        mltsg::GPUMat tex0(&input);
        tex0.apply();

        float sigmaSpace = 6.0f;
        float sigmaColor = 65.0f;
        int size = 32;

        cv::Mat input1 = cv::imread(PATH);
        cv::Mat bFilterCV;
        bFilterCV.create(input1.size(), input1.type());
        cv::bilateralFilter(input1, bFilterCV, size, sigmaColor, sigmaSpace);
        cv::imshow("Output1", bFilterCV);
        mltsg::endMark("cv::bilateralFilter spend: %fs\n");

        cv::Mat output1;
        output1.create(input1.size(), input1.type());

        cv::Mat spaceWeight;
        spaceWeight.create(size + 1, size + 1, CV_32SC1);
        for (int i = 0; i <= size; ++i)
        {
            for (int j = 0; j <= size; ++j)
            {
                vec2 spUVOff = vec2(i, j);
                spaceWeight.ptr<float>(i, j)[0] = exp(-dot(spUVOff, spUVOff) / 2.0f / pow(sigmaSpace, 2.0f));
            }
        }

        std::vector<float> colorWeight(256 * 3);
        for (int i = 0; i < 256 * 3; ++i)
        {
            colorWeight[i] = float(exp(-pow(i, 2.0f) / 2.0f / pow(sigmaColor, 2.0f)));
        }

        mltsg::markTime();
        mltsg::multiProcess<MLTSG_U8, 32>(output1, [&](glm::vec2 uv)
        {
            vec3 col = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(input1, uv));
            vec3 sumCol = vec3(0.0f);
            float sumFac = 0.0f;
            for (float i = -float(size); i <= float(size); i += 1.0f)
            {
                for (float j = -float(size); j <= float(size); j += 1.0f)
                {
                    vec2 spUVOff = vec2(i, j);
                    vec3 spCol = mltsg::_rgb(mltsg::texelFetch<MLTSG_U8>(input1, uv + spUVOff / vec2(input1.cols, input1.rows)));
                    
                    float p = *spaceWeight.ptr<float>(int(abs(j)), int(abs(j)));
                    
                    p *= colorWeight[int(dot(abs(col - spCol) * 255.0f, vec3(1.0f, 1.0f, 1.0f)))];

                    sumCol += spCol * p;
                    sumFac += p;
                }
            }

            return vec4(sumCol / sumFac, 1.0f);
        });
        mltsg::endMark("Bilateral filter spend: %fs\n");
        cv::imshow("Output0", output1);

        mltsg::StageProperties assets {
            {}, { &tex0 }, {}, 
            {
                glm::vec4(6.0f, 65.0f, 1.0f, 16.0f) // { sigmaSpace, sigmaColor } 
            },
            "../shaders/bilateralFilter.spv"
        };

        mltsg::StageProperties assetsForBlit {
            {}, {}, {}, {},
            "../shaders/blit.spv"
        };

        mltsg::Stage output(tex0.width(), tex0.height(), &assets);
        mltsg::Stage blitBuf(tex0.width(), tex0.height(), &assetsForBlit);

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
            mltsg::uiMouseX = x;
            mltsg::uiMouseY = reinterpret_cast<mltsg::GPUMat*>(data)->height() - y;
            mltsg::uiMouseLBT = ldown ? 1.0f : 0.0f;
            mltsg::uiMouseRBT = 0.0f;
        }, output.getGPUMat());

        int age = 1;
        float avgFPS = 0.0f;
        while (true) {
            mltsg::markTime();
            
            output.render(age);

            avgFPS = glm::mix(avgFPS, 1.0f / mltsg::endMark(""), 0.4f);

            if (output.show("Output") == 'q')
            {
                break;
            }

            age += 1;
        }

        mltsg::Log("bilateralFilter with vulkan spend: %fs\n", 1.0f / avgFPS);

    }
    mltsg::cleanupVulkan();
    return 0;
}