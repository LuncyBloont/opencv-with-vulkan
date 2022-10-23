#include "helper.h"
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include <cstdio>
#include <ctime>

std::clock_t markedTime = 0;

void markTime()
{
    markedTime = clock();
}

void endMark(const char* msg)
{
    std::printf(msg, (clock() - markedTime) * 1.0f / CLOCKS_PER_SEC);
    markedTime = clock();
}

float areaOfTriangle(glm::vec2 A, glm::vec2 B, glm::vec2 C)
{
    glm::vec2 P = B - A;
    glm::vec2 E = C - A;
    return 0.5f * glm::abs(-P.y * E.x + P.x * E.y);
}

float disToLine(glm::vec2 p, glm::vec2 A, glm::vec2 B)
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

#define Log _Log_Type_

Log::Log(LogType type, FILE* file) : type(type), file(file)
{}

Log::Log(const Profile& customProfile, FILE* file) : file(file), custom(customProfile)
{
    type = LogType::Custom;
}

void Log::setColor() const
{
    const char* prefix = "unknown";
    const char* reset = "\033[0m";
    const char* prefixStyle = "\033[45;1m";
    const char* signStyle = "\033[35m";
    const char* textStyle = "\033[35;1m";
    switch (type) {
        case LogType::Error:
            prefix = "error";
            prefixStyle = "\033[41;1m";
            signStyle = "\033[31m";
            textStyle = "\033[31;1m";
            break;
        case LogType::Info:
            prefix = "info";
            prefixStyle = "\033[40;1m";
            signStyle = "\033[30m";
            textStyle = "\033[30;1m";
            break;
        case LogType::Waring:
            prefix = "waring";
            prefixStyle = "\033[43;1m";
            signStyle = "\033[33m";
            textStyle = "\033[33;1m";
            break;
        case LogType::Custom:
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

void Log::unsetColor() const
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

#undef Log

const _Log_Type_ Log(_Log_Type_::LogType::Info, stdout);
const _Log_Type_ LogErr(_Log_Type_::LogType::Error, stdout);
const _Log_Type_ LogWarn(_Log_Type_::LogType::Waring, stdout);

