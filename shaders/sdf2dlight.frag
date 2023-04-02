#version 420

#extension GL_GOOGLE_include_directive : require

#include "../shaderLib/templateHead.frag.glsl"

#define SHOW_FOR_OPENCV

float scene(in vec2 pos)
{
    // return max(0.0,  distance(pos, vec2(300.0, 300.0)) - 14.0);
    return textureLod(_tex0, pos / _tex0Info.xy, 0.0).x / 0.01 - 1.0;
}

void _frag(in vec4 coord, out vec4 fragColor)
{
    vec2 light = _mouse.w > 0.5 ? _frameInfo.xy / 2.0 : _mouse.xy;
    vec2 pos = coord.zw;
    vec2 dir = normalize(pos - light);
    vec2 stop = light;
    float dis2l = distance(pos, light);

    float time = 0.0;
    float dis = 3.0;

    float hit = 0.0;
    float solid = (scene(pos) < 0.01 ? 1.0 : 0.0);

    for (int i = 0; i < 64 && dis < dis2l; i += 1)
    {
        time += 1.0;
        stop = light + dir * dis;
        float d = scene(stop);
        dis += d;

        hit = (dis >= dis2l ? 0.0 : 1.0);
        if (hit < 0.5) { break; }
        if (d < 0.01) { hit = 1.0; break; }
    }

    if (_mouse.z > 0.5)
    {
        fragColor = vec4(mix(vec3(1.0, 0.5, 0.0), vec3(0.0, 0.5, 1.0), 1.0 - pow(time / 64.0, 7.0)), 1.0);
    }
    else
    {
        vec3 nC = (solid > 0.5 ? vec3(0.3, 0.7, 0.4) : vec3(0.5, 0.5, 0.3));
        vec3 lit = 20000.0 / (pow(120.0, 2.0) + pow(dis2l, 2.0)) * vec3(1.0, 0.99, 0.95);
        vec3 env = vec3(0.4, 0.6, 0.7) * 0.4;
        // fragColor = vec4(distance(stop, light) / 100.0);
        fragColor = vec4(nC * lit * (1.0 - hit) + nC * env, 1.0);
    }
}

#include "../shaderLib/templateEnd.frag.glsl"