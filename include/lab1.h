#pragma once

#include <cstdint>

void getChannel(const uint8_t* input, int width, int height, int inStep, int inChannel,
    uint8_t* output, int outStep, int channelToGet);