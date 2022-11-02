#include "glm/fwd.hpp"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "shader.h"
#include "gpuMat.h"
#include "stage.h"
#include "vkenv.h"
#include <stdint.h>

int main()
{
    mltsg::initializeVulkan();
    {
        cv::Mat input = cv::imread(MLTSG_PATH("/images/ii.jpg"));

        cv::imshow("Input", input);

        cv::Mat hist = mltsg::genHistMap<uint8_t, 255>(input);

        cv::Mat histShow;
        histShow.create(hist.rows * 512, hist.cols, CV_8UC4);

        cv::Mat colorRamp = mltsg::equalizeHist<uint8_t, 255>(hist, input);
        
        cv::Mat colorRampShow;
        colorRampShow.create(hist.rows * 512, hist.cols, CV_8UC4);

        cv::Mat* uniTex0 = &hist;

        auto shader = [&](glm::vec2 uv) {
            glm::vec4 k = glm::vec4(mltsg::texelFetch<float, MLTSG_HDR_MAX>(*uniTex0, uv)) * float(MLTSG_HDR_MAX);

            glm::vec4 out(0.0f);

            if (uv.y > 1.0f - k.r)
            {
                out.r = 1.0f;
            }
            if (uv.y > 1.0f - k.g)
            {
                out.g = 1.0f;
            }
            if (uv.y > 1.0f - k.b)
            {
                out.b = 1.0f;
            }
            if (uv.y > 1.0f - k.a)
            {
                out.a = 1.0f;
            }
            return out;
        };

        uniTex0 = &hist;
        mltsg::multiProcess<MLTSG_U8, 32>(histShow, shader);
        cv::imshow("Hist", histShow);

        
        uniTex0 = &colorRamp;
        mltsg::multiProcess<MLTSG_U8, 32>(colorRampShow, shader);
        cv::imshow("ColorRamp", colorRampShow);

        mltsg::GPUMat rawTex(&input);
        rawTex.apply();

        mltsg::GPUMat colorRampTex(&colorRamp, MLTSG_READ_MAT, true, MLTSG_USE_RAW, true);
        colorRampTex.apply();

        mltsg::StageProperties assets {
            {}, { &rawTex, &colorRampTex }, {}, {},
            MLTSG_PATH("/shaders/equalizeHist.spv")
        };

        mltsg::Stage frame(rawTex.width(), rawTex.height(), &assets);

        frame.render(1);
        frame.show("Output");
        cv::waitKey();
    }
    mltsg::cleanupVulkan();

    return 0;
}