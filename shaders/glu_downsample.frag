#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    const ivec2 pos = clamp(ivec2(ivec2(fragCoord.xy * _vecLib[0].xy + 0.5)), ivec2(0), ivec2(_vecLib[1].xy) - 1);
    fragColor = texelFetch(_tex0, pos, 0);
}

#include "../shaderLib/templateEnd.frag.glsl"