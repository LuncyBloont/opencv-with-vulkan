#extension GL_GOOGLE_include_directive : require

#ifndef TEMPLATE_END_GLSL
#define TEMPLATE_END_GLSL

#include "templateHead.frag.glsl"

void main()
{
    vec4 coord = vec4(_uv.xy, _uv.xy * _frame.xy);
    _frag(coord, _outColor);
}

#endif