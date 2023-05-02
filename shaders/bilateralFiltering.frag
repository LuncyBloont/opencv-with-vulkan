#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

ivec2 uvFilter(vec2 raw)
{
    return ivec2(clamp(raw, vec2(0.0), _frameInfo.xy - 1.0));
}

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    const int size = int(_vecLib[0].w);
    
    const float sigmaSpace = _vecLib[0].x;
    const float sigmaColor = _vecLib[0].y;

    const float ss2 = sigmaSpace * sigmaSpace;
    const float sc2 = sigmaColor * sigmaColor;
    
    const vec4 col = texelFetch(_tex0, uvFilter(fragCoord.zw), 0);
    vec4 sumCol = vec4(0.0);
    float sumFac = 0.0;
    for (int i = -size / 2; i <= size / 2; ++i)
    {
        for (int j = -size / 2; j <= size / 2; ++j)
        {
            const vec2 spUVOff = vec2(i, j);
            const vec4 spCol = texelFetch(_tex0, uvFilter(fragCoord.zw + spUVOff), 0);
            
            const float p = exp(-dot(spUVOff, spUVOff) / ss2) * exp(-dot(spCol - col, spCol - col) * 255.0 * 255.0 / sc2);
            
            sumCol += spCol * p;
            sumFac += p;
        }
    }
    fragColor = sumCol / sumFac;
}

#include "../shaderLib/templateEnd.frag.glsl"