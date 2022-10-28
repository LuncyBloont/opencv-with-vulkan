#version 420

precision highp float;

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

#define SIZE 8

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    vec4 sum = vec4(0.0);
    float base = 0.0;
    for (int i = -SIZE; i < SIZE; ++i)
    {
        for (int j = -SIZE; j < SIZE; ++j)
        {
            ivec2 pos = ivec2(fragCoord.zw) + ivec2(i, j);
            if (pos.x < 0 || pos.y < 0 || pos.x >= _tex0Info.x || pos.y >= _tex0Info.y)
            {
                continue;
            }
            sum += texelFetch(_tex0, pos, 0);
            base += 1.0;
        }
    }

    fragColor = sum / base;
}

#include "../shaderLib/templateEnd.frag.glsl"