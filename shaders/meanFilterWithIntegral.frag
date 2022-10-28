#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

precision highp int;

#define size 32

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    ivec2 pos = ivec2(fragCoord.zw);
    ivec2 p00 = clamp(pos - ivec2(size), ivec2(0), ivec2(_tex0Info.xy - 1));
    ivec2 p11 = clamp(pos + ivec2(size), ivec2(0), ivec2(_tex0Info.xy - 1));
    ivec2 p01 = clamp(pos + ivec2(-size, size), ivec2(0), ivec2(_tex0Info.xy - 1));
    ivec2 p10 = clamp(pos + ivec2(size, -size), ivec2(0), ivec2(_tex0Info.xy - 1));

    fragColor = texelFetch(_tex0, p11, 0) + texelFetch(_tex0, p00, 0) - texelFetch(_tex0, p01, 0) - texelFetch(_tex0, p10, 0);
    fragColor = fragColor / float(p11.x - p00.x) / float(p11.y - p00.y) / 255.0;
}

#include "../shaderLib/templateEnd.frag.glsl"