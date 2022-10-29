#version 420

#extension GL_GOOGLE_include_directive : require

#include "./common.frag.glsl"

#define iChannel0 _ref0

/*
 * Copyright (c) 2022 LuncyTB. All rights reserved.
 */

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord/iResolution.xy;
    
    vec2 mpos = boat(iTime, iResolution.xy);
    
    if (distance(mpos, fragCoord) < 5.0)
    {
        fragColor = vec4(1.0 * (0.7 + cos(iTime * 520.0) * 0.3));   
        return;
    }
    
    if (distance(iMouse.zw, fragCoord) < 5.0)
    {
        fragColor = vec4(1.0);   
        return;
    }
    
    vec4 sum = vec4(0.0);
    float base = 0.0;
    for (float r = 0.0; r < 6.28; r += 0.1)
    {
        for (float l = 0.1; l < 1.0; l += 0.1)
        {
            vec4 s = texture(iChannel0, uv + toScreenScale(vec2(cos(r) * l, sin(r) * l) * 0.005, iResolution.xy));
            float p = sigmod(l);
            base += p;
            sum += s * p;
        }
    }
    
    fragColor = sum / base * 0.98;
}

#include "./execute.frag.glsl"