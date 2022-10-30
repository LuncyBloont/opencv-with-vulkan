#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

#define SHOW_FOR_OPENCV
// #define LAZY_UPDATE

ivec2 uvFilter(vec2 raw)
{
    return ivec2(clamp(raw, vec2(0.0), _frameInfo.xy - 1.0));
}

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    float paddingX = 6.0;
    float posY = 24.0;
    float sizeH = 16.0;
    float inPaddingX = 10.0;
    float inSizeH = 4.0;

#ifdef LAZY_UPDATE
    if ((_mouse.z > 0.5 && 
            abs(_mouse.y - (_frame.y - posY)) < inSizeH && abs(_mouse.x / _frame.x - 0.5) < 0.5 - inPaddingX / _frame.x
        ) || _time.w < 1.0)
    {
#endif
        float size = max(1.0, _vecLib[0].w * (_mouse.x - inPaddingX) / (_frameInfo.x - inPaddingX * 2.0));
        
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
                
                float p = exp(-dot(spUVOff, spUVOff) / 2.0 / pow(sigmaSpace, 2.0));
                
                if (_vecLib[0].z > 0.5)
                {
                    p *= exp(-dot((spCol - col) * 256.0, (spCol - col) * 256.0) * 3.0 / 2.0 / pow(sigmaColor, 2.0));
                
                }
                sumCol += spCol * p;
                sumFac += p;
            }
        }
        fragColor = vec4(sumCol / sumFac, 1.0);

        /* --------- UI Widget ------ */

        if (abs(fragCoord.w - (_frame.y - posY)) < inSizeH && abs(fragCoord.x - 0.5) < 0.5 - inPaddingX / _frame.x)
        {
            if (fragCoord.z < _mouse.x)
            {
                fragColor = mix(fragColor, vec4(0.6, 0.7, 0.2, 1.0), 0.6);
            }
        }
        else if (abs(fragCoord.w - (_frame.y - posY)) < sizeH && abs(fragCoord.x - 0.5) < 0.5 - paddingX / _frame.x)
        {
            fragColor = mix(fragColor, vec4(0.1, 0.1, 0.1, 1.0), 0.6);
        }

#ifdef LAZY_UPDATE
    }
    else
    {
        fragColor = texelFetch(_ref0, ivec2(fragCoord.zw), 0);
    }
#endif
}

#include "../shaderLib/templateEnd.frag.glsl"