#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

ivec2 uvFilter(vec2 raw)
{
    return ivec2(clamp(raw, vec2(0.0), frameInfo.xy - 1.0));
}

void frag(in vec4 fragCoord, out vec4 fragColor)
{
    if (mouse.z > 0.5 || time.w < 1.0 || mouse.y > frame.y * 0.9)
    {
        float size = max(1.0, mouse.x * 64.0 / frameInfo.x) * mix(1.0, (1.0 + cos(time.x)) * 0.5, mouse.y > frame.y * 0.9);
        float sigmaSpace = vecLib[0].x;
        float sigmaColor = vecLib[0].y;
        vec3 col = texelFetch(tex0, uvFilter(fragCoord.zw), 0).rgb;
        vec3 sumCol = vec3(0.0);
        float sumFac = 0.0;
        for (float i = -size; i <= size; i += 1.0)
        {
            for (float j = -size; j <= size; j += 1.0)
            {
                vec2 spUVOff = vec2(i, j);
                vec3 spCol = texelFetch(tex0, uvFilter(fragCoord.zw + spUVOff), 0).rgb;
                float p = exp(-dot(spUVOff, spUVOff) / 2.0 / pow(sigmaSpace, 2.0)) * 
                    exp(-dot(spCol - col, spCol - col) / 2.0 / pow(sigmaColor, 2.0));
                sumCol += spCol * p;
                sumFac += p;
            }
        }
        fragColor = vec4(sumCol / sumFac, 1.0);
    }
    else
    {
        fragColor = texelFetch(ref0, ivec2(fragCoord.zw), 0);
    }
}

#include "../shaderLib/templateEnd.frag.glsl"