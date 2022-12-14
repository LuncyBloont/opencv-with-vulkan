#ifndef CVVK_HELPER_H
#define CVVK_HELPER_H

#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"
#include "shader.h"
#include <cstdio>
#include <sstream>
#include <stdint.h>
#include <string>

namespace mltsg 
{
    
#define MLTSG_MULTI_PASS(times, _src, _dst, resultPtr, ...) { for (int i##times = 0; i##times < times; ++i##times) \
    { \
        cv::Mat* src = i##times % 2 == 0 ? _src : _dst; \
        cv::Mat* dst = i##times % 2 == 1 ? _src : _dst; \
        __VA_ARGS__ \
    } \
    resultPtr = (times + 2 - 1) % 2 == 1 ? _src : _dst; \
}

void markTime();
float endMark(const char* msg);

float areaOfTriangle(glm::vec2 A, glm::vec2 B, glm::vec2 C);
float disToLine(glm::vec2 p, glm::vec2 A, glm::vec2 B);

#define MLTSG_U8 uint8_t, 255
#define MLTSG_HDR float, MLTSG_HDR_MAX


#define MLTSG_Log _MLTSG_Log_Type_

/** @brief class MLTSG_Log is used to MLTSG_Log message on console.
*/
class MLTSG_Log
{
public:
    enum class MLTSG_LogType
    {
        Error,
        Info,
        Waring,
        Custom
    };

    struct Profile
    {
        const char* prefix = "";
        const char* prefixStyle = "";
        const char* signStyle = "";
        const char* textStyle = "";
    };

private:
    MLTSG_LogType type;
    FILE* file = stdout;
    Profile custom;

private:
    void setColor() const;
    void unsetColor() const;

public:

    explicit MLTSG_Log(MLTSG_LogType type, FILE* file);
    explicit MLTSG_Log(const Profile& customProfile, FILE* file);

    template<typename ...Args>
    void operator()(const std::string& msg, const Args&... args) const
    {
        setColor();
        std::fprintf(file, msg.c_str(), args...);
        unsetColor();
    }
};

#undef MLTSG_Log

extern const _MLTSG_Log_Type_ Log;
extern const _MLTSG_Log_Type_ LogErr;
extern const _MLTSG_Log_Type_ LogWarn;
extern const _MLTSG_Log_Type_ _MLTSG_LogDB;

#ifdef DEBUG 
#define MLTSG_LogDB(...) _MLTSG_LogDB(__VA_ARGS__)
#else
#define MLTSG_LogDB(...)
#endif

template <typename T>
std::string _any_to_string(const T& t)
{
    std::stringstream s;
    s << t;
    return s.str();
}

#define CSTR(s) _any_to_string(s).c_str()
#define STR(s) _any_to_string(s)

cv::Mat imreadRGB(const char* path, int flags = cv::IMREAD_COLOR);

struct Scaler
{
    int width;
    int height;
    glm::vec2 operator()(glm::vec2 uv) { return uv * glm::vec2(float(width), float(height)); } 
};

struct ToUV
{
    int width;
    int height;
    glm::vec2 operator()(glm::vec2 coord) { return coord / glm::vec2(float(width), float(height)); }
};

#define MLTSG_PATH(s) ("../" s)

template <typename Int, int32_t Limit>
cv::Mat genHistMap(const cv::Mat& input, bool combineChannels)
{
    cv::Mat res;
    res.create(1, Limit, CV_32SC(input.channels()));
    memset(res.data, 0, res.elemSize() * res.total());

    float* ptr = res.ptr<float>(0);

    for (int r = 0; r < input.rows; ++r)
    {
        const Int* line = input.ptr<Int>(r);
        for (int c = 0; c < input.cols; ++c)
        {
            const Int* vals = line + c * input.channels();
            if (combineChannels)
            {
                int br = 0;
                for (int i = 0; i < input.channels(); ++i)
                {
                    br += int(vals[i]);
                }
                br /= input.channels();

                for (int i = 0; i < input.channels(); ++i)
                {
                    ptr[br * input.channels() + i] += 1.0f / float(input.cols * input.rows);
                }
            }
            else 
            {
                for (int i = 0; i < input.channels(); ++i)
                {
                    ptr[int(vals[i] * input.channels() + i)] += 1.0f / float(input.cols * input.rows);
                }
            }
        }
    }

    return res;
}

template <typename Int, int32_t Limit>
cv::Mat equalizeHist(const cv::Mat& input, const cv::Mat& raw)
{
    cv::Mat res(cv::Size(Limit, 1), input.type(), cv::Scalar(1.0f, 1.0f, 1.0f, 1.0f));

    glm::vec4 s = glm::vec4(0.0f);
    float* ptr = res.ptr<float>(0);
    const float* iptr = input.ptr<float>(0);
    for (int c = 0; c < Limit; ++c)
    {
        for (int i = 0; i < input.channels(); ++i)
        {
            s[i] += iptr[c * input.channels() + i];
            ptr[c * input.channels() + i] = s[i];
        }
    }
    
    return res;
}

template <uint32_t CoreSize, typename Int, int32_t Scale, typename Type>
cv::Mat genSDF2D(const cv::Mat& input, Type solid, float threshold, float disScale = 0.001f, int times = 1)
{
    float core[CoreSize][CoreSize];

    for (int x = 0; x < CoreSize; ++x)
    {
        for (int y = 0; y < CoreSize; ++y)
        {
            core[x][y] = glm::length(glm::vec2(float(x), float(y))) * disScale;
        }
    }

    cv::Mat res;
    res.create(input.size(), input.type());

    multiProcess<Int, Scale, 32>(res, [&](glm::vec2 uv) {
        Type col = Type(texelFetch<Int, Scale>(input, uv));
        if (glm::distance(solid, col) < threshold)
        {
            return glm::vec4(0.0f);
        }
        return glm::vec4(1.0f);
    });

    Scaler scaler { input.cols, input.rows };
    ToUV toUV { input.cols, input.rows };

    bool route = true;

    const auto shader = [&](glm::vec2 uv) {
        glm::vec2 pos = scaler(uv);
        Type old = Type(texelFetch<Int, Scale>(res, uv));
        for (int x = 0; x < CoreSize; ++x)
        {
            for (int y = 0; y < CoreSize; ++y)
            {
                glm::vec2 smpUV = toUV(pos - (route ? 1.0f : -1.0f) * glm::vec2(float(x), float(y)));
                Type smp = texelFetch<Int, Scale>(res, smpUV);
                float dis = core[x][y];
                old = glm::min(old, smp + dis);
            }
        }
        return glm::vec4(old.x);
    };

    for (int t = 0; t < times; ++t)
    {
        route = true;
        process<Int, Scale>(res, shader);
        route = false;
        process<Int, Scale, ProcessRoute::BB>(res, shader);
    }
    
    return res;
}

template <typename T>
bool inBound(T x, T y, T w, T h, T zw = 0.f, T zh = 0.f)
{
    return x < w && y < h && x >= zw && y >= zh;
}

}

#endif