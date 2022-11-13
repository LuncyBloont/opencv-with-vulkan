#version 420

precision highp float;

#extension GL_GOOGLE_include_directive : require

#include "../../shaderLib/templateHead.frag.glsl"

#include "../waveWater/common.frag.glsl"

#include "./funclib.frag.glsl"

#define iChannel0 _ref0
#define iChannel1 _ref1

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    ivec2 p = ivec2(fragCoord);
    ivec2 update;
    
    update = ivec2((iFrame % (BLOCK * BLOCK)) / BLOCK, iFrame % BLOCK);
    
    if (p % BLOCK == update)
    {
        fragColor = texelFetch(iChannel1, p / BLOCK, 0);
    }
    else
    {
        fragColor = texelFetch(iChannel0, p, 0);
    }
}

#include "../../shaders/waveWater/execute.frag.glsl"
#include "../../shaderLib/templateEnd.frag.glsl"