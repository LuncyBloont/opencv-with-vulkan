#ifndef TEMPLATE_HEAD_GLSL
#define TEMPLATE_HEAD_GLSL

#define REF_CNT 3
#define TEX_CNT 3

precision highp float;

layout(location = 0) in vec4 _position;
layout(location = 1) in vec4 _uv;

layout (binding = 0) uniform UniObject {
    mat4 mats[8];
    vec4 vecs[8 + 3 + REF_CNT + TEX_CNT];
} _uni;

layout (binding = 1) uniform sampler2D _references[REF_CNT];
layout (binding = 2) uniform sampler2D _textures[TEX_CNT];

layout(location = 0) out vec4 _outColor;

#define _ref0 (_references[0])
#define _ref1 (_references[1])
#define _ref2 (_references[2])

#define _tex0 (_textures[0])
#define _tex1 (_textures[1])
#define _tex2 (_textures[2])

#define _time (_uni.vecs[REF_CNT + TEX_CNT + 8])
#define _frame (_uni.vecs[REF_CNT + TEX_CNT + 1 + 8])
#define _frameInfo (_uni.vecs[REF_CNT + TEX_CNT + 1 + 8])
#define _mouse (_uni.vecs[REF_CNT + TEX_CNT + 2 + 8])

#define _matLib (_uni.mats)
#define _vecLib (_uni.vecs)

#define _ref0Info (_uni.vecs[8 + 0])
#define _ref1Info (_uni.vecs[8 + 1])
#define _ref2Info (_uni.vecs[8 + 2])

#define _tex0Info (_uni.vecs[8 + REF_CNT + 0])
#define _tex1Info (_uni.vecs[8 + REF_CNT + 1])
#define _tex2Info (_uni.vecs[8 + REF_CNT + 2])

void _frag(in vec4 fragCoord, out vec4 fragColor);

#endif