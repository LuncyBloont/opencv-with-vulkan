#version 420

precision highp float;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 uv;

layout (binding = 0) uniform UniObject {
    mat4 mats[8];
    vec4 vecs[16];
} uni;

layout (binding = 1) uniform sampler2D references[3];
layout (binding = 2) uniform sampler2D textures[3];

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = vec4(uv.xy, fract(uni.vecs[6].x), 1.0) * texture(textures[0], uv.xy);
}