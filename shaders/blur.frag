#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    float size = 15.0;
    vec4 col = vec4(0.0);
    float base = 0.0;

    for (float i = -size; i <= size; i += 1.0)
    {
        for (float j = -size; j <= size; j += 1.0)
        {
            vec2 uv = fragCoord.zw + vec2(i, j);
            uv /= _frame.xy;
            float p = cos(clamp(length(vec2(i, j)) / size, 0.0, 1.0) * 3.14159) * 0.5 + 0.5;
            col += texture(_tex0, uv) * p;
            base += p;
        }
    }

    fragColor = col / base;
}

#include "../shaderLib/templateEnd.frag.glsl"
