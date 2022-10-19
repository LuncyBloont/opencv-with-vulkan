#include "helper.h"
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
