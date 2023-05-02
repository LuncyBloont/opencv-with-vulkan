#include "stage.h"
#include <opencv2/opencv.hpp>

int main(int argc, char** args)
{
    std::string iname = MLTSG_PATH("/images/images/city.png");
    std::string oname = "./bl_d.png";

    if (argc == 3)
    {
        iname = args[1];
        oname = args[2];
    }

    mltsg::initializeVulkan();

    {
        cv::Mat iImg = cv::imread(iname, cv::IMREAD_UNCHANGED);

        while (iImg.cols > 2048 || iImg.rows > 2048)
        {
            cv::resize(iImg, iImg, iImg.size() / 2);
        }

        mltsg::GPUMat tex(&iImg, MLTSG_READ_MAT, false);
        tex.apply();

        mltsg::StageProperties assets{};
        assets.uniVec = {glm::vec4(75.0f, 50.0f, 0.0f, 33.0f)};
        assets.uniMat = {};
        assets.shaderPath = MLTSG_PATH("/shaders/bilateralFiltering.spv");
        assets.textures = {&tex};

        mltsg::Stage stage(tex.width(), tex.height(), &assets);

        stage.render(1);

        stage.getGPUMat()->apply();

        cv::imwrite(oname, *stage.getGPUMat()->cpuData);

        std::cout << "bl time: " << stage.realFrameTime() << "ms/" << stage.treeFrameTime() << "ms" << std::endl;
        std::cout << "bl other time: " << tex.applyTime << "ms" << std::endl;

        std::cerr << "Vulkan-GPU-GraphicsPipeline " << iname << " " << iImg.cols << "x" << iImg.rows << "x" << iImg.channels() << " " << stage.realFrameTime() + tex.applyTime << std::endl;
    }

    mltsg::cleanupVulkan();
    return 0;
}