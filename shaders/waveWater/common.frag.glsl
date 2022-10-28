#extension GL_GOOGLE_include_directive : require

precision highp float;

#include "../../shaderLib/templateHead.frag.glsl"

#include "./funcs.frag.glsl"

#define iResolution vec3(_frame.xy, 1.0)
#define iTime (_time.x)
#define iTimeDelta (_time.x / _time.w)
#define iFrame int(_time.w)
#define iFrameRate (_time.w / _time.x)
#define iChannelTime float[3](_time.x, _time.x, _time.x);
#define iChannelResolution vec3[3](vec3(_ref0Info.xy, 1.0), vec3(_tex0Info.xy, 1.0), vec3(_tex1Info.xy, 1.0))
#define iMouse vec4(_mouse.xy, _mouse.xy)
#define iChannel0 _ref0
#define iChannel1 _tex0
#define iChannel2 _tex1
#define iDate vec4(_time.x / 3600.0 / 24.0 / 356.0, _time.x / 3600.0 / 24.0 / 30.0, _time.x / 3600.0 / 24.0, _time.x)
#define iSampleRate 44100.0