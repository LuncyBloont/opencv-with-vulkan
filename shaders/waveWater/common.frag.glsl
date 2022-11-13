#extension GL_GOOGLE_include_directive : require

precision highp float;

#include "../../shaderLib/templateHead.frag.glsl"

#include "./funcs.frag.glsl"

#define iResolution vec3(_frame.xy, 1.0)
#define iTime (_time.x)
#define iTimeDelta (_time.x / _time.w)
#define iFrame int(floor(_time.w + 0.1))
#define iFrameRate (_time.w / _time.x)
#define iMouse vec4(_mouse.xy, _mouse.xy)
#define iDate vec4(_time.x / 3600.0 / 24.0 / 356.0, _time.x / 3600.0 / 24.0 / 30.0, _time.x / 3600.0 / 24.0, _time.x)
#define iSampleRate 44100.0

// iChannel{i} should be defined at each buffer shader file for better compatible.