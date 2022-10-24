#version 420

precision highp float;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 uv;

layout (location = 0) out vec4 fposition;
layout (location = 1) out vec4 fuv;

const vec4 screen[4] = vec4[](
    vec4(-1.0, -1.0, 0.0, 1.0),
    vec4(1.0, -1.0, 0.0, 1.0),
    vec4(1.0, 1.0, 0.0, 1.0),
    vec4(-1.0, 1.0, 0.0, 1.0)
);

void main()
{
    gl_Position = position;
    fposition = position;
    fuv = uv;
} 