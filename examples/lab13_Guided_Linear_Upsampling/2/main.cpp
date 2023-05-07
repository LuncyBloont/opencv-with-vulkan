#include "gpuMat.h"
#include "helper.h"
#include "stage.h"
#include <opencv2/opencv.hpp>
#include <fstream>

int main(int argc, char** args)
{
    mltsg::initializeVulkan();
    {
        if (argc < 3)
        {
            std::cerr << "no arguments given..." << std::endl;
            mltsg::cleanupVulkan();
            return -1;
        }

        cv::Mat iImg = mltsg::imreadRGB(args[1], cv::IMREAD_UNCHANGED);

        mltsg::GPUMat iTex(&iImg, MLTSG_READ_MAT, false);

        const uint32_t sWidth = (iTex.width() + 8 - 1) / 8;
        const uint32_t sHeight = (iTex.height() + 8 - 1) / 8;

        cv::Mat sImg(sHeight, sWidth, iTex.cpuData->type());

        mltsg::StageProperties downsampleAssets{
            {}, {&iTex}, {},
            {
                glm::vec4(sWidth * 8, sHeight * 8, 8 / 2, 0.0f),
                glm::vec4(iTex.width(), iTex.height(), 8, 0.0f)
            }, MLTSG_PATH("/shaders/glu_downsample.spv")
        };

        mltsg::Stage downsampleStage{sWidth, sHeight, &downsampleAssets};

        mltsg::StageProperties calIndexWeightAssets{
            {&downsampleStage}, {&iTex}, {},
            {
                glm::vec4(iTex.width(), iTex.height(), 8, 0.0f),
                glm::vec4(sWidth, sHeight, 8 / 2, 0.0f)
            },
            MLTSG_PATH("/shaders/glu_index_weight.spv")
        };

        mltsg::Stage indexWeightStage{iTex.width(), iTex.height(), &calIndexWeightAssets};

        mltsg::StageProperties upsampleAssets{
            {&indexWeightStage}, {downsampleStage.getGPUMat()}, {},
            {glm::vec4(iTex.width(), iTex.height(), 8, 0.0f), glm::vec4(sWidth, sHeight, 8 / 2, 0.0f)},
            MLTSG_PATH("/shaders/glu_upsample.spv")
        };

        mltsg::Stage upsampleStage{iTex.width(), iTex.height(), &upsampleAssets};

        auto k0 = mltsg::timeStart();
        for (int i = 0; i < 6; ++i)
        {
            iTex.apply();

            downsampleStage.render(1 + i);
            upsampleStage.render(1 + i);

            upsampleStage.getGPUMat()->apply();
        }
        float kk = mltsg::timeEnd(k0) / 6.0f;

        cv::imwrite(args[2], *upsampleStage.getGPUMat()->cpuData);

        float allTime = iTex.applyTime + upsampleStage.getGPUMat()->applyTime + kk;
        std::cout << "time: " << allTime << std::endl;

        std::cerr << "Vulkan_GLU_GraphicsPipeline " << args[1] << " " << iTex.width() << "x" << iTex.height() << "x" << iTex.cpuData->channels() << " " << allTime << std::endl;
    }
    mltsg::cleanupVulkan();
}