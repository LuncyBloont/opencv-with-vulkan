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