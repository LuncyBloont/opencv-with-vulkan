#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

float limitU(float u)
{
    return clamp(u, 0.0, (_tex1Info.x - 1.0) / _tex1Info.x);
}

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    vec4 raw = texelFetch(_tex0, ivec2(fragCoord.zw), 0);
    float changeScale = _vecLib[0][0];
    fragColor = clamp(vec4(
        texture(_tex1, vec2(limitU(raw.r), 0.0)).r,
        texture(_tex1, vec2(limitU(raw.g), 0.0)).g,
        texture(_tex1, vec2(limitU(raw.b), 0.0)).b,
        texture(_tex1, vec2(limitU(raw.a), 0.0)).a
    ), 0.0, 1.0);

    fragColor = mix(fragColor, raw, pow(abs(fragColor - raw), vec4(changeScale)));
}

#include "../shaderLib/templateEnd.frag.glsl"