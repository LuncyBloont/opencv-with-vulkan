#ifndef CVVK_HELPER_H
#define CVVK_HELPER_H

#include "glm/fwd.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"
#include <cstdio>
#include <sstream>
#include <stdint.h>
#include <string>
#include <glm/glm.hpp>
#include <chrono>

namespace mltsg 
{
    
#define MLTSG_MULTI_PASS(times, _src, _dst, resultPtr, ...) do { for (int i##times = 0; i##times < times; ++i##times) \
    { \
        cv::Mat* src = i##times % 2 == 0 ? _src : _dst; \
        cv::Mat* dst = i##times % 2 == 1 ? _src : _dst; \
        __VA_ARGS__ \
    } \
    resultPtr = (times + 2 - 1) % 2 == 1 ? _src : _dst; \
} while(0)

void markTime();
float endMark(const char* msg, float scale = 1.0f);

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

#ifndef NDEBUG 
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
    glm::vec2 operator()(glm::vec2 uv) const { return uv * glm::vec2(float(width), float(height)); } 
};

struct ToUV
{
    int width;
    int height;
    glm::vec2 operator()(glm::vec2 coord) const { return coord / glm::vec2(float(width), float(height)); }
};

#define MLTSG_PATH(s) ("../" s)

template <typename T>
bool inBound(T x, T y, T w, T h, T zw = 0.f, T zh = 0.f)
{
    return x < w && y < h && x >= zw && y >= zh;
}

inline float markTimeX()
{
    static auto pre = std::chrono::system_clock::now();
    const auto now = std::chrono::system_clock::now();

    const auto dur = std::chrono::duration<float, std::chrono::milliseconds::period>(now - pre);
    pre = now;
    return dur.count();
}

inline auto timeStart()
{
    return std::chrono::system_clock::now();
}

inline float timeEnd(const std::chrono::system_clock::time_point& beg)
{
    const auto now = std::chrono::system_clock::now();
    const auto dur = std::chrono::duration<float, std::chrono::milliseconds::period>(now - beg);
    return dur.count();
}

}

#endif