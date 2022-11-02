#include "helper.h"
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "opencv2/core.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"
#include <cstdio>
#include <ctime>
#include <opencv2/imgproc.hpp>

std::clock_t markedTime = 0;

void mltsg::markTime()
{
    markedTime = clock();
}

float mltsg::endMark(const char* msg)
{
    clock_t t = clock();
    float dur = (t - markedTime) * 1.0f / CLOCKS_PER_SEC;
    
    if (msg[0] != 0)
    {
        mltsg::Log(msg, dur);
    
    }
    markedTime = clock();
    return dur;
}

float mltsg::areaOfTriangle(glm::vec2 A, glm::vec2 B, glm::vec2 C)
{
    glm::vec2 P = B - A;
    glm::vec2 E = C - A;
    return 0.5f * glm::abs(-P.y * E.x + P.x * E.y);
}

float mltsg::disToLine(glm::vec2 p, glm::vec2 A, glm::vec2 B)
{
    float dis = 1e9f;
    glm::vec2 nvec = p - A;
    glm::vec2 mdir = glm::normalize(B - A);
    glm::float32 mdis = glm::distance(A, B);
    float dotres = glm::dot(mdir, nvec);
    if (dotres < 0.0f)
    {
        dis = glm::distance(A, p);
    }
    else if (dotres > mdis)
    {
        dis = glm::distance(p, B);
    }
    else
    {
        dis = glm::distance(nvec, mdir * dotres);
    }
    if (mdis == 0.0f)
    {
        dis = glm::distance(p, B);
    }
    return dis;
}

#define MLTSG_Log _MLTSG_Log_Type_

mltsg::MLTSG_Log::MLTSG_Log(MLTSG_LogType type, FILE* file) : type(type), file(file)
{}

mltsg::MLTSG_Log::MLTSG_Log(const Profile& customProfile, FILE* file) : file(file), custom(customProfile)
{
    type = MLTSG_LogType::Custom;
}

void mltsg::MLTSG_Log::setColor() const
{
    const char* prefix = "unknown";
    const char* reset = "\033[0m";
    const char* prefixStyle = "\033[45;1m";
    const char* signStyle = "\033[35m";
    const char* textStyle = "\033[35;1m";
    switch (type) {
        case MLTSG_LogType::Error:
            prefix = "error";
            prefixStyle = "\033[41;1m";
            signStyle = "\033[31m";
            textStyle = "\033[31;1m";
            break;
        case MLTSG_LogType::Info:
            prefix = "info";
            prefixStyle = "\033[40;1m";
            signStyle = "\033[30m";
            textStyle = "\033[30;1m";
            break;
        case MLTSG_LogType::Waring:
            prefix = "waring";
            prefixStyle = "\033[43;1m";
            signStyle = "\033[33m";
            textStyle = "\033[33;1m";
            break;
        case MLTSG_LogType::Custom:
            prefix = custom.prefix;
            prefixStyle = custom.prefixStyle;
            signStyle = custom.signStyle;
            textStyle = custom.textStyle;
            break;
    }

    if (file == stdout)
    {
        std::fprintf(file, "%s  %s  %s %s>>%s %s", prefixStyle, prefix, reset, signStyle, reset, textStyle);
    }
    else
    {
        std::fprintf(file, "  %s   >> ", prefix);
    }
}

void mltsg::MLTSG_Log::unsetColor() const
{
    if (file == stdout)
    {
        std::fprintf(file, "\033[0m");
    }
    else
    {
        std::fprintf(file, "");
    }
}

#undef MLTSG_Log

const mltsg::_MLTSG_Log_Type_ mltsg::Log(mltsg::_MLTSG_Log_Type_::MLTSG_LogType::Info, stdout);
const mltsg::_MLTSG_Log_Type_ mltsg::LogErr(mltsg::_MLTSG_Log_Type_::MLTSG_LogType::Error, stdout);
const mltsg::_MLTSG_Log_Type_ mltsg::LogWarn(mltsg::_MLTSG_Log_Type_::MLTSG_LogType::Waring, stdout);
const mltsg::_MLTSG_Log_Type_ mltsg::_MLTSG_LogDB(mltsg::_MLTSG_Log_Type_::Profile{ 
    "debug",
    "\033[44;1m", 
    "\033[34m",
    "\033[30m"
}, stdout);

cv::Mat mltsg::imreadRGB(const char* path, int flags)
{
    cv::Mat buf = cv::imread(path, flags);
    cv::Mat res;
    res.create(buf.size(), buf.type());
    cv::ColorConversionCodes code = cv::COLOR_BGR2RGB;
    switch (res.channels()) {
        case 1:
            return buf;
        case 2:
            return buf;
        case 3:
            code = cv::COLOR_BGR2RGB;
            break;
        case 4:
            code = cv::COLOR_BGRA2RGBA;
            break;
        default:
            code = cv::COLOR_BGR2RGB;
    }
    cv::cvtColor(buf, res, code);
    cv::flip(res, buf, 0);
    return buf;
}
