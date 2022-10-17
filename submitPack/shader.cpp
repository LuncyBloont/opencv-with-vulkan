#include "shader.h"
#include "glm/common.hpp"
#include "glm/fwd.hpp"

glm::vec4 getPixel(const cv::Mat& img, int x, int y, SampleUV uvtype)
{
    switch (uvtype) {
        case SampleUV::Repeat:
            x = (x % img.cols + img.cols) % img.cols;
            y = (y % img.rows + img.rows) % img.rows;
            break;
        case SampleUV::Clamp:
            x = glm::clamp(x, 0, img.cols - 1);
            y = glm::clamp(y, 0, img.rows - 1);
            break;
    }

    glm::vec4 res(0.0f, 0.0f, 0.0f, 1.0f);
    const uint8_t* p = img.ptr(y) + x * img.channels();

    if (img.channels() >= 1)
    {
        res.x = p[0] / 255.0f;
    }
    if (img.channels() >= 2)
    {
        res.y = p[1] / 255.0f;
    }
    if (img.channels() >= 3)
    {
        res.z = p[2] / 255.0f;
    }
    if (img.channels() >= 4)
    {
        res.w = p[3] / 255.0f;
    }
    return res;
}


glm::vec4 sample(const cv::Mat& img, glm::vec2 uv, SampleUV uvtype, SamplePoint pointtype)
{

    glm::vec2 near = glm::floor(uv * glm::vec2(img.cols, img.rows));
    int x = int(near.x);
    int y = int(near.y);

    if (pointtype == SamplePoint::Point)
    {
        return getPixel(img, x, y, uvtype);
    }
    
    glm::vec2 offset = glm::fract(uv * glm::vec2(img.cols, img.rows));
    return glm::mix(
        glm::mix(getPixel(img, x, y, uvtype), getPixel(img, x + 1, y, uvtype), offset.x), 
        glm::mix(getPixel(img, x, y + 1, uvtype), getPixel(img, x + 1, y + 1, uvtype), offset.x), offset.y);
}