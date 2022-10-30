#version 420
#extension GL_GOOGLE_include_directive : require
#include "../waveWater/common.frag.glsl"

#define iChannel0 _tex0
#define iChannel1 _tex1
#define iChannel2 _tex2

#define SHOW_FOR_OPENCV

/*
 * Copyright (c) 2022 LuncyTB. All rights reserved.
 */

#define PI 3.1415926535
#define PI2 (3.1415926535 * 2.0)

#define MAX_TIMES 64.0
#define MIN_DIS 0.01
#define MAX_DIS 1e9
#define e vec2(-0.01, 0.01)

struct Surface {
    vec3 normal;
    vec3 albedo;
    vec3 other;
};

mat4 packM(vec3 pos, vec3 rot, vec3 scl) {
    float cx = cos(rot.x), cy = cos(rot.y), cz = cos(rot.z);
    float sx = sin(rot.x), sy = sin(rot.y), sz = sin(rot.z);
    return mat4(
        cz*cy - sx*sz*sy, cy*sz + sx*cz*sy, -cx*sy, 0.0,
        -sz*cx, cx*cz, sx, 0.0,
        cz*sy + cy*sx*sz, sy*sz - cy*sx*cz, cx*cy, 0.0,
        0.0, 0.0, 0.0, 1.0
    ) * mat4(
        scl.x, 0.0, 0.0, 0.0,
        0.0, scl.y, 0.0, 0.0,
        0.0, 0.0, scl.z, 0.0,
        -pos.x, -pos.y, -pos.z, 1.0
    );
}

vec3 toLocal(in vec4 pos, in mat4 m) {
    return (m * pos).xyz;
}

float sdfSphere(in vec3 pos, in float r) {
    return length(pos) - r;
}

float scene(in vec3 pos) {
    float d = MAX_DIS;
    
    mat4 m0 = packM(
        vec3(cos(iTime) * 0.6, sin(iTime * 0.6), sin(iTime) * 0.4), 
        vec3(iTime, iTime * 1.5, iTime * 0.5), 
        vec3(1.0));
    d = min(d, sdfSphere(toLocal(vec4(pos, 1.0), m0), 0.5));
    
    return d;
}

vec3 getNormal(in vec3 pos) {
    return normalize(
        e.yxy * scene(pos + e.yxy) + 
        e.yyx * scene(pos + e.yyx) + 
        e.xyy * scene(pos + e.xyy) +
        e.xxx * scene(pos + e.xxx)
    );
}

void getFace(in vec3 pos, out Surface face) {

    mat4 m0 = packM(
        vec3(cos(iTime) * 0.6, sin(iTime * 0.6), sin(iTime) * 0.4), 
        vec3(iTime, iTime * 1.5, iTime * 0.5), 
        vec3(1.0));
    vec3 pp = toLocal(vec4(pos, 1.0), m0);
    if (sdfSphere(pp, 0.5) < MIN_DIS) {
        float lm = 0.3;
        face = Surface(getNormal(pos), vec3(0.9, 0.3, 0.4), vec3(0.0));
        float r = mod(atan(pp.y, pp.x), PI2);
        float r1 = mod(atan(pp.y, pp.x) - PI2 / 6.0, PI2);
        float k = (pp.z + lm) / lm / 2.0;
        float p = 1.0 - k;
        if (abs(r - PI2 * 1.0 / 6.0) < PI / 3.0 * k) face.albedo = vec3(0.9, 0.1, 0.1);
        if (abs(r - PI2 * 3.0 / 6.0) < PI / 3.0 * k) face.albedo = vec3(0.1, 0.9, 0.1);
        if (abs(r - PI2 * 5.0 / 6.0) < PI / 3.0 * k) face.albedo = vec3(0.1, 0.1, 0.9);
        if (abs(r1 - PI2 * 1.0 / 6.0) < PI / 3.0 * p) face.albedo = vec3(0.9, 0.9, 0.1);
        if (abs(r1 - PI2 * 3.0 / 6.0) < PI / 3.0 * p) face.albedo = vec3(0.1, 0.9, 0.9);
        if (abs(r1 - PI2 * 5.0 / 6.0) < PI / 3.0 * p) face.albedo = vec3(0.9, 0.1, 0.9);
        if (pp.z > lm) face.albedo = vec3(0.1);
        if (pp.z < -lm) face.albedo = vec3(0.9);
    } else {
        face = Surface(vec3(0.0), vec3(0.0), vec3(0.0));
    }
}

float march(in vec3 ray, in vec3 str) {
    float d = MAX_DIS;
    float pass = 0.0;
    
    for (float i = 0.0; i < MAX_TIMES; i++) {
        d = min(d, scene(str + ray * pass));
        pass += d;
        if (d < MIN_DIS) { return pass; }
    }

    return MAX_DIS;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    float dis0 =  min(iResolution.x, iResolution.y) * 0.2;
    float dis1 =  dis0 * 1.3;
    vec2 Ctr = iResolution.xy / 2.0;
    vec2 B = Ctr + vec2(cos(PI * 0.5) * dis0, sin(PI * 0.5) * dis0);
    vec2 Y = Ctr + vec2(cos(PI * 0.5 - PI2 / 3.0) * dis0, sin(PI * 0.5 - PI2 / 3.0) * dis0);
    vec2 R = Ctr + vec2(cos(PI * 0.5 + PI2 / 3.0) * dis0, sin(PI * 0.5 + PI2 / 3.0) * dis0);
    
    vec3 c = vec3(1.0);
    
    vec3 dY = vec3(0.0, 0.0, 1.0);
    vec3 dB = vec3(1.0, 0.0, 0.0);
    vec3 dR = vec3(0.0, 1.0, 0.0);
    
    if (distance(fragCoord, R) < dis1) {
        c -= dR;
    }
    
    if (distance(fragCoord, Y) < dis1) {
        c -= dY;
    }
    
    if (distance(fragCoord, B) < dis1) {
        c -= dB;
    }

    // Output to screen
    fragColor = vec4(mix(c, 1.0 - c, cos(iTime) * 0.5 + 0.5), 1.0);
    
    vec3 light0 = normalize(vec3(-0.5, 0.5, -1.0));
    vec3 light0Col = vec3(1.0, 0.97, 0.9) * 1.5;
    vec3 env = vec3(0.2, 0.5, 0.6) * 0.4;
    
    vec2 vuv = (fragCoord - iResolution.xy * 0.5) / min(iResolution.x, iResolution.y);
    vec3 ray = normalize(vec3(vuv.x, 1.0, vuv.y));
    vec3 pos = vec3(0.5, -2.0, 0.1);
    
    float d = march(ray, pos);
    if (d < MAX_DIS) {
        Surface face;
        getFace(pos + ray * d, face);
        
        vec3 col = light0Col * face.albedo * max(0.0, dot(face.normal, -light0))
            + env * face.albedo
            ;
        
        float correction = 2.2;
        fragColor = vec4(vec3(
            pow(col.r, 1.0 / correction), 
            pow(col.g, 1.0 / correction), 
            pow(col.b, 1.0 / correction)
        ), 1.0);
    }
    
}

#include "../waveWater/execute.frag.glsl"