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

float fractalHeart(vec3 pos, float h, float uvs)
{
    float d = sdfCone2(pos, h);
    float sub = 0.1;

    if (abs(d) > sub * 2.0)
    {
        return abs(d) - sub;
    }
    
    vec2 uv = vec2(
        atan(pos.z, pos.x),
        -atan(pos.y, length(pos.xz)) + _time.x * 0.5 + cos(_time.x * 6.0 + 3.1416 * 0.5) * 0.35
    ) * uvs;

    vec2 suv = fract(uv / 3.1415926 * 0.5) * _tex0Info.xy;

    float dp = texelFetch(_tex0, ivec2(suv), 0).r * (cos(uv.y + _time.x * 12.0) * 0.2 + 0.8);

    return abs(d) + 0.05 - dp * 0.15;
}

#define DECLARE_SCENE(fname, type, dInit, packFname) \
type fname(vec3 pos) \
{ \
    type s = dInit; \
    vec3 posForHeart = transform(pos, vec3(0.0), vec3(_mouse.y * 0.01 + 3.14159, -_mouse.x * 0.01, 0.0), 1.0); \
    float dance = cos(_time.x * 6.0) * 0.06; \
    float sacle = 0.7 + dance; \
    \
    s = fmin(s, packFname( \
            0.0, 0.0, \
            fractalHeart(transform(posForHeart, vec3(0.45, 0.5, 0.0), vec3(0.0, 0.0, -0.35 + dance * 0.51), sacle), 1.7, 1.0) * sacle, \
            1.0 \
        )); \
    \
    s = smin(s, packFname( \
            0.0, 0.0, \
            fractalHeart(transform(posForHeart, vec3(-0.45, 0.5, 0.0), vec3(0.0, 0.0, 0.35 - dance * 0.51), sacle), 1.7, 1.0) * sacle, \
            1.0 \
        ), 4.1); \
    \
    sacle = 0.9 + dance; \
    s = fmin(s, packFname( \
            0.0, 0.0, \
            fractalHeart(transform(posForHeart, vec3(-0.45, 0.5, 0.0), vec3(0.0, 0.0, 0.35 + dance * 0.51), sacle), 1.4, 2.0) * sacle, \
            1.0 \
        )); \
    \
    s = smin(s, packFname( \
            0.0, 0.0, \
            fractalHeart(transform(posForHeart, vec3(0.45, 0.5, 0.0), vec3(0.0, 0.0, -0.35 - dance * 0.51), sacle), 1.4, 2.0) * sacle, \
            1.0 \
        ), 4.1); \
    \
    return s; \
} \

float depthPack(float x, float y, float z, float w)
{
    return z;
}

vec4 surfacePack(float x, float y, float z, float w)
{
    return vec4(x, y, z, w);
}

DECLARE_SCENE(depthScene, float, FAR, depthPack)
DECLARE_SCENE(surfaceScene, vec4, vec4(0.0, 0.0, FAR, 0.0), surfacePack)

float march(vec3 dir, vec3 pos, float max_t)
{
    float d = 0.0;
    for (float i = 0.0; i < max_t; i += 1.0)
    {
        float dis = depthScene(pos + d * dir);
        d = d + dis * 0.5;

        if (dis < E * d || d > FAR)
        {
            return d;
        }
    }
    return FAR;
}

vec3 calNormal(vec3 pos)
{
    vec2 offset = vec2(1.0, -1.0);
    float d = depthScene(pos);
    return normalize(
        offset.xxy * (depthScene(pos + offset.xxy * E) - d) + 
        offset.xyx * (depthScene(pos + offset.xyx * E) - d) + 
        offset.yxx * (depthScene(pos + offset.yxx * E) - d) + 
        offset.yyx * (depthScene(pos + offset.yyx * E) - d) + 
        offset.yxy * (depthScene(pos + offset.yxy * E) - d) + 
        offset.xyy * (depthScene(pos + offset.xyy * E) - d) +
        offset.yyy * (depthScene(pos + offset.yyy * E) - d) +
        offset.xxx * (depthScene(pos + offset.xxx * E) - d)
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
    vec3 suncol = SUNCOL * 0.7;

    vec3 l2 = vec3(0.0, -1.0, 0.0);
    vec3 l2Col = vec3(1.0, 0.2, 0.15) * 1.4;

    float dis = march(dir, pos, MAX_T);
    vec4 surface = surfaceScene(pos + dir * dis);
    vec3 normal = calNormal(pos + dir * dis);

    float shadow = clamp(march(sun, pos + dir * dis + sun * E * 6.0, MAX_T / 4.0), 0.0, 1.0);
    float shadow2 = clamp(march(l2, pos + dir * dis + l2 * E * 6.0, MAX_T / 4.0), 0.0, 1.0);

    float subsurface = 0.5;

    vec3 col = albedo(ID(surface));

    vec3 face = col * ENV;

    face = mix(face, ENV * face, pow(1.0 - max(0.0, dot(normal, -dir)), 6.0));

    face += calLight(col, normal, dir, suncol, sun, shadow, subsurface);

    face += calLight(col, normal, dir, l2Col, l2, shadow2, subsurface);

    face = mix(face, ENV, pow(clamp(dis * 0.25, 0.0, 1.0), 3.0)); // fog

    fragColor = vec4((dis < FAR ? face : ENV) * clamp(1.7 - pow(length(fragCoord.xy * 2.0 - 1.0), 1.3), 0.0, 1.0), 1.0);
}

#include "../../shaderLib/templateEnd.frag.glsl"