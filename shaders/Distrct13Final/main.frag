#version 420

#extension GL_GOOGLE_include_directive : require

#include "../../shaderLib/templateHead.frag.glsl"

#include "../waveWater/common.frag.glsl"

#include "./funclib.frag.glsl"

#define iChannel0 _ref0
#define iChannel1 _tex0
#define iChannel2 _tex1

vec3 blurSky(vec3 normal)
{
    return SKYCOL - 
        0.031 * max(0.0, dot(normal, CLOUD0)) -
        0.03 * max(0.0, dot(normal, CLOUD0)) -
        max(0.0, -normal.z) * 0.1;
}

vec4 ObjTestTransform(vec3 pos)
{
    return vec4(transform(pos, vec3(1.9, 1.8, 0.0), vec3(0.0, 0.0, -1.83), 0.4), 0.4);
}

float ObjTest(vec3 pos)
{
    float d = SDFCube(pos + vec3(0.0, 0.0, -0.6), vec4(0.4, 1.5, 1.85, 0.0));
    if (d < 0.06)
    {
        vec3 subPos = vec3(pos.x, pos.y, mod(pos.z, 0.1) - 0.05);
        d = nmin(d, SDFCube(subPos, vec4(0.415, 1.515, 0.00, 0.01)));
    }
    
    if (d < 2.0)
    {
        d = nmin(d, SDFCube(pos - vec3(0.0, 0.5, 2.55), vec4(0.355, 0.515, 0.1, 0.00)));
        d = nmin(d, SDFCube(pos - vec3(0.0, 0.85, 2.75), vec4(0.015, 0.015, 0.4, 0.00)));
        d = nmin(d, SDFCube(pos - vec3(0.1, 0.75, 2.75), vec4(0.015, 0.015, 0.76, 0.00)));
    }
    
    float d0 = SDFCube(pos - vec3(-1.0, 0.8, 1.0), vec4(0.06, 0.06, 0.07, 0.00));
    if (d0 < 2.8)
    {
        d0 = nmin(d0, SDFCube(pos - vec3(-1.0, 0.8, 1.3), vec4(0.035, 0.215, 0.03, 0.00)));
        d0 = nmin(d0, SDFCube(pos - vec3(-1.2, 0.8, 1.3), vec4(0.195, 0.065, 0.01, 0.00)));
        d0 = nmin(d0, SDFCube(pos - vec3(-1.0, 0.8, 1.0), vec4(0.02, 0.02, 0.3, 0.00)));
    }
    
    d = nmin(d, d0);
    
    return d;
}

float ObjTestP0(vec3 pos)
{
    float d = SDFCube(pos - vec3(-0.3, 0.8, -0.1), vec4(0.75, 0.01, 1.5, 0.12));
    
    if (d < 0.2)
    {
        float d0 = SDFCube(pos - vec3(-0.3, 0.8, 0.86), vec4(0.76, 0.02, 0.02, 0.13));
        d0 = -nmin(-d0, SDFCube(pos - vec3(-0.3, 0.8, 0.33), vec4(2.0, 0.8, 0.5, 0.0)));
        d = nmin(d, d0);
    }
    
    d = -nmin(-d, SDFCube(pos - vec3(-0.3, 0.8, 1.4), vec4(2.0, 0.8, 0.5, 0.0)));
    
    d = smin(d, SDFSphere(pos * 1.2 - vec3(-0.3, 0.8, -0.4) ) / 1.2, 5.1);
    d = smin(d, SDFSphere(pos * 1.2 - vec3(-0.3, 0.8, -1.1) ) / 1.2, 5.1);
    
    
    if (d < 0.2)
    {
        d = -nmin(-d, SDFCube(pos - vec3(-0.95, 0.9, -0.24), vec4(0.07, 0.26, 1.0, 0.0)));
        d = -nmin(-d, SDFCube(pos - vec3(-0.7, 0.9, -0.24), vec4(0.07, 0.26, 1.0, 0.0)));
    }
    
    return d;
}

float ObjTestP1(vec3 pos)
{
    float d = SDFSphere((pos - vec3(-4.3, 0.8, 0.95)) * 3.4) / 3.4;
    d = -nmin(-d, SDFCube((pos - vec3(-4.3, 0.8, 0.95)), vec4(1.0, 1.0, 0.03, 0.0)));
    
    return d;
}

float ObjTestP2(vec3 pos)
{
    float dk = SDFSphere((pos - vec3(-4.3, 0.0, 0.95)) * 3.4) / 3.4;
    
    float d = FAR;
    
    if (dk < 2.0)
    {
        d = nmin(d, SDFCube(pos - vec3(-4.3, 0.8, 1.45), vec4(0.005, 0.005, 0.23, 0.0)));
        d = nmin(d, SDFCube(pos - vec3(-4.3, 0.8, 1.24), vec4(0.02, 0.02, 0.13, 0.0)));
        d = nmin(d, SDFCube(pos - vec3(-4.43, 0.85, 0.55), vec4(0.007, 0.007, 0.23, 0.0)));
        d = nmin(d, SDFCube(pos - vec3(-4.19, 0.70, 0.55), vec4(0.007, 0.007, 0.23, 0.0)));
        d = nmin(d, SDFCube(pos - vec3(-4.25, 0.87, 0.55), vec4(0.007, 0.007, 0.23, 0.0)));
    }
    
    return d;
}

float ObjTestP3(vec3 pos)
{
    
    float d = FAR;
    
    d = nmin(d, SDFCube(pos - vec3(-4.3, 0.8, 0.64), vec4(0.01, 0.01, 0.01, 0.0)));
    
    return d;
}

vec2 ObjTestUV(vec3 pos)
{
    return pos.xy;
}

vec4 ObjGroundT(vec3 pos)
{
    return vec4(transform(pos, vec3(-4.7, -0.55, 0.7), vec3(0.0), 1.0), 1.0);
}

float SDFRock(vec3 pos, float r)
{
    return length(pos) - r;
}

float ObjGround(vec3 pos)
{
    float k;
    float m;
    float h = 0.5;
    float r = 0.7;
    float d = FAR;
    
    k = hash2(floor(pos.xy / 2.0));
    m = 0.3 + k * 0.7;
    d = nmin(d, SDFRock(vec3(mod(pos.xy, 2.0), pos.z - k * h), r * m));
    
    k = hash2(floor(pos.xy / 2.0 + vec2(1.0, 0.0)));
    m = 0.3 + k * 0.7;
    d = nmin(d, SDFRock(vec3(mod(pos.xy, 2.0) - vec2(2.0, 0.0), pos.z - k * h), r * m));
    
    k = hash2(floor(pos.xy / 2.0 + vec2(0.0, 1.0)));
    m = 0.3 + k * 0.7;
    d = nmin(d, SDFRock(vec3(mod(pos.xy, 2.0) - vec2(0.0, 2.0), pos.z - k * h), r * m));
    
    k = hash2(floor(pos.xy / 2.0 + vec2(1.0, 1.0)));
    m = 0.3 + k * 0.7;
    d = nmin(d, SDFRock(vec3(mod(pos.xy, 2.0) - vec2(2.0, 2.0), pos.z - k * h), r * m));
    
    return d;
}

float ObjGround2(vec3 pos)
{
    return SDFGround(pos + vec3(0.0, 0.0, 0.5));
}

float ObjHills(vec3 pos, float bias)
{
    float d = FAR;
    d = nmin(d, ObjGround2(pos));
    
    if (d > 4.0 + bias)
    {
        return d;
    }
    
    d = smin(d, ObjGround(pos), 0.67);
    
    if (d < 2.1 + bias)
    {
        float d0 = FAR;
        d0 = nmin(d0, ObjGround((pos + vec3(62.3433, 18.1213, -0.5)) * 6.0) / 6.0);
        d0 = nmin(d0, ObjGround((pos + vec3(35.4123, 84.9931, -1.0)) * 6.0) / 6.0);
        d0 = nmin(d0, ObjGround((pos + vec3(12.7542, 55.5973, -1.5)) * 6.0) / 6.0);

        d0 = -smin(-d0, -d + 0.05, 7.3);

        d = smin(d, d0, 2.4);
        
        if (d < 1.6 + bias)
        {
            float d1 = FAR;
            d1 = nmin(d1, ObjGround((pos + vec3(47.3351, 11.7521, -0.5)) * 6.0) / 6.0);
            d1 = nmin(d1, ObjGround((pos + vec3(89.5073, 67.6396, -0.75)) * 6.0) / 6.0);
            d1 = nmin(d1, ObjGround((pos + vec3(38.5951, 31.2831, -1.0)) * 6.0) / 6.0);
            d1 = nmin(d1, ObjGround((pos + vec3(41.2641, 38.7748, -1.25)) * 6.0) / 6.0);
            d1 = nmin(d1, ObjGround((pos + vec3(26.7448, 76.4833, -1.5)) * 6.0) / 6.0);

            d1 = -smin(-d1, -d + 0.06, 12.5);

            d = smin(d, d1, 3.6);
        }
    }
    
    if (d < 0.1 + bias)
    {
        d = d - textureLod(iChannel1, pos.xy * 1.4 + 1.0, 0.0).r * 0.028;
        d = d - textureLod(iChannel1, pos.xy * 3.0, 0.0).r * 0.0115;
        d = d - textureLod(iChannel1, pos.xy * 4.0, 0.0).r * 0.0063;
        d = d - textureLod(iChannel1, pos.xy * 8.0, 0.0).r * 0.0035;
    }
    
    return d;
}

vec2 ObjGroundUV(vec3 pos)
{
    return pos.xy;
}

vec4 ObjWaterT(vec3 pos)
{
    return vec4(transform(pos, vec3(0.0, 0.0, 0.35), vec3(0.0), 1.0), 1.0);
}

float ObjWater(vec3 pos, float bias)
{
    float h = 0.001; 
    float b = SDFGround(pos);
    if (b < h * 1.5 + bias)
    {
        float offset = 0.0;
        offset -= textureLod(iChannel2, pos.xy * 0.1 + vec2(iTime * 0.003, iTime * 0.01), 0.0).r * h;
        offset -= textureLod(iChannel2, pos.xy * 0.2 - vec2(iTime * 0.0043, iTime * 0.016), 0.0).r * h;
        return b + offset;
    }
    return b;
}

vec2 ObjWaterUV(vec3 pos)
{
    return pos.xy;
}

#define SCENE(type, name, init, pack) \
type name(vec3 pos, float bias) \
{ \
    type d = init; \
    \
    vec4 pos0 = ObjTestTransform(pos); \
    d = nmin(d, pack(ObjTest(pos0.xyz) * pos0.w, ObjTestUV(pos0.xyz), 1.0)); \
    d = nmin(d, pack(ObjTestP0(pos0.xyz) * pos0.w, ObjTestUV(pos0.xyz), 4.0)); \
    d = nmin(d, pack(ObjTestP1(pos0.xyz) * pos0.w, ObjTestUV(pos0.xyz), 6.0)); \
    d = nmin(d, pack(ObjTestP2(pos0.xyz) * pos0.w, ObjTestUV(pos0.xyz), 7.0)); \
    d = nmin(d, pack(ObjTestP3(pos0.xyz) * pos0.w, ObjTestUV(pos0.xyz), 5.0)); \
    \
    vec4 pos1 = ObjGroundT(pos); \
    d = nmin(d, pack(ObjHills(pos1.xyz, bias) * pos1.w, ObjGroundUV(pos1.xyz), 2.0)); \
    \
    vec4 pos2 = ObjWaterT(pos); \
    d = nmin(d, pack(ObjWater(pos2.xyz, bias) * pos2.w, ObjWaterUV(pos2.xyz), 3.0)); \
    \
    return d * min(iTime + 1.0, 1.0); \
}

/*


*/

// ------------------------------------------------------

SCENE(float, getDist, FAR, packDepth)
SCENE(vec4, getSurface, vec4(vec2(0.0), FAR, 0.0), packSurface)

vec2 march(vec3 org, vec3 dir, float simplify)
{
    float d = 0.0;
    vec3 p = org;
    float t = 0.0;
    for (; t < MAXT * simplify; t += 1.0)
    {
        float nd = getDist(p, E * d);
        d += nd;
        p += nd * dir;
        if (abs(nd) <= E * d)
        {
        
#ifdef MARCH_TEST
            return vec2(t / MAXT * simplify, 0.0);
#endif
            return vec2(d, E * d);
        }
        if (d >= FAR)
        {
            break;
        }
    }

#ifdef MARCH_TEST
    return vec2(t / MAXT * simplify, 0.0);
#endif
    
    return vec2(FAR, FAR * E);
}

vec3 getNormal(vec3 pos, float bias)
{
    vec2 offset = vec2(1.0, -1.0);
    float d = getDist(pos, bias);
    return normalize(
        offset.xyy * getDist(pos + offset.xyy * E, bias) + 
        offset.yyx * getDist(pos + offset.yyx * E, bias) + 
        offset.yxy * getDist(pos + offset.yxy * E, bias) +
        offset.xxx * getDist(pos + offset.xxx * E, bias)
    );
}

float shadow(vec3 org, 
             vec3 dir, 
             float start, 
             float width, 
             float simplify, 
             float seed)
{
    float d = start + start * seed;
    vec3 p = org + dir * start * seed;
    float mind = FAR;
    float pd = 0.0001;
    for (float t = 0.0; t < SMAXT * simplify; t += 1.0)
    {
        float nd = getDist(p, SE * d);
        float gd = sqrt(pd * pd - nd * nd / 4.0) * nd / pd;
        float k = nd * nd / 2.0 / pd;
        mind = min((gd + nd * 0.4) / max(0.0, d - k + d * 0.4) * width, mind);
        if (abs(nd) <= SE * d)
        {
            return clamp(0.0, 0.0, 1.0);
        }
        if (d >= FAR)
        {
            break;
        }
        d += nd;
        p += nd * dir;
        pd = nd;
    }
    return clamp(mind - SE * width, 0.0, 1.0);
}

float ambientOcclusion(vec3 org, 
                       vec3 dir, 
                       float dis, 
                       float start, 
                       float seed)
{
    float d = start + start * seed * 2.0;
    vec3 p = org + start * seed * dir * 2.0;
    float ao = 0.0;
    float base = 0.0;
    for (float t = 0.0; t < AOMAXT; t += 1.0)
    {
        float nd = getDist(p, SE * d);
        ao += max(0.0, nd) / max(0.001, d);
        base += 1.0;
        if (d >= dis)
        {
            break;
        }
        d += nd;
        p += nd * dir;
    }
    return clamp(ao / base, 0.0, 1.0);
}

vec3 rfnNormal(vec3 normal, float rfn, vec3 pos, float seed)
{
    vec3 U = normalize(abs(normal.z) == 1.0 ? vec3(1.0, 0.0, 0.0) : vec3(0.0, 0.0, 1.0));
    vec3 V = cross(U, normal);
    float a = seed * PI * 2.0;
    float r = fract(a * 647.831371);
    return normalize(normal / (0.0001 + pow(rfn, 1.7)) * 0.31 + U * cos(a) * r + V * sin(a) * r);
}

vec3 calEnv(vec3 normal, float rfn, vec3 pos, float seed)
{
    vec3 rnormal = rfnNormal(normal, rfn * 0.4, pos, seed);
    vec3 clear = textureLod(iChannel0, normal2UV(rnormal), 0.0).xyz;
    vec3 blur = blurSky(normal);
    return mix(clear, blur, rfn * 0.75);
}


Material ms[] = Material[](
    Material(vec4(0.0), 0.0, vec4(0.0)),
    Material(vec4(0.4, 0.42, 0.47, 0.8), 0.0, vec4(0.0)),
    Material(vec4(0.4, 0.41, 0.36, 0.05), 0.98, vec4(0.0)),
    Material(vec4(0.6, 0.63, 0.57, 0.88), 0.0, vec4(0.0)),
    Material(vec4(0.74, 0.74, 0.73, 0.05), 0.0, vec4(0.0)),
    Material(vec4(0.34, 0.34, 0.33, 0.05), 0.0, vec4(0.9, 0.4, 0.1, 1.2)),
    Material(vec4(0.78, 0.71, 0.43, 0.95), 0.02, vec4(0.0)),
    Material(vec4(0.84, 0.84, 0.84, 0.95), 0.01, vec4(0.0))
);

vec3 light(vec3 normal, 
           vec3 vdir, 
           float id, 
           vec2 uv, 
           float sd, 
           float ao, 
           vec3 wpos, 
           float seed)
{
    
    int bid = int(id);
    float fac = fract(id);
    vec4 albedo = mix(ms[bid].albedo, ms[bid + 1].albedo, fac);
    float rfn = mix(ms[bid].roughness, ms[bid + 1].roughness, fac);
    vec4 emission = mix(ms[bid].emission, ms[bid + 1].emission, fac);
    
    float nl = max(0.0, dot(normal, -SUN));
    vec3 rfdir = reflect(vdir, normal);
    float rfnl = max(0.0, dot(rfdir, -SUN));
    float sp = max(0.0, dot(rfdir, -SUN));
    float fnl = pow(1.0 - max(0.0, dot(vdir, -normal)), 5.0) * 0.5;
    fnl = fnl + 0.07;
    fnl = mix(fnl, 0.95, albedo.w);
    
    vec3 rfCol = calEnv(rfdir, rfn, wpos, seed);
    
    rfdir = rfnNormal(rfdir, rfn, wpos, seed);

#ifdef REAL_REFLECT
    vec2 p = march(wpos, rfdir, 0.5);
    vec3 rhpos = wpos + rfdir * p.x;
    
    if (p.x < FAR)
    {
        vec4 data = getSurface(rhpos, p.y);
        vec3 rfnormal = getNormal(rhpos, p.y);
        
        float rfsd = shadow(rhpos - SUN * E, -SUN, E, 1.0 / SUNSIZE, 0.25, seed);
        
        int rfbid = int(data.w);
        float rffac = fract(data.w);
        vec4 rfalbedo = mix(ms[rfbid].albedo, ms[rfbid + 1].albedo, rffac);
        float rfrfn = mix(ms[rfbid].roughness, ms[rfbid + 1].roughness, rffac);
        vec4 rfemission = mix(ms[rfbid].emission, ms[rfbid + 1].emission, rffac);
        vec3 rfabd = mix(vec3(1.0) , rfalbedo.xyz * 2.0, rfalbedo.w);
        
        rfCol = rfalbedo.xyz * (calEnv(rfnormal, 1.0, wpos, seed) + rfabd * SUNCOL * rfsd * max(0.0, dot(rfnormal, -SUN)));
        rfCol = mix(rfCol, FOG, clamp(pow(p.x * FOGSCALE, FOGEX), 0.0, 1.0));
        rfCol += ms[rfbid].emission.xyz * ms[rfbid].emission.w;
    }
#endif
    
    vec3 f = vec3(0.0);
    f += albedo.xyz * nl * sd * SUNCOL * (1.0 - albedo.w);
    
    f += albedo.xyz * calEnv(normal, 1.0, wpos, seed) * ao * (1.0 - fnl);
    
    vec3 rfalbedo = mix(vec3(1.0), albedo.xyz, albedo.w);
    
    f += ao * fnl * rfCol * rfalbedo;
    
    f += rfalbedo * fnl * sd * pow(rfnl, 64.0 / SUNSIZE * (1.024 - rfn)) * 33.0 * (1.111 - rfn) / SUNSIZE;
    
    f += ms[bid].emission.xyz * ms[bid].emission.w;
    
    return f;
}

// -------------------------------------------------------

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    if (fragCoord.x > (iResolution.x + BLOCKF - 1.0) / BLOCKF || 
        fragCoord.y > (iResolution.y + BLOCKF - 1.0) / BLOCKF)
    {
        return;
    }
    
    vec2 fragPos = floor(fragCoord) * BLOCKF;
    fragPos += vec2((iFrame % (BLOCK * BLOCK)) / BLOCK, iFrame % BLOCK);
    
    vec3 vdir = normalize(vec3((fragPos * 2.0 - iResolution.xy) / iResolution.x, 1.0).xzy);
    vdir = camera(vdir, vec3(0.0, 0.0, -750.0 * 0.01 + iMouse * 0.01));
    
    vec3 pos = vec3(0.0, -3.0, 0.0);
    
    vec2 p = march(pos, vdir, 1.0);
    
#ifdef MARCH_TEST
    fragColor = mix(vec4(0.5, 0.8, 0.9, 1.0), vec4(1.0, 0.6, 0.1, 1.0), p.x);
    return;
#endif
    
    vec3 spos = p.x * vdir + pos;
    
    vec3 normal = getNormal(spos, p.y);
    
    vec2 seed = normal2UV(normal + fract(spos * 882.134) / 0.3381);
    float s = hash2(seed);
    
    vec4 data = getSurface(spos, p.y);
    
    float sd = shadow(spos - E * SUN * 8.0, -SUN, E * 8.0, 1.0 / SUNSIZE, 1.0, s);
    sd = sd * 0.5 + shadow(spos - E * SUN * 8.0, -SUN, E * 8.0, 1.0 / SUNSIZE, 0.3, s);
    
    float ao = ambientOcclusion(spos + normal * E * 2.0, normal, 1.0, E * 2.0, s);
    
    vec3 face = light(normal, vdir, data.w, data.xy, sd, ao, spos, s);
    
    vec3 sky = calEnv(vdir, 0.0, spos, 0.0);
    
    face = mix(face, FOG, clamp(pow(p.x * FOGSCALE, FOGEX), 0.0, 1.0));

    // Output to screen
    fragColor = p.x < FAR ? vec4(face, 1.0) : vec4(sky, 1.0);
}

#include "../../shaders/waveWater/execute.frag.glsl"
#include "../../shaderLib/templateEnd.frag.glsl"