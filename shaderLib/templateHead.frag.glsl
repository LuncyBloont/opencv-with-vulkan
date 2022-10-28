#ifndef TEMPLATE_HEAD_GLSL
#define TEMPLATE_HEAD_GLSL

#define REF_CNT 3
#define TEX_CNT 3

precision highp float;

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 uv;

layout (binding = 0) uniform UniObject {
    mat4 mats[8];
    vec4 vecs[8 + 3 + REF_CNT + TEX_CNT];
} uni;

layout (binding = 1) uniform sampler2D references[REF_CNT];
layout (binding = 2) uniform sampler2D textures[TEX_CNT];

layout(location = 0) out vec4 outColor;

#define ref0 (references[0])
#define ref1 (references[1])
#define ref2 (references[2])

#define tex0 (textures[0])
#define tex1 (textures[1])
#define tex2 (textures[2])

#define time (uni.vecs[REF_CNT + TEX_CNT + 8])
#define frame (uni.vecs[REF_CNT + TEX_CNT + 1 + 8])
#define frameInfo (uni.vecs[REF_CNT + TEX_CNT + 1 + 8])
#define mouse (uni.vecs[REF_CNT + TEX_CNT + 2 + 8])

#define matLib (uni.mats)
#define vecLib (uni.vecs)

#define ref0Info (uni.vecs[8 + 0])
#define ref1Info (uni.vecs[8 + 1])
#define ref2Info (uni.vecs[8 + 2])

#define tex0Info (uni.vecs[8 + REF_CNT + 0])
#define tex1Info (uni.vecs[8 + REF_CNT + 1])
#define tex2Info (uni.vecs[8 + REF_CNT + 2])

void frag(in vec4 fragCoord, out vec4 fragColor);

#endif