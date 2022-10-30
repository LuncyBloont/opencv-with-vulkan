#version 420

#extension GL_GOOGLE_include_directive : require

#include "./common.frag.glsl"

#define iChannel0 _ref0
#define iChannel1 _tex0
#define iChannel2 _tex1

#define SHOW_FOR_OPENCV

/*
 * Copyright (c) 2022 LuncyTB. All rights reserved.
 */

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;
    vec4 pzz = texture(iChannel0, uv);
    vec4 piz = texture(iChannel0, uv - vec2(-1.0, 0.0) / iResolution.xy);
    vec4 ppz = texture(iChannel0, uv - vec2(1.0, 0.0) / iResolution.xy);
    vec4 pzi = texture(iChannel0, uv - vec2(0.0, -1.0) / iResolution.xy);
    vec4 pzp = texture(iChannel0, uv - vec2(0.0, 1.0) / iResolution.xy);
    
    vec3 nor = cross(vec3(-1.0, 0.0, piz.r - pzz.r), vec3(0.0, 1.0, pzp.r - pzz.r)) + 
        cross(vec3(0.0, 1.0, pzp.r - pzz.r), vec3(1.0, 0.0, ppz.r - pzz.r)) + 
        cross(vec3(1.0, 0.0, ppz.r - pzz.r), vec3(0.0, -1.0, pzi.r - pzz.r)) + 
        cross(vec3(0.0, -1.0, pzi.r - pzz.r), vec3(-1.0, 0.0, piz.r - pzz.r));
    nor *= vec3(1.0, 1.0, 0.09);
    nor = -normalize(nor);
    
    vec4 sky = vec4(0.77, 0.88, 0.99, 1.0);

    // Output to screen
    fragColor = texture(iChannel1, (fragCoord * 1.0 + nor.xy * 1200.0) / iResolution.xy) * 
        vec4(0.5, 0.7, 1.0, 1.0) * 1.5;
    fragColor = mix(fragColor, vec4(0.9, 0.91, 0.99, 1.0) * sky, 
        pow(pzz.r * texture(iChannel2, uv * 12.0).r * 1.2, 0.5));
    
    vec2 mpos = boat(iTime, iResolution.xy);
    if (distance(mpos, fragCoord) < 5.0)
    {
        fragColor = vec4(0.3, 0.4, 0.31, 1.0) * 1.1 * sky;
    }
    else if (distance(mpos, fragCoord) < 7.0)
    {
        vec2 offset = normalize(fragCoord - mpos);
        fragColor = vec4(0.3, 0.4, 0.31, 1.0) * 
            (0.8 + 0.45 * max(0.0, dot(offset, normalize(vec2(1.0, 0.4))))) *
            sky;
    }
    else if (distance(mpos - vec2(1.0, 0.4) * 3.2, fragCoord) < 12.0)
    {
        vec2 offset = normalize(fragCoord - mpos);
        fragColor *= 0.5 + 0.5 * vec4(1.0) * 
            pow(distance(mpos - vec2(1.0, 0.4) * 3.2, fragCoord) / 12.0, 0.7);
    }
}

#include "./execute.frag.glsl"