#include "lab1.h"

void getChannel(const uint8_t* input, int width, int height, int inStep, int inChannel,
    uint8_t* output, int outStep, int channelToGet)
{
    for (int i = 0; i < width * height; ++i)
    {
        int index = i * inChannel;
        if (i % inStep != 0) { continue; }
        output[i / inStep * outStep] = input[index + channelToGet];
    }
}