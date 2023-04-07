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

#include "iphelper.hpp"

int main()
{
    mltsg::initializeVulkan();
    {
        bool combineChannels = true;

        cv::Mat input = cv::imread(MLTSG_PATH("/images/ii2.jpg"));

        cv::imshow("Input", input);

        cv::Mat hist = mltsg::genHistMap<uint8_t, 255>(input, combineChannels);

        cv::Mat histShow;
        histShow.create(hist.rows * 512, hist.cols, CV_8UC4);

        cv::Mat colorRamp = mltsg::equalizeHist<uint8_t, 255>(hist);
        
        cv::Mat colorRampShow;
        colorRampShow.create(hist.rows * 512, hist.cols, CV_8UC4);

        cv::Mat histEndShow;
        histEndShow.create(hist.rows * 512, hist.cols, CV_8UC4);

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
            {}, { &rawTex, &colorRampTex }, {}, 
            { glm::vec4(1.0f) },
            MLTSG_PATH("/shaders/equalizeHist.spv")
        };

        mltsg::Stage frame(rawTex.width(), rawTex.height(), &assets);

        cv::namedWindow("Output");

        frame.render(1);
        frame.applyAndShow("Output");

        cv::Mat histEnd = mltsg::genHistMap<uint8_t, 255>(*frame.getGPUMat()->cpuData, combineChannels);
        uniTex0 = &histEnd;
        mltsg::multiProcess<MLTSG_U8, 32>(histEndShow, shader);
        cv::imshow("Hist new", histEndShow);

        struct Data 
        {
            mltsg::StageProperties* assets;
            mltsg::Stage* frame;
            int age;
        } rdata { &assets, &frame, 2 };

        int cs = 0;
        assets.uniVec[0] = glm::vec4(0.0f);
        cv::createTrackbar("Fac", "Output", &cs, input.cols * 6 / 10, 
            [](int val , void* rdata){
                Data& data = *reinterpret_cast<Data*>(rdata);
                float fac(val / (1.0f * data.frame->getGPUMat()->width() * 6 / 10));
                data.assets->uniVec[0] = { fac, 0.0f, 0.0f, 0.0f };

            }, &rdata);

        while (true) {
            
            frame.render(rdata.age);
            rdata.age += 1;

            if (frame.show("Output") == 'q')
            {
                break;
            }

        }
    }
    mltsg::cleanupVulkan();

    return 0;
}
