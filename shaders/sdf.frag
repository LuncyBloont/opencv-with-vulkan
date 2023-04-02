#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

vec4 release(in sampler2D old, in vec4 coord)
{
    int r = int(_vecLib[0].x);
    float scale = _vecLib[0].y;
    float pscale = _vecLib[0].z;

    vec4 oldval = texelFetch(old, ivec2(coord.zw), 0);
    if (oldval.x / pscale <= 1.0) { return oldval; }
    
    float mindis = 1e9;
    for (int x = -r; x <= r; x += 1)
    {
        for (int y = -r; y <= r; y += 1)
        {
            float disCS = length(vec2(x, y));
            float disSN = texelFetch(old, ivec2(coord.zw) + ivec2(x, y), 0).x / pscale;
            mindis = min(disCS + disSN, mindis); 
        }
    }
    return vec4(vec3(mindis * scale), 1.0);
}

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    if (_time.w < 0.5)
    {
        fragColor = release(_tex0, fragCoord);
    }
    else
    {
        fragColor = release(_ref0, fragCoord);
    }
}

#include "../shaderLib/templateEnd.frag.glsl"