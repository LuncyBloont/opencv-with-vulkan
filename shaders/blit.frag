#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

#define SHOW_FOR_OPENCV

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    fragColor = texelFetch(_ref0, ivec2(fragCoord.zw), 0);
}

#include "../shaderLib/templateEnd.frag.glsl"