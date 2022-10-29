#version 420

#extension GL_GOOGLE_include_directive : require

#include "./common.frag.glsl"

#define iChannel0 _ref0
#define iChannel1 _tex0

/*
 * Copyright (c) 2022 LuncyTB. All rights reserved.
 */

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord / iResolution.xy;

    fragColor = texture(iChannel0, uv);
    
    vec4 wave = texture(iChannel1, uv * 6.0 + vec2(0.044, -0.053) * iTime);
    wave = mix(wave, texture(iChannel1, uv * 6.0 * 0.56 + vec2(-0.052, 0.047) * iTime), 0.5);
    
    fragColor += mix(vec4(0.0), wave * 4.0, pow(fragColor.r, 0.95) + 0.001);
}

#include "./execute.frag.glsl"