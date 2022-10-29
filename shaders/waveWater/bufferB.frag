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

    vec4 col = texture(iChannel0, uv);
    
    fragColor = col;
}

#include "./execute.frag.glsl"