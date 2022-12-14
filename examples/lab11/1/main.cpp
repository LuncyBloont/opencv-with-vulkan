#include "gpuMat.h"
#include "helper.h"
#include "opencv2/highgui.hpp"
#include "vkenv.h"

void process()
{
    cv::Mat input0raw = cv::imread("C:/Users/xhyma/Pictures/antelope.jpg");
    cv::Mat input1raw = cv::imread("C:/Users/xhyma/Pictures/lion.jpg");

    cv::Mat input0 { input0raw.size(), CV_32FC3 };
    cv::Mat input1 { input0raw.size(), CV_32FC3 };
    mltsg::multiProcess<MLTSG_HDR, 32>(input0, [&](glm::vec2 uv) { return mltsg::texelFetch<MLTSG_U8>(input0raw, uv); });
    mltsg::multiProcess<MLTSG_HDR, 32>(input1, [&](glm::vec2 uv) { return mltsg::texelFetch<MLTSG_U8>(input1raw, uv); });
    cv::Mat output { input0.size(), CV_8UC3 };

    const int maxLevel = 9;

    mltsg::GPUMat gm0 { &input0, MLTSG_READ_MAT, true, MLTSG_USE_RAW, true };
    mltsg::GPUMat gm1 { &input1, MLTSG_READ_MAT, true, MLTSG_USE_RAW, true };

    gm0.apply();
    gm1.apply();

    std::vector<cv::Mat> lap0 { maxLevel };
    std::vector<cv::Mat> lap1 { maxLevel };
    std::vector<cv::Mat> lapC { maxLevel };

    for (int i = 0; i < maxLevel; ++i) { lap0[i].create(gm0.levelToMat(i)->size(), CV_32FC3); }
    for (int i = 0; i < maxLevel; ++i) { lap1[i].create(gm1.levelToMat(i)->size(), CV_32FC3); }
    for (int i = 0; i < maxLevel; ++i) { lapC[i].create(gm1.levelToMat(i)->size(), CV_32FC3); }

    cv::Mat* nowMip = nullptr;
    cv::Mat* nextMip = nullptr;
    const auto&& genLaplacian = [&](glm::vec2 uv) {
        return (mltsg::sample<MLTSG_HDR>(*nowMip, uv, mltsg::SampleUV::Clamp) - mltsg::sample<MLTSG_HDR>(*nextMip, uv, mltsg::SampleUV::Clamp));
    };

    for (int i = 0; i < maxLevel; ++i)
    {
        nowMip = gm0.levelToMat(i);
        nextMip = i < maxLevel - 1 ? gm0.levelToMat(i + 1) : nullptr;
        if (i < maxLevel - 1)
        {
            mltsg::multiProcess<MLTSG_HDR, 32>(lap0[i], genLaplacian);
        }
        else
        {
            mltsg::multiProcess<MLTSG_HDR, 32>(lap0[i], [&](glm::vec2 uv) { return mltsg::sample<MLTSG_HDR>(*nowMip, uv, mltsg::SampleUV::Clamp); });
        }
    }

    for (int i = 0; i < maxLevel; ++i)
    {
        nowMip = gm1.levelToMat(i);
        nextMip = i < maxLevel - 1 ? gm1.levelToMat(i + 1) : nullptr;
        if (i < maxLevel - 1)
        {
            mltsg::multiProcess<MLTSG_HDR, 32>(lap1[i], genLaplacian);
        }
        else
        {
            mltsg::multiProcess<MLTSG_HDR, 32>(lap1[i], [&](glm::vec2 uv) { return mltsg::sample<MLTSG_HDR>(*nowMip, uv, mltsg::SampleUV::Clamp); });
        }
    }

    for (int i = 0; i < maxLevel; ++i)
    {
        mltsg::multiProcess<MLTSG_HDR, 32>(lapC[i], [&](glm::vec2 uv) {
            return uv.x >= .5f ? mltsg::sample<MLTSG_HDR>(lap0[i], uv) : mltsg::sample<MLTSG_HDR>(lap1[i], uv);
        });
    }

    cv::Mat outputTmp { input0.size(), CV_32FC3 };

    for (int i = 0; i < lapC.size(); ++i)
    {
        mltsg::multiProcess<MLTSG_HDR, 32>(outputTmp, [&](glm::vec2 uv) {
            if (i == 0)
            {
                return mltsg::sample<MLTSG_HDR>(lapC[lapC.size() - 1], uv, mltsg::SampleUV::Clamp);
            }
            else
            {
                return mltsg::sample<MLTSG_HDR>(lapC[lapC.size() - 1 - i], uv, mltsg::SampleUV::Clamp) + mltsg::sample<MLTSG_HDR>(outputTmp, uv, mltsg::SampleUV::Clamp);
            }
        });
    }

    mltsg::multiProcess<MLTSG_U8, 32>(output, [&](glm::vec2 uv) {
        return glm::abs(mltsg::sample<MLTSG_HDR>(outputTmp, uv));
    });

    /* int k = 0;

    while (true)
    {
        mltsg::multiProcess<MLTSG_U8, 32>(output, [&](glm::vec2 uv) {
            // return mltsg::sample<MLTSG_HDR>(*gm0.levelToMat(k % gm0.levels), uv);
            return glm::abs(mltsg::sample<MLTSG_HDR>(lapC[k % lapC.size()], uv)) * 3.f;
            return mltsg::sample<MLTSG_HDR>(input0, uv);
        });
        cv::imshow("K", output);

        if (cv::waitKey(1000) == 'q')
        {
            break;
        }

        k += 1;
    } */

    cv::imshow("Output", output);
    cv::waitKey();


}

int main()
{
    mltsg::initializeVulkan();
    process();
    mltsg::cleanupVulkan();
    return 0;
}