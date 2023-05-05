#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    const ivec2 spos = clamp(ivec2(fragCoord.xy * _vecLib[0].xy / _vecLib[0].z), ivec2(0), ivec2(_vecLib[1].xy) - 1);
    const ivec2 pos = ivec2(fragCoord.xy * _vecLib[0].xy);
    
    // fragColor = texelFetch(_tex0, spos, 0);
    // return;
    
    const int offsetX[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    const int offsetY[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    
    const vec4 data = texelFetch(_tex1, pos, 0);

    uint A = uint(data.w * 255.0);
    uint B = uint(data.z * 255.0);
    float w = data.x / 255.0 + data.y;

    const ivec2 apos = clamp(spos + ivec2(offsetX[A], offsetY[A]), ivec2(0), ivec2(_vecLib[1].xy));
    const ivec2 bpos = clamp(spos + ivec2(offsetX[B], offsetY[B]), ivec2(0), ivec2(_vecLib[1].xy));

    fragColor = mix(texelFetch(_tex0, apos, 0), texelFetch(_tex0, bpos, 0), w);
}

#include "../shaderLib/templateEnd.frag.glsl"