#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    const ivec2 pos = ivec2(fragCoord.xy * _vecLib[0].xy);
    const ivec2 root = ivec2(pos / _vecLib[0].z);
    
    // fragColor = texelFetch(_ref0, root, 0);
    // return;

    const int offsetX[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
    const int offsetY[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
    float dis[9];
    vec4 near[9];
    
    float minV = 1e9;
    uint A = 0;
    uint B = 0;
    
    const vec4 col = texelFetch(_tex0, pos, 0);
    
    for (uint i = 0; i < 9; ++i)
    {
        const ivec2 cpos = ivec2(offsetX[i], offsetY[i]) + root;
        near[i] = texelFetch(_ref0, cpos, 0);
    }
    
    for (uint i = 0; i < 9; ++i)
    {
        dis[i] = distance(col, near[i]) + 0.00001;
        const bool con = dis[i] < minV;
        A = con ? i : A;
        minV = con ? dis[i] : minV; 
    }
    
    minV = 1e9;
    for (uint i = 0; i < 9; ++i)
    {
        float w = dis[i] / (dis[A] + dis[i]);
        const vec4 diff = col - mix(near[i], near[A], w);
        float err = dot(diff, diff);
        const bool con = err < minV;
        B = con ? i : B;
        minV = con ? err : minV;
    }
    
    const float bw = dis[A] / (dis[A] + dis[B]);
    
    fragColor = vec4(fract(bw * 255.0), bw, B / 255.0, A / 255.0);
}

#include "../shaderLib/templateEnd.frag.glsl"