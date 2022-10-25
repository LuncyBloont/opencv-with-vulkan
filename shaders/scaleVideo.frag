#version 420
#extension GL_GOOGLE_include_directive : require

precision highp float;

#include "../shaderLib/templateHead.frag.glsl"

void frag(in vec4 fragCoord, out vec4 fragColor)
{
    vec2 pos = fragCoord.xy * 2.0 - 1.0;
    vec2 scalePos = pos * 0.1;
    float len = length(pos);
    float x = clamp(len, 0.0, 1.0);
    vec2 smpUV = mix(scalePos, pos, 0.5 - 0.5 * cos(x * 3.1415926)) * 0.5 + 0.5;
    vec4 col = texture(tex0, smpUV);
    fragColor = col;
}

#include "../shaderLib/templateEnd.frag.glsl"