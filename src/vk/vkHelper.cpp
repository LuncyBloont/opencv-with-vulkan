#include "vkHelper.h"
#include "opencv2/highgui.hpp"
#include "vkenv.h"
#include "vkinfo.h"
#include "vulkan/vulkan_core.h"
#include <stdexcept>
#include <stdint.h>
#include <vcruntime.h>
#include <vcruntime_string.h>
#include <vector>
#include "gpuMat.h"

void mltsg::readShader(VkShaderModule& shader, std::string fname)
{
    std::vector<char> codes;

    mltsg::SHADER_INFO info{};

    std::ifstream file(fname, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "\033[31mFailed to read shader file (" << fname << ")\n\033[0m";
        throw std::runtime_error("read shader");
    }

    while (file.peek() != EOF)
    {
        char p;
        file.read(&p, 1);
        codes.push_back(p);
    }

    file.close();

    info.codeSize = codes.size();
    info.pCode = reinterpret_cast<uint32_t*>(codes.data());

    mltsg::Log("Load shader %s (size: %llu)\n", mltsg::CSTR(fname), info.codeSize);
    
    mltsg::trydo(VK_SUCCESS) = vkCreateShaderModule(mltsg::gVkDevice, &info, MLTSG_GVKALC, &shader);
}

template <typename Func>
static void showMipmap_tmp(int levels, bool HDR, Func func)
{
    const cv::Mat& mat = func(0);

    if (levels > 1)
    {
        cv::Mat o { cv::Size { (int)mat.cols * 3 / 2 + 1, (int)mat.rows }, CV_8UC4 };
        mltsg::multiProcess<MLTSG_U8, 32>(o, [&](glm::vec2 uv) {
            if (uv.x * o.cols < mat.cols && uv.y * o.rows < mat.rows)
            {
                if (!HDR)
                {
                    return mltsg::sample<MLTSG_U8>(func(0), uv * glm::vec2(o.cols, o.rows) / glm::vec2(mat.cols, mat.rows));
                } 
                else 
                {
                    return glm::abs(mltsg::sample<MLTSG_HDR>(func(0), uv * glm::vec2(o.cols, o.rows) / glm::vec2(mat.cols, mat.rows)));
                }
            }
            return glm::vec4(0.f);
        });
        for (int i = 1; i < levels; ++i)
        {
            mltsg::multiProcess<MLTSG_U8, 32>(o, [&](glm::vec2 uv) {
                glm::vec2 px = uv * glm::vec2(o.cols, o.rows);
                glm::vec2 size = glm::vec2(mltsg::toMipmapSize(mat.cols, i), mltsg::toMipmapSize(mat.rows, i));
                float ys = o.rows - 2.f * size.y + 1.f;
                if (px.x > mat.cols - .5f && px.x < mat.cols + size.x - .5f && px.y > ys - 1.f && px.y < ys + size.y)
                {
                    if (!HDR)
                    {
                        return mltsg::sample<MLTSG_U8>(func(i), (px - glm::vec2(mat.cols, ys - .5f)) / size);
                    } 
                    else 
                    {
                        return glm::abs(mltsg::sample<MLTSG_HDR>(func(i), (px - glm::vec2(mat.cols, ys - .5f)) / size));
                    }
                }
                return mltsg::sample<MLTSG_U8>(o, uv);
            });
        }

        cv::imshow("Mip", o);
        cv::waitKey();
    }
    else
    {
        cv::imshow("Mip", mat);
        cv::waitKey();
    }
}

void mltsg::showMipmap(const GPUMat* mat)
{
    showMipmap_tmp((int)mat->levels, mat->HDR, [&](int i) { return *mat->levelToMat(i); });
}


void mltsg::showMipmap(const std::vector<cv::Mat>* maps, bool HDR)
{
    showMipmap_tmp((int)maps->size(), HDR, [&](int i) { return maps->at(i); });
}