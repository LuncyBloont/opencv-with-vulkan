#extension GL_GOOGLE_include_directive : require

#ifndef TEMPLATE_END_GLSL
#define TEMPLATE_END_GLSL

#include "templateHead.frag.glsl"

void main()
{
#ifdef SHOW_FOR_OPENCV
    vec4 coord = vec4(_uv.x, 1.0 - _uv.y, _uv.x * _frame.x, (1.0 - _uv.y) * _frame.y);
    _frag(coord, _outColor);
    _outColor = _outColor.bgra;
#else
    vec4 coord = vec4(_uv.xy, _uv.xy * _frame.xy);
    _frag(coord, _outColor);
#endif
}

#endif