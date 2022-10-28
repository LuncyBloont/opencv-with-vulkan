#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

ivec2 uvFilter(vec2 raw)
{
    return ivec2(clamp(raw, vec2(0.0), _frameInfo.xy - 1.0));
}

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    if (_mouse.z > 0.5 || _time.w < 1.0 || _mouse.y > _frame.y * 0.9)
    {
        float size = max(1.0, _mouse.x * 64.0 / _frameInfo.x) * mix(1.0, (1.0 + cos(_time.x)) * 0.5, _mouse.y > _frame.y * 0.9);
        float sigmaSpace = _vecLib[0].x;
        float sigmaColor = _vecLib[0].y;
        vec3 col = texelFetch(_tex0, uvFilter(fragCoord.zw), 0).rgb;
        vec3 sumCol = vec3(0.0);
        float sumFac = 0.0;
        for (float i = -size; i <= size; i += 1.0)
        {
            for (float j = -size; j <= size; j += 1.0)
            {
                vec2 spUVOff = vec2(i, j);
                vec3 spCol = texelFetch(_tex0, uvFilter(fragCoord.zw + spUVOff), 0).rgb;
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
        fragColor = texelFetch(_ref0, ivec2(fragCoord.zw), 0);
    }
}

#include "../shaderLib/templateEnd.frag.glsl"