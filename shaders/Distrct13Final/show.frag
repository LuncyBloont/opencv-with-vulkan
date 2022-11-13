#version 420

#extension GL_GOOGLE_include_directive : require

#include "../../shaderLib/templateHead.frag.glsl"

#include "../waveWater/common.frag.glsl"

#include "./funclib.frag.glsl"

#define SHOW_FOR_OPENCV

#define iChannel0 _ref0

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 uv = fragCoord / iResolution.xy;
    
    vec3 col = texelFetch(iChannel0, ivec2(fragCoord), 0).xyz;
    
    col = pow(col * 0.72, vec3(0.86));
    
    col /= 1.0 + 0.7 * pow(length(uv * 2.0 - 1.0) * 0.8, 2.3);
    
    fragColor = vec4(col, 1.0);
}

#include "../../shaders/waveWater/execute.frag.glsl"
#include "../../shaderLib/templateEnd.frag.glsl"