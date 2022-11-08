#version 420

#extension GL_GOOGLE_include_directive : require
#define SHOW_FOR_OPENCV

#include "../../shaderLib/templateHead.frag.glsl"

#define SUN vec3(0.4, 2.2, -0.4)
#define SUNCOL vec3(1.5, 1.48, 1.45)
#define COL0 vec3(1.0, 0.99, 0.99)
#define ENV vec3(0.1, 0.13, 0.21)
#define SUB0 vec3(0.8, 0.3, 0.23)

#include "kit.frag.glsl"

vec4 scene(vec3 pos)
{
    vec4 s = vec4(0.0, 0.0, FAR, 0.0);
    float d;
    vec3 posForHeart = transform(pos, vec3(0.0), vec3(_mouse.y * 0.01, _mouse.x * 0.01, 0.0), 1.0);
    
    float dance = cos(_time.x * 6.0) * 0.06;
    float sacle = 0.7 + dance;
    // d = sdfCone2(transform(posForHeart, vec3(0.45, 0.5, 0.0), vec3(0.0, 0.0, -0.35 + dance * 0.51), sacle), 1.7) * sacle;
    s = fmin(s, vec4(
            0.0, 0.0, 
            sdfCone2(transform(posForHeart, vec3(0.45, 0.5, 0.0), vec3(0.0, 0.0, -0.35 + dance * 0.51), sacle), 1.7) * sacle,
            1.0
        ));

    // d = sdfCone2(transform(posForHeart, vec3(-0.45, 0.5, 0.0), vec3(0.0, 0.0, 0.35 - dance * 0.51), sacle), 1.7) * sacle;
    s = smin(s, vec4(
            0.0, 0.0, 
            sdfCone2(transform(posForHeart, vec3(-0.45, 0.5, 0.0), vec3(0.0, 0.0, 0.35 - dance * 0.51), sacle), 1.7) * sacle,
            2.0
        ), 2.1);

    return s;
}

vec4 march(vec3 dir, vec3 pos)
{
    vec4 s = vec4(0.0, 0.0, 0.0, 0.0);
    for (uint i = 0; i < MAX_T; ++i)
    {
        vec4 dis = scene(pos + DIS(s) * dir);
        s = vec4(UV(dis), DIS(dis) + DIS(s), ID(dis));

        if (DIS(dis) < E)
        {
            return s;
        }
    }
    return vec4(0.0, 0.0, FAR, 0.0);
}

vec3 calNormal(vec3 pos)
{
    vec2 offset = vec2(1.0, -1.0);
    vec4 s = scene(pos);
    return normalize(
        offset.xxy * (DIS(scene(pos + offset.xxy * E)) - DIS(s)) + 
        offset.xyx * (DIS(scene(pos + offset.xyx * E)) - DIS(s)) + 
        offset.yxx * (DIS(scene(pos + offset.yxx * E)) - DIS(s)) + 
        offset.yyx * (DIS(scene(pos + offset.yyx * E)) - DIS(s)) + 
        offset.yxy * (DIS(scene(pos + offset.yxy * E)) - DIS(s)) + 
        offset.xyy * (DIS(scene(pos + offset.xyy * E)) - DIS(s)) +
        offset.yyy * (DIS(scene(pos + offset.yyy * E)) - DIS(s)) +
        offset.xxx * (DIS(scene(pos + offset.xxx * E)) - DIS(s))
    );
}

vec3 albedo(float id)
{
    vec3 arr[] = vec3[](ENV, COL0, vec3(0.4, 0.7, 0.1));
    uint i = uint(id);
    float fac = fract(id);
    return mix(arr[i], arr[i + 1], fac);
}

void _frag(in vec4 fragCoord, out vec4 fragColor)
{
    vec2 vpos = (fragCoord.xy * 2.0 - 1.0) * vec2(_frame.x / _frame.y, 1.0);
    float scale = 2.0;

    vec3 dir = normalize(vec3(vpos, 1.0));
    vec3 pos = vec3(0.0, 0.0, -3.0);
    vec3 sun = normalize(SUN);

    vec4 surface = march(dir, pos);
    vec3 normal = calNormal(pos + dir * DIS(surface));

    float shadow = clamp(DIS(march(sun, pos + dir * DIS(surface) + sun * E * 8.0)), 0.0, 1.0);

    float ntol = dot(normal, sun);
    float subsurface = 0.5;

    vec3 col = albedo(ID(surface));

    vec3 face = mix(col * max(0.0, ntol) * SUNCOL * shadow, SUB0 * (0.5 + 0.5 * ntol) * SUNCOL, subsurface) + col * ENV;

    fragColor = vec4(DIS(surface) < FAR ? face : ENV, 1.0);
}

#include "../../shaderLib/templateEnd.frag.glsl"