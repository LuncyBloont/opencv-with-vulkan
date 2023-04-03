#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    const ivec2 pos = ivec2(fragCoord.xy * _vecLib[0].xy + _vecLib[0].z);
}

#include "../shaderLib/templateEnd.frag.glsl"