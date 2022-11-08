#extension GL_GOOGLE_include_directive : require

#include "../../shaderLib/templateHead.frag.glsl"

#define DIS(v4) v4.z
#define UV(v4) v4.xy
#define ID(v4) v4.w

#define MAX_T 128
#define FAR 100.0
#define E 0.001

vec4 smin(vec4 a, vec4 b, float k)
{
    float f = pow(clamp(pow(k, 2.0) * abs(a.z - b.z), 0.0, 1.0) - 1.0, 2.0);
    float fac = (f * sign(a.z - b.z) - sign(a.z - b.z) + 1.0) * 0.5;

    return vec4(
        mix(a.xy, b.xy, fac),
        min(a.z, b.z) - f * 0.25 / pow(k, 2.0),
        mix(a.w, b.w, fac)
    );
}

vec4 smax(vec4 a, vec4 b, float k)
{
    vec4 f = smin(a * vec4(1.0, 1.0, -1.0, 1.0), b * vec4(1.0, 1.0, -1.0, 1.0), k);
    return vec4(f.xy, -f.z, f.w);
}

vec4 fmin(vec4 a, vec4 b)
{
    return a.z < b.z ? a: b;
}

vec4 fmax(vec4 a, vec4 b)
{
    return a.z >= b.z ? a : b;
}

float scaleF0(float x, float scale)
{
    float b = pow(1.0 / scale, 1.0 / (scale - 1.0));
    return -pow(b, scale) + pow(b + x, scale);
}

float scaleF1(float x, float scale)
{
    float limit = pow(1.0 / scale, 1.0 / (scale - 1.0));
    float y = x - pow(x, scale);
    return y;
}

float dance0(float t)
{
    return abs(cos(t)) + sin(t * 2.0 + 0.4) * 0.3 - cos(t * 4.0 + 1.5) * 0.1;
}

float sdfHeart(vec3 pos, float side)
{
    float dis0 = pos.y > 0.0 ? 
        distance(abs(pos.xy), vec2(0.5, 0.0)) - 0.5 :
        distance(vec2(abs(pos.x), scaleF1(abs(pos.y * _vecLib[0].z * 20.0), (_vecLib[0].y - 0.5) * 20.0)), vec2(-(_vecLib[0].x - 0.5) * 30.0, 0.0)) - 1.0 - (_vecLib[0].x - 0.5) * 30.0;
    float tail = -pow(-clamp(pos.y * 0.5, -100.0, 0.0), 2.0);
    float dis1 = dis0 < 0.0 ? abs(pos.z) - tail : length(vec2(dis0, abs(pos.z) - tail));

    return dis1 - side;
}

float sdfShpere(vec3 pos)
{
    return length(pos) - 1.0;
}

float sdfCone(vec3 pos, float h)
{
    float dis0 = length(pos.xz);
    float edgeDis = length(vec2(dis0 - 1.0, pos.y));
    float faceDis = (pos.y + h * dis0 - h) / length(vec2(h, 1.0));
    float bottomDis = -pos.y;
    return pos.y - 1.0 / h * dis0 > -1.0 / h || dis0 < 1.0 ? max(faceDis, bottomDis) : edgeDis;
}

float sdfCone2(vec3 pos, float h)
{
    float dis0 = length(pos.xz);
    float faceDis = (pos.y + h * dis0 - h) / length(vec2(h, 1.0));
    float edgeDis = length(vec2(dis0, pos.y + 1.0 / h)) - length(vec2(1.0, 1.0 / h));
    return pos.y - 1.0 / h * dis0 > -1.0 / h ? faceDis : max(faceDis, edgeDis);
}

vec3 transform(vec3 pos, vec3 offset, vec3 rotation, float scale)
{
    float cy = cos(rotation.y);
    float sy = sin(rotation.y);
    float cx = cos(rotation.x);
    float sx = sin(rotation.x);
    float cz = cos(rotation.z);
    float sz = sin(rotation.z);
    mat3 r = mat3(cy, 0.0, -sy, 0.0, 1.0, 0.0, sy, 0.0, cy) * 
        mat3(1.0, 0.0, 0.0, 0.0, cx, sx, 0.0, -sx, cx) *
        mat3(cz, sz, 0.0, -sz, cz, 0.0, 0.0, 0.0, 1.0);
    
    return r * (pos - offset) / scale;
}