#version 420
#extension GL_GOOGLE_include_directive : require
#include "../waveWater/common.frag.glsl"

#define iChannel0 _tex0
#define iChannel1 _tex1
#define iChannel2 _tex2

/*
 * Copyright (c) 2022 LuncyTB. All rights reserved.
 */
 
precision highp float;

#define PI 3.14159
#define E 2.71828
#define TIMES 32.0
#define MAX_DIS 1e3
#define MIN_DIS 0.01
#define e vec2(-0.01, 0.01)

vec3 light = normalize(vec3(0.3, 0.4, -1.2));
vec3 lightCol = vec3(1.0, 0.97, 0.95) * 1.5;
vec3 env = vec3(0.7, 0.2, 0.1) * 1.1;
vec3 cloudCol = vec3(0.7, 0.7, 0.8);
float fog = 0.17;
float fogForce = 0.71;
#define _ iChannel2

struct F {
    vec3 normal;
    vec3 albedo;
    vec3 arm; // Alpha Roughness Metallic
    vec3 emission;
};

mat4 packLocal(vec3 pos, vec3 rot, vec3 scale) {
    float cx = cos(rot.x), cy = cos(rot.y), cz = cos(rot.z);
    float sx = sin(rot.x), sy = sin(rot.y), sz = sin(rot.z);
    return mat4(
            1.0 / scale.x, 0.0, 0.0, 0.0,
            0.0, 1.0 / scale.y, 0.0, 0.0, 
            0.0, 0.0, 1.0 / scale.z, 0.0,
            0.0 ,0.0, 0.0, 1.0
        ) * mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, cx, -sx, 0.0,
            0.0, sx, cx, 0.0,
            0.0, 0.0, 0.0, 1.0
        ) * mat4(
            cy, 0.0, sy, 0.0, 
            0.0, 1.0, 0.0, 0.0,
            -sy, 0.0, cy, 0.0,
            0.0, 0.0, 0.0, 1.0
        ) * mat4(
            cz, -sz, 0.0, 0.0, 
            sz, cz, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        ) * mat4(
            1.0, 0.0, 0.0, 0.0, 
            0.0, 1.0, 0.0, 0.0, 
            0.0, 0.0, 1.0, 0.0,
            -pos.x, -pos.y, -pos.z, 1.0
        );
}

float hash(in float s) {
    return fract(sin(s * 34.3201) * 349321.4893 + 0.34);
}

vec2 noise2(in vec2 uv) {
    vec2 k = vec2(fract(sin(uv.x * 5.341 + uv.y * 102.7558) * 41234.0123), 
        fract(cos(uv.y * -23.341 + uv.x * 74.0134) * 93481.43217));
    float r = k.x * PI * 2.0;
    float l = pow(k.y + 0.001, 0.5);
    return vec2(cos(r) * l, sin(r) * l);
}

float noise(in vec2 uv) {
    return fract(sin(dot(uv, vec2(56.7712, 23.0071)) + 0.12) * 82333.132);
}

float cloud1(in vec2 uv, in float size) {
    vec2 p00 = floor(uv / size);
    vec2 p01 = floor(uv / size + vec2(0.0, 1.0));
    vec2 p11 = floor(uv / size + vec2(1.0, 1.0));
    vec2 p10 = floor(uv / size + vec2(1.0, 0.0));
    uv = uv / size;
    vec2 v00 = normalize(noise2(p00));
    vec2 v01 = normalize(noise2(p01));
    vec2 v11 = normalize(noise2(p11));
    vec2 v10 = normalize(noise2(p10));
    return clamp(mix(
        mix(dot(v11, uv - p11), dot(v01, uv - p01), cos((uv.x - p00.x) * PI) * 0.5 + 0.5),
        mix(dot(v10, uv - p10), dot(v00, uv - p00), cos((uv.x - p01.x) * PI) * 0.5 + 0.5),
        cos((uv.y - p00.y) * PI) * 0.5 + 0.5
    ) * 0.5 + 0.5, 0.0, 1.0);
}

float cloud(in vec2 uv, in float size, in float times, in float sub) {
    float c = 0.0;
    float b = 0.0;
    float k = 1.0;
    for (float i = 0.0; i < times; i++) {
        k = pow(sub, i);
        c += cloud1(uv * sign(hash(i) - 0.5) + vec2(0.3, 1.3) * i, size * pow(0.5, i)) * k;
        b += k;
    }
    return c / b;
}

float sdfSphere(in vec3 pos, in float r) {
    float d = length(pos) - r;
    return d;
}

float replace(in vec3 pos, in float r, in float rp, in sampler2D tex, in float size) {
    float d = length(pos) - r;
    if (d < abs(rp) * 8.0 && rp != 0.0) {
        return rp * textureLod(tex, 
            size * vec2(atan(pos.y, pos.x), atan(pos.z, length(pos.xy))), 0.0).r;
    }
    return 0.0;
}

float sdfCone(in vec3 pos, in float h, in float r, in vec3 scl) {
    pos = pos / scl;
    if (pos.z < 0.0) {
        return sqrt(pow(pos.z, 2.0) + pow(min(r, length(pos.xy) - r), 2.0));
    } else {
        
    }
}

float smin(in float a, in float b, in float k) {
    float m = min(a, b);
    float d = abs(a - b);
    return m - pow(sqrt(1.0 / E), d * k) / k;
}

vec3 tFog(in vec3 col, in float d) {
    return mix(col, mix(cloudCol, env, fogForce), clamp(log(d) * fog, 0.0, 1.0));
}

vec3 gamma(in vec3 c, in float base) {
    return vec3(pow(c.r, 1.0 / base),
        pow(c.g, 1.0 / base), pow(c.b, 1.0 / base));
}

vec3 bg(in vec3 ray, in float sub) {
    vec3 c = vec3(0.0);
    float d = 0.0;
    if (ray.z < 0.0) {
        vec2 guv = ray.xy / ray.z;
        float k = mod(floor(fract(guv.x) * 2.0) + floor(fract(guv.y) * 2.0), 2.0);
        c = mix(vec3(0.7, 0.6, 0.2), vec3(0.2, 0.1, 0.1), k);
        c = c * env + c * lightCol * max(0.0, dot(-light, vec3(0.0, 0.0, 1.0)));
        d = length(vec3(guv, 1.0));
    } else if (ray.z >= 0.0) {
        c = env;
        d = MAX_DIS;
        vec2 guv = ray.xy / (ray.z + 0.01) * 3.1;
        d = length(vec3(guv, 3.1));
        float l1 = pow(cloud(guv + vec2(iTime, iTime * 0.7), 3.0, sub, 0.5), 3.3) * (1.6 + log(d * 0.1));
        float l2 = pow(cloud(guv - vec2(iTime * 0.6, -iTime * 1.3), 6.0, sub, 0.5), 3.3) * (1.6 + log(d * 0.1));
        c = mix(c, cloudCol, pow(l1 * l2, 0.6));
    }
    return tFog(c, d);
}

vec3 background(in vec3 ray, in float size) {
    float k = size / min(iResolution.x, iResolution.y);
    vec3 r000 = floor(ray * size);
    vec3 r001 = floor(ray * size + vec3(0.0, 0.0, 1.0));
    vec3 r010 = floor(ray * size + vec3(0.0, 1.0, 0.0));
    vec3 r011 = floor(ray * size + vec3(0.0, 1.0, 1.0));
    vec3 r100 = floor(ray * size + vec3(1.0, 0.0, 0.0));
    vec3 r101 = floor(ray * size + vec3(1.0, 0.0, 1.0));
    vec3 r110 = floor(ray * size + vec3(1.0, 1.0, 0.0));
    vec3 r111 = floor(ray * size + vec3(1.0, 1.0, 1.0));
    vec3 ins = 1.0 - fract(ray * size);
    
    return mix(
            mix(mix(bg(r000, size / 87.0), bg(r001, size / 87.0), 0.5 * cos(ins.z * PI) + 0.5), 
                mix(bg(r010, size / 87.0), bg(r011, size / 87.0), 0.5 * cos(ins.z * PI) + 0.5),
                0.5 * cos(ins.y * PI) + 0.5),
            mix(mix(bg(r100, size / 87.0), bg(r101, size / 87.0), 0.5 * cos(ins.z * PI) + 0.5), 
                mix(bg(r110, size / 87.0), bg(r111, size / 87.0), 0.5 * cos(ins.z * PI) + 0.5),
                0.5 * cos(ins.y * PI) + 0.5),
            0.5 * cos(ins.x * PI) + 0.5);
}

vec3 M(in vec3 p, in mat4 m) {
    return (m * vec4(p, 1.0)).xyz;
}

mat4 m0, m1;
float mouseAni;

float scene(in vec3 pos) {
    float d = MAX_DIS;
    
    vec3 p0 = M(pos, m0);
    if (length(p0) < 2.4) {
        d = smin(d, sdfSphere(p0, 0.6) - 
            replace(p0, 0.6, 0.1, iChannel0, 0.1) -
            replace(p0, 0.6, 0.01, iChannel0, 1.8), 22.0);
        d = smin(d, sdfSphere(p0 + vec3(0.0, 0.2, 0.6 + mouseAni * 0.7), 0.25) -
            replace(p0 + vec3(0.0, 0.2, 0.6 + mouseAni * 0.7), 0.25, 0.0, _, 0.0), 8.0);
        d = smin(d, sdfSphere(p0 + vec3(0.0, 0.4, 0.8 + mouseAni), 0.2) -
            replace(p0 + vec3(0.0, 0.4, 0.8 + mouseAni), 0.2, 0.0, _, 0.0), 22.0);
        d = smin(d, sdfSphere(p0 + vec3(0.0, 0.4, -0.6), 0.2) -
            replace(p0 + vec3(0.0, 0.4, -0.6), 0.2, 0.1, iChannel0, 0.55), 6.0);

        vec3 pp0 = vec3(-abs(p0.x), p0.yz);
        float d1 = smin(MAX_DIS, sdfSphere(pp0 + vec3(0.6, -0.2, 0.4 + mouseAni), 0.3) - 
            replace(pp0 + vec3(0.6, -0.2, 0.4 + mouseAni), 0.3, 0.1, iChannel0, 0.25), 6.0);
        d1 = smin(d1, sdfSphere(pp0 + vec3(0.8, -0.2, 0.7 + mouseAni), 0.2) - 
            replace(pp0 + vec3(0.8, -0.2, 0.7 + mouseAni), 0.2, 0.1, iChannel0, 0.25), 24.0);
        d1 = smin(d1, sdfSphere(pp0 + vec3(1.0, -0.1, 0.9 + mouseAni), 0.1) - 
            replace(pp0 + vec3(1.0, -0.1, 0.9 + mouseAni), 0.1, 0.1, iChannel0, 0.25), 24.0);
        d1 = -min(-d1, sdfSphere(pp0 + vec3(1.4, 0.0, 0.3 + mouseAni), 0.7) - 
            replace(pp0 + vec3(1.4, 0.0, 0.3 + mouseAni), 0.7, 0.1, iChannel0, 0.25));
        d1 = -min(-d1, sdfSphere(pp0 + vec3(1.0, 0.5, 0.6 + mouseAni), 0.7) - 
            replace(pp0 + vec3(1.0, 0.5, 0.6 + mouseAni), 0.7, 0.1, iChannel0, 0.25));

        d = smin(d, d1, 64.0);
        
        float md = min(MAX_DIS, sdfSphere(p0 + vec3(0.0, 0.6 + (0.05 - mouseAni * 0.5), -0.3 + mouseAni), 0.9) -
            replace(p0 + vec3(0.0, 0.6 + (0.05 - mouseAni * 0.5), -0.3 + mouseAni), 0.9, 0.2, iChannel0, 0.3));
        md = -min(-md, sdfSphere(p0 + vec3(0.0, 0.6, -0.7), 1.0) - 
            replace(p0 + vec3(0.0, 0.6, -0.7), 1.0, -0.2, iChannel0, 0.3));
        
        d = -min(-d, md);
        
        float xd = min(MAX_DIS, sdfSphere(pp0 + vec3(0.27, 0.7, -0.3), 0.4) - 
            replace(pp0 + vec3(0.27, 0.7, -0.3), 0.4, 0.05, iChannel0, 1.0));
        xd = -min(-xd, sdfSphere(pp0 + vec3(0.14, 0.7, -0.46), 0.48) - 
            replace(pp0 + vec3(0.14, 0.7, -0.46), 0.48, 0.05, iChannel0, 1.0));
        d = -min(xd, -d);
        
        xd = min(MAX_DIS, sdfSphere(pp0 + vec3(0.22, 0.7, -0.44), 0.42) - 
            replace(pp0 + vec3(0.22, 0.7, -0.44), 0.42, 0.05, iChannel0, 1.0));
        xd = -min(-xd, sdfSphere(pp0 + vec3(0.09, 0.7, -0.58), 0.5) - 
            replace(pp0 + vec3(0.09, 0.7, -0.58), 0.5, 0.05, iChannel0, 1.0));
        d = -min(xd, -d);
        
    } else {
        d = min(d, length(p0) - 1.2);  
    }
    
    vec3 twoBpos = M(vec3(abs(pos.x), pos.yz) + vec3(-1.7, 0.0, 0.0), m1);
    d = min(d, sdfSphere(twoBpos, 0.4 - abs(cos(iTime * 1.5)) * 0.2) - 
        replace(twoBpos, 0.4, 0.1, iChannel1, 0.2));
    
    return d;
}

void hitF(in vec3 pos, out F face) {
    face.albedo = vec3(0.5, 0.14, 0.1);
    face.normal = normalize(
        e.yyx * scene(pos + e.yyx) +
        e.yxy * scene(pos + e.yxy) +
        e.xyy * scene(pos + e.xyy) +
        e.xxx * scene(pos + e.xxx)
    );
    vec3 p0 = M(pos, m0);
    vec3 pp0 = vec3(-abs(p0.x), p0.yz);

    float headD = sdfSphere(p0 + vec3(0.0, 0.4, -0.6), 0.3);
    if (abs(headD) < MIN_DIS + 0.2) {
        float rd = replace(p0 + vec3(0.0, 0.4, -0.6), 0.2, 0.1, iChannel0, 0.55);
        face.albedo = mix(vec3(0.4, 0.24, 0.1), face.albedo, headD / (MIN_DIS + 0.2));
        face.arm.y = 0.5 * (1.0 - headD / (MIN_DIS + 0.2));
        face.emission = vec3(0.8, 0.21, 0.02) * 4.5 * pow(abs(rd) / 0.1, 3.0) * (1.0 - headD / (MIN_DIS + 0.2));
    }

    float mouseD = sdfSphere(p0 + vec3(0.0, 0.6 + (0.05 - mouseAni * 0.5), -0.3 + mouseAni), 0.9);
    if (abs(mouseD) < MIN_DIS + 0.2) {
        float brd = mouseD - replace(p0 + vec3(0.0, 0.6 + (0.05 - mouseAni * 0.5), -0.3 + mouseAni), 0.9, 0.2, iChannel0, 0.3);
        if (abs(brd) < MIN_DIS * 3.0) { 
            face.albedo = mix(face.albedo, vec3(0.08, 0.06, 0.03), clamp((1.0 - abs(mouseD) / 0.1) * (1.0 - p0.y * 4.0), 0.0, 1.0));
        }
    }

    float mouseD2 = sdfSphere(p0 + vec3(0.0, 0.6, -0.7), 1.0);
    if (abs(mouseD2) < MIN_DIS + 0.2) {
        float brd = mouseD2 - replace(p0 + vec3(0.0, 0.6, -0.7), 1.0, -0.2, iChannel0, 0.3);
        if (abs(brd) < MIN_DIS * 3.0) {
            face.albedo = mix(face.albedo, vec3(0.08, 0.06, 0.03), clamp((1.0 - abs(mouseD2) / 0.1) * (1.0 - p0.y * 4.0), 0.0, 1.0));
        }
    }

    float xD = sdfSphere(pp0 + vec3(0.15, 0.23, -0.1), 0.42);
    if (xD < 0.0 && mouseD2 < -MIN_DIS - 0.1) { 
        face.emission = vec3(1.1, 0.04, 0.01) * 6.0 * pow((-xD / 0.42), 0.7); 
    };

    float hdlD = sdfSphere(pp0 + vec3(1.0, -0.5, 0.8 + mouseAni), 0.9);
    if (hdlD < MIN_DIS) {
        face.albedo = mix(vec3(0.4, 0.24, 0.1), face.albedo, max(0.0, (hdlD + 0.2) / 0.2));
        face.emission = vec3(0.8, 0.21, 0.02) * 4.4 * pow(max(0.0, -0.1 - hdlD), 2.3);
    }
    
    vec3 twoBpos = M(vec3(abs(pos.x), pos.yz) + vec3(-1.7, 0.0, 0.0), m1);
    if (sdfSphere(twoBpos, 0.4 - abs(cos(iTime * 1.5)) * 0.2) - 
            replace(twoBpos, 0.4, 0.1, iChannel1, 0.2) < MIN_DIS) {
        face.albedo = vec3(0.6, 0.48, 0.33) * 1.3;
        face.arm = vec3(0.0, 0.55 + cos(iTime) * 0.45, 1.0);
        face.emission = vec3(0.0);
    }
}

float march(in vec3 org, in vec3 ray, in float times) {
    float d = 0.0;
    for (float i = 0.0; i < times; i++) {
        float s = scene(org + ray * d);
        if (s < MIN_DIS) { return d; }
        d += s;
    } 
    return MAX_DIS;
}

vec3 render(in F face, in vec3 ray, in float shadow, in vec3 old) {
    float fnl = mix(pow(1.0 - abs(dot(-ray, face.normal)), 6.0), 1.0, 0.03 + face.arm.z * 0.8);
    vec3 ref = reflect(ray, face.normal);
    float sscale = 0.07 + face.arm.y;
    float postK = pow(max(0.0, dot(-light, ref)), pow(1.0 / sscale, 2.0));
    return (1.0 - face.arm.z) * face.albedo * background(face.normal, 1.0)
        + (1.0 - face.arm.z * 0.9) * face.albedo * lightCol * max(0.0, dot(-light, face.normal)) * shadow
        + mix(vec3(1.0), face.albedo, face.arm.z) * background(ref, (1.0 - face.arm.y) * 6.0 + 1.0) * (0.8 + face.arm.z * 0.2) * fnl * mix(1.0 - face.arm.y, 1.0, face.arm.z)
        + lightCol * postK * (0.4 + face.arm.z * 0.6) * shadow * mix(pow(1.0 - face.arm.y, 2.0), pow(1.0 - face.arm.y * 0.6, 2.0), face.arm.z) 
        + face.emission;
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    vec2 pos2D = (fragCoord - iResolution.xy * 0.5) / min(iResolution.x, iResolution.y);
    vec3 ray = normalize(vec3(pos2D.x, 1.0, pos2D.y));
    vec3 pos = vec3(0.1, -4.0, 0.2);
    
    m0 = packLocal(vec3(cos(iTime * 0.67) * 0.8, 0.8, 0.0 - cos(iTime * 19.0) * 0.05), 
        vec3(0.1 + cos(iTime * 2.5) * 0.23, 0.0, iMouse.x * 0.03 + cos(iTime * 0.7) + sin(iTime * 0.1) * 10.0), 
        vec3(1.0, 1.0, 1.0));
    mouseAni = cos(iTime * 19.0 + cos(iTime * 23.0) * 0.2) * 0.05;
    m1 = packLocal(vec3(0.0), 
        vec3(0.1 + cos(iTime * 2.5) * 0.23, 0.0, iMouse.x * 0.03 + cos(iTime * 0.7) + sin(iTime * 0.1) * 10.0), 
        vec3(1.0, 1.0, 1.0));
    
    vec3 col = background(ray, 128.0);
    
    float d = march(pos, ray, TIMES);
    if (d < MAX_DIS) {
        F face; face.albedo = vec3(0.0); face.arm = vec3(1.0, 0.02, 0.0); face.emission = vec3(0.0);
        hitF(pos + ray * d, face);
        float sd = march(pos + ray * d - light * MIN_DIS * 12.0, -light, TIMES);
        if (sd < MAX_DIS) {
            col = render(face, ray, 0.0, col);
        } else {
            col = render(face, ray, 1.0, col);
        }
    }
    
    fragColor = vec4(gamma(col, 2.2), 1.0);
}

#include "../waveWater/execute.frag.glsl"