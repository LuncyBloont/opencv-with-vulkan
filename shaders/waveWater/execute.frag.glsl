#extension GL_GOOGLE_include_directive : require

precision highp float;

void mainImage(out vec4 fragColor, in vec2 fragCoord);

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    mainImage(fragColor, fragCoord.zw);
}

#include "../../shaderLib/templateEnd.frag.glsl"