#include "gpuMat.h"
#include "helper.h"
#include "stage.h"
#include "opencv2/opencv.hpp"
#include <fstream>

void equalizeHistColor(cv::Mat& dst, cv::Mat& src)
{
    cv::Mat hists[] = {
        cv::Mat{src.size(), CV_8UC1},
        cv::Mat{src.size(), CV_8UC1},
        cv::Mat{src.size(), CV_8UC1},
        cv::Mat{src.size(), CV_8UC1}
    };

    cv::Mat post[] = {
        cv::Mat{src.size(), CV_8UC1},
        cv::Mat{src.size(), CV_8UC1},
        cv::Mat{src.size(), CV_8UC1},
        cv::Mat{src.size(), CV_8UC1}
    };

    cv::split(src, hists);

    switch (src.channels())
    {
    case 4:
        cv::equalizeHist(hists[3], post[3]);
    case 3:  // NOLINT(clang-diagnostic-implicit-fallthrough)
        cv::equalizeHist(hists[2], post[2]);
    case 2:  // NOLINT(clang-diagnostic-implicit-fallthrough)
        cv::equalizeHist(hists[1], post[1]);
    case 1:  // NOLINT(clang-diagnostic-implicit-fallthrough)
        cv::equalizeHist(hists[0], post[0]);
    default:  // NOLINT(clang-diagnostic-implicit-fallthrough)
        break;
    }

    cv::merge(post, src.channels(), dst);
}

void test_multi_images()
{
    const std::string assetsDir = "D:/tmp/input_training_highres/input_training_highres";
    const std::string outputDir = "D:/tmp/input_training_highres/tmp";
    constexpr int start = 1;
    constexpr int end = 32;
    constexpr int downsample = 8;

    std::ofstream md_out{outputDir + "/" + "test.md"};
    md_out << "| file | build | upsample | \n";
    md_out << "| --- | --- | --- |\n";

    for (int i = start; i <= end; ++i)
    {
        mltsg::initializeVulkan();
        {
            std::string id_str = std::to_string(i);
            const std::string fname = "GT" + ((i < 10 ? "0" : "") + std::to_string(i)) + ".png";
        
            cv::Mat input = cv::imread(assetsDir + "/" + fname);
            cv::imwrite(outputDir + "/" + id_str + "_raw.png", input);
            mltsg::GPUMat inputTex0{&input, MLTSG_READ_MAT, false};
        
            const uint32_t sWidth = (inputTex0.width() + downsample - 1) / downsample;
            const uint32_t sHeight = (inputTex0.height() + downsample - 1) / downsample;
        
            cv::Mat post{cv::Size(int(sWidth), int(sHeight)), input.type()};
            mltsg::GPUMat postTex{&post, MLTSG_READ_MAT, false};
        
            mltsg::StageProperties downsampleAssets{
                {}, {&inputTex0}, {},
                {
                    glm::vec4(sWidth * downsample, sHeight * downsample, downsample / 2, 0.0f),
                    glm::vec4(inputTex0.width(), inputTex0.height(), downsample, 0.0f)
                }, MLTSG_PATH("/shaders/glu_downsample.spv")
            };
            mltsg::Stage downsampleStage{sWidth, sHeight, &downsampleAssets};

            mltsg::StageProperties calIndexWeightAssets{
                {}, {&inputTex0}, {},
                {
                    glm::vec4(inputTex0.width(), inputTex0.height(), downsample, 0.0f),
                    glm::vec4(sWidth, sHeight, downsample / 2, 0.0f)
                },
                MLTSG_PATH("/shaders/glu_index_weight.spv")
            };
            mltsg::Stage indexWeightStage{inputTex0.width(), inputTex0.height(), &calIndexWeightAssets};

            mltsg::StageProperties upsampleAssets{
                    {}, {&postTex, indexWeightStage.getGPUMat()}, {},
                    {glm::vec4(inputTex0.width(), inputTex0.height(), downsample, 0.0f), glm::vec4(sWidth, sHeight, downsample / 2, 0.0f)},
                    MLTSG_PATH("/shaders/glu_upsample.spv")
                };
            mltsg::Stage upsampleStage{inputTex0.width(), inputTex0.height(), &upsampleAssets};

            inputTex0.apply();
            
            clock_t beg = clock();
            downsampleStage.render(1);
            clock_t dur0 = clock() - beg;
            
            downsampleStage.getGPUMat()->apply();

            beg = clock();
            indexWeightStage.render(1);
            dur0 += clock() - beg;
            
            indexWeightStage.getGPUMat()->apply();
            
            std::cout << fname << ": build time " << (float(dur0) * 1000.0f / CLOCKS_PER_SEC) << "ms" << std::endl;
        
            equalizeHistColor(post, *downsampleStage.getGPUMat()->cpuData);

            postTex.apply();
            
            beg = clock();
            upsampleStage.render(1);
            clock_t dur1 = clock() - beg;
            
            upsampleStage.getGPUMat()->apply();
            
            std::cout << fname << ": upsample time " << (float(dur1) * 1000.0f / CLOCKS_PER_SEC) << "ms" << std::endl;

            cv::imwrite(outputDir + "/" + id_str + "_post_upsample.png", *upsampleStage.getGPUMat()->cpuData);
            std::cout << "complete: " << fname << std::endl;

            md_out << "| " << fname << " | " << (float(dur0) * 1000.0f / CLOCKS_PER_SEC) << "ms | " <<
                (float(dur1) * 1000.0f / CLOCKS_PER_SEC) << "ms |\n";
        }
        mltsg::cleanupVulkan();
    }
    md_out.close();
}

int main()
{
    mltsg::initializeVulkan();
    {
        // down sample the input
        cv::Mat input = cv::imread(MLTSG_PATH("images/PinkPig.jpg"));
        // cv::Mat input = cv::imread(MLTSG_PATH("images/8loopColor.png"));

        cv::imshow("input", input);
        cv::waitKey();

        mltsg::GPUMat inputTex0{&input, MLTSG_READ_MAT, false};
        inputTex0.apply();

        constexpr int downsample = 8;

        const uint32_t sWidth = (inputTex0.width() + downsample - 1) / downsample;
        const uint32_t sHeight = (inputTex0.height() + downsample - 1) / downsample;

        mltsg::StageProperties downsampleAssets{
            {}, {&inputTex0}, {},
            {
                glm::vec4(sWidth * downsample, sHeight * downsample, downsample / 2, 0.0f),
                glm::vec4(inputTex0.width(), inputTex0.height(), downsample, 0.0f)
            }, MLTSG_PATH("/shaders/glu_downsample.spv")
        };
    
        mltsg::Stage downsampleStage{sWidth, sHeight, &downsampleAssets};

        downsampleStage.render(1);
        downsampleStage.applyAndShow("downsample");
        cv::waitKey();

        // build index and weight
        mltsg::StageProperties calIndexWeightAssets{
            {}, {&inputTex0}, {},
            {
                glm::vec4(inputTex0.width(), inputTex0.height(), downsample, 0.0f),
                glm::vec4(sWidth, sHeight, downsample / 2, 0.0f)
            },
            MLTSG_PATH("/shaders/glu_index_weight.spv")
        };

        mltsg::Stage indexWeightStage{inputTex0.width(), inputTex0.height(), &calIndexWeightAssets};

        indexWeightStage.render(1);
        indexWeightStage.applyAndShow("index and weight");
        cv::waitKey();

        // image filter
        cv::Mat post{downsampleStage.getGPUMat()->cpuData->size(), downsampleStage.getGPUMat()->cpuData->type()};
        equalizeHistColor(post, *downsampleStage.getGPUMat()->cpuData);
        cv::imshow("post small", post);
        cv::waitKey();
        
        // upsample
        mltsg::GPUMat postTex{&post, MLTSG_READ_MAT, false};
        postTex.apply();
        mltsg::StageProperties upsampleAssets{
            {}, {&postTex, indexWeightStage.getGPUMat()}, {},
            {glm::vec4(inputTex0.width(), inputTex0.height(), downsample, 0.0f), glm::vec4(sWidth, sHeight, downsample / 2, 0.0f)},
            MLTSG_PATH("/shaders/glu_upsample.spv")
        };

        mltsg::Stage upsampleStage{inputTex0.width(), inputTex0.height(), &upsampleAssets};

        upsampleStage.render(1);
        upsampleStage.applyAndShow("upsample");
        cv::imwrite("D:/tmp/a.png", *upsampleStage.getGPUMat()->cpuData);
        cv::waitKey();
    }
    mltsg::cleanupVulkan();
    
    test_multi_images();

    return 0;
}