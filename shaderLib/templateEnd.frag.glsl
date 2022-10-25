#extension GL_GOOGLE_include_directive : require

#ifndef TEMPLATE_END_GLSL
#define TEMPLATE_END_GLSL

#include "templateHead.frag.glsl"

void main()
{
    vec4 coord = vec4(uv.xy, uv.xy * frame.xy);
    frag(coord, outColor);
}

#endif