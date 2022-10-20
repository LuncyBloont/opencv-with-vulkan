#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include "helper.h"
#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "shader.h"
#include <iostream>

#define BTYPE_COLOR 0
#define BTYPE_ALPHA 1
#define BTYPE_SIZE 2
#define BTYPE_VALUE 3
#define BTYPE_CONTR 4
#define BTYPE_NONE -1

constexpr glm::vec2 color_ctr = glm::vec2(128, 128);
constexpr float color_radius = 100.0f;
constexpr int color_width = 256;
constexpr int color_height = 385;
constexpr float color_area = 16.0f;
constexpr float color_size = 260.0f;
constexpr float color_alpha = 280.0f;
constexpr float color_value = 300.0f;
constexpr float color_contra = 320.0f;
constexpr float color_show = 340.0f;

int main(int argc, char** args)
{
    cv::namedWindow("Drawer");
    cv::namedWindow("Brush");

    struct Data
    {
        cv::Mat input;
        cv::Mat output;
        cv::Mat colorPan;
        glm::vec4 color;
        bool ldown = false;
        glm::vec2 oldmpos;
        glm::vec2 oldmpos_m;

        bool bmdown = false;
        bool bfirst = false;
        int btype = BTYPE_NONE;
        float bsize = 5.0f;
        float balpha = 0.5f;
        glm::vec3 bcolor = glm::vec3(0.0f, 1.0f, 1.0f);
        float bcontr = 0.5f;
        float bvalue = 0.5f;
    } tmp;

    if (argc == 2)
    {
        tmp.input = cv::imread(args[1]);
    }
    else if (argc == 3)
    {
        tmp.input.create(atoi(args[1]),atoi(args[2]), CV_8UC3);
    }
    else
    {
        tmp.input = cv::imread("../dd.png");
    }

    tmp.output.create(tmp.input.size(), tmp.input.type());

    tmp.colorPan.create(color_height, color_width, tmp.input.type());

    multiProcess<U8, 16>(tmp.output, [&](glm::vec2 uv) { return texelFetch<U8>(tmp.input, uv); });

    cv::imshow("Drawer", tmp.output);

    multiProcess<U8, 16>(tmp.colorPan, [&](glm::vec2 uv) {

        glm::vec2 nuv = uv * glm::vec2(tmp.colorPan.cols, tmp.colorPan.rows);
        glm::vec2 ctr = color_ctr;
        glm::vec2 nuvD = nuv;
        if (glm::distance(nuv, ctr) < color_radius)
        {
            constexpr float r0 = 0.0f;
            constexpr float r1 = 2.0f * 3.14159265f / 3.0f;
            constexpr float r2 = 4.0f * 3.14159265f / 3.0f;
            glm::vec2 A = ctr + glm::vec2(glm::cos(r0), glm::sin(r0)) * color_radius;
            glm::vec2 B = ctr + glm::vec2(glm::cos(r1), glm::sin(r1)) * color_radius;
            glm::vec2 C = ctr + glm::vec2(glm::cos(r2), glm::sin(r2)) * color_radius;
            float r = glm::clamp(areaOfTriangle(B, C, nuvD) / areaOfTriangle(A, B, C), 0.0f, 1.0f);
            float g = glm::clamp(areaOfTriangle(C, A, nuvD) / areaOfTriangle(A, B, C), 0.0f, 1.0f);
            float b = glm::clamp(areaOfTriangle(B, A, nuvD) / areaOfTriangle(A, B, C), 0.0f, 1.0f);
            glm::vec3 col = glm::vec3(r, g, b);
            col = col / glm::max(glm::max(r, g), b);
            return glm::vec4(col, 1.0f);
        }

        return glm::vec4(1.0f);
    });

    cv::imshow("Brush", tmp.colorPan);

    cv::setMouseCallback("Drawer", [](int event, int x, int y, int flags, void* data) {
        Data& tmp = *reinterpret_cast<Data*>(data);

        glm::vec2 muv = glm::vec2(x, y);
        if (event == cv::EVENT_LBUTTONDOWN) { tmp.ldown = true; tmp.oldmpos = muv; tmp.oldmpos_m = muv; tmp.bfirst = true; }
        if (event == cv::EVENT_LBUTTONUP) { tmp.ldown = false; }

        if (tmp.ldown)
        {
            multiProcess<U8, 32>(tmp.output, [&](glm::vec2 uv) {
                glm::vec2 nuv = uv * glm::vec2(tmp.output.cols, tmp.output.rows);

                if (disToLine(nuv, muv, tmp.oldmpos) < tmp.bsize && 
                    (tmp.bfirst || disToLine(nuv, tmp.oldmpos, tmp.oldmpos_m) >= tmp.bsize))
                {
                    return glm::mix(texelFetch<U8>(tmp.output, uv), tmp.color, tmp.color.a);
                }

                return texelFetch<U8>(tmp.output, uv);
            });
        }

        tmp.oldmpos_m = tmp.oldmpos;
        tmp.oldmpos = muv;

        cv::imshow("Drawer", tmp.output);
        tmp.bfirst = false;
    }, &tmp);

    auto update = [](int event, int x, int y, int flags, void* data) {
        Data& tmp = *reinterpret_cast<Data*>(data);

        glm::vec2 muv = glm::vec2(x, y);

        glm::vec2 ctr = glm::vec2(128, 128);

        if (event == cv::EVENT_LBUTTONDOWN) 
        { 
            tmp.bmdown = true; 
            tmp.btype = BTYPE_NONE;
            if (glm::distance(muv, ctr) < color_radius)
            {
                tmp.btype = BTYPE_COLOR;
            }

            if (muv.y > color_alpha && muv.y < color_alpha + color_area)
            {
                tmp.btype = BTYPE_ALPHA;
            }

            if (muv.y > color_value && muv.y < color_value + color_area)
            {
                tmp.btype = BTYPE_VALUE;
            }

            if (muv.y > color_contra && muv.y < color_contra + color_area)
            {
                tmp.btype = BTYPE_CONTR;
            }

            if (muv.y > color_size && muv.y < color_size + color_area)
            {
                tmp.btype = BTYPE_SIZE;
            }
        }
        if (event == cv::EVENT_LBUTTONUP) { tmp.bmdown = false; tmp.btype = BTYPE_NONE; }
        
        float val = glm::clamp(muv.x / color_width, 0.0f, 1.0f);
        glm::vec2 lmuv = ctr + glm::normalize(muv - ctr) * glm::min(color_radius - 1.0f, glm::distance(muv, ctr));
        
        if (tmp.bmdown)
        {
            switch (tmp.btype) {
                case BTYPE_ALPHA:
                    tmp.balpha = val;
                    break;
                case BTYPE_COLOR:
                    tmp.bcolor = texelFetch<U8>(tmp.colorPan, lmuv / glm::vec2(color_width, color_height));
                    break;
                case BTYPE_CONTR:
                    tmp.bcontr = val;
                    break;
                case BTYPE_SIZE:
                    tmp.bsize = val * color_width;
                    break;
                case BTYPE_VALUE:
                    tmp.bvalue = val;
                    break;
                default:
                    break;
            }
        }
        
        tmp.color = glm::vec4(glm::mix(tmp.bcolor, glm::vec3(1.0f), tmp.bcontr) * tmp.bvalue, tmp.balpha);

        glm::vec3 k = tmp.color / glm::max(glm::max(tmp.color.r, tmp.color.g), tmp.color.b);

        multiProcess<U8, 16>(tmp.colorPan, [&](glm::vec2 uv) {

            glm::vec2 muv = uv * glm::vec2(color_width, color_height);

            if (muv.y > color_alpha && muv.y < color_alpha + color_area)
            {
                if (muv.x > tmp.balpha * color_width - 1.0f && muv.x < tmp.balpha * color_width + 1.0f)
                {
                    return glm::vec4(int(muv.y) % 2);
                }
                glm::vec3 checker = glm::mix(
                    glm::vec3(1.0f), 
                    glm::vec3(0.7f), 
                    float((glm::fract(muv.x / 5.0f) < 0.5f) ^ (glm::fract(muv.y / 5.0f) < 0.5f)));
                return glm::vec4(glm::mix(_rgb(tmp.color), checker, 1.0f - uv.x), 1.0f);
            }

            if (muv.y > color_value && muv.y < color_value + color_area)
            {
                if (muv.x > tmp.bvalue * color_width - 1.0f && muv.x < tmp.bvalue * color_width + 1.0f)
                {
                    return glm::vec4(int(muv.y) % 2);
                }
                return glm::vec4(k * uv.x, 1.0f);
            }

            if (muv.y > color_contra && muv.y < color_contra + color_area)
            {
                if (muv.x > tmp.bcontr * color_width - 1.0f && muv.x < tmp.bcontr * color_width + 1.0f)
                {
                    return glm::vec4(int(muv.y) % 2);
                }
                return glm::vec4(glm::mix(k, glm::vec3(1.0f), uv.x), 1.0f);
            }

            if (muv.y > color_size && muv.y < color_size + color_area)
            {
                if (muv.x > tmp.bsize - 1.0f && muv.x < tmp.bsize + 1.0f)
                {
                    return glm::vec4(int(muv.y) % 2);
                }
                return glm::mix(tmp.color, glm::vec4(1.0f), float(muv.x > tmp.bsize));
            }

            if (muv.y > color_show && muv.y < color_show + color_area * 2.0f)
            {
                glm::vec3 checker = glm::mix(
                    glm::vec3(1.0f), 
                    glm::vec3(0.7f), 
                    float((glm::fract(muv.x / 5.0f) < 0.5f) ^ (glm::fract(muv.y / 5.0f) < 0.5f)));
                return glm::vec4(glm::mix(_rgb(tmp.color), checker, 1.0f - tmp.color.a), 1.0f);
            }
            
            return texelFetch<U8>(tmp.colorPan, uv);
        });

        cv::imshow("Brush", tmp.colorPan);
    };

    update(cv::EVENT_LBUTTONUP, 0, 0, 0, &tmp);
    cv::setMouseCallback("Brush", update, &tmp);

    cv::waitKey();

    return 0;
}