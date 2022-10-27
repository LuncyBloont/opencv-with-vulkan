#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

void frag(in vec4 fragCoord, out vec4 fragColor)
{
    float size = 1.5;
    vec3 n = vec3(0.0);
    float base = 0.0;

    float s = dot(texture(tex0, fragCoord.xy).rgb, vec3(1.0 / 3.0));

    for (float i = -size; i <= size; i += 1.0)
    {
        for (float j = -size; j <= size; j += 1.0)
        {
            vec2 uv0 = fragCoord.zw + vec2(i, j);
            uv0 /= frame.xy;

            vec2 uv1 = fragCoord.zw + vec2(-j, i);
            uv1 /= frame.xy;

            float p = cos(clamp(length(vec2(i, j)) / size, 0.0, 1.0) * 3.14159) * 0.5 + 0.5;

            float s0 = dot(texture(tex0, uv0).rgb, vec3(1.0 / 3.0));
            float s1 = dot(texture(tex0, uv1).rgb, vec3(1.0 / 3.0));
            n += normalize(cross(vec3(i, j, s0 - s), vec3(-j, i, s1 - s)));
            base += p;
        }
    }

    n = (n / base);

    n.z *= 0.02;

    n = normalize(n);

    fragColor = vec4(n.bgr * vec3(1.0, -1.0, 1.0) * 0.5 + 0.5, 1.0);
}

#include "../shaderLib/templateEnd.frag.glsl"
