#ifndef CVVK_HELPER_H
#define CVVK_HELPER_H

#include "glm/glm.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"
#include <cstdio>
#include <sstream>
#include <string>

#define MULTI_PASS(times, _src, _dst, resultPtr, ...) { for (int i##times = 0; i##times < times; ++i##times) \
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

#define U8 uint8_t, 255


#define Log _Log_Type_

/** @brief class Log is used to Log message on console.
*/
class Log
{
public:
    enum class LogType
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
    LogType type;
    FILE* file = stdout;
    Profile custom;

private:
    void setColor() const;
    void unsetColor() const;

public:

    explicit Log(LogType type, FILE* file);
    explicit Log(const Profile& customProfile, FILE* file);

    template<typename ...Args>
    void operator()(const std::string& msg, const Args&... args) const
    {
        setColor();
        std::fprintf(file, msg.c_str(), args...);
        unsetColor();
    }
};

#undef Log

extern const _Log_Type_ Log;
extern const _Log_Type_ LogErr;
extern const _Log_Type_ LogWarn;
extern const _Log_Type_ __LogDB;

#ifdef DEBUG 
#define LogDB(...) __LogDB(__VA_ARGS__)
#else
#define LogDB(...)
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

#endif