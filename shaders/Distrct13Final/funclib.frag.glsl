
precision highp float;

#define PI atan(0.0, -1.0)

struct Material
{
    vec4 albedo;
    float roughness;
    vec4 emission;
};

float packDepth(float dist, vec2 uv, float ID)
{
    return dist;
}

vec4 packSurface(float dist, vec2 uv, float ID)
{
    return vec4(uv, dist, ID);
}

float smin(float a, float b, float k)
{
    float p = pow(clamp(abs(a - b) * k, 0.0, 1.0) - 1.0, 2.0) * 0.25 / k;
    return min(a, b) - p;
}

vec4 smin(vec4 a, vec4 b, float k)
{
    float p = pow(clamp(abs(a.z - b.z), 0.0, 1.0) - 1.0, 2.0);
    vec4 res = mix(b, a, p * 0.5 * sign(a.z - b.z) - (sign(a.z - b.z) * 0.5 - 0.5));
    res.z = smin(a.z, b.z, k);
    return res;
}

float nmin(float a, float b)
{
    return min(a, b);
}

vec4 nmin(vec4 a, vec4 b)
{
    return a.z < b.z ? a : b;
}

float SDFSphere(vec3 pos)
{
    return length(pos) - 1.0;
}

float SDFCube(vec3 pos, vec4 hsize)
{
    pos = abs(pos) - hsize.xyz;
    return (length(max(vec3(0.0), pos)) + min(0.0, max(max(pos.x, pos.y), pos.z))) - hsize.w;
}

float SDFGround(vec3 pos)
{
    return abs(pos.z);
}

vec3 transform(vec3 pos, vec3 offset, vec3 rotation, float scale)
{
    float cx = cos(rotation.x);
    float sx = sin(rotation.x);
    float cy = cos(rotation.y);
    float sy = sin(rotation.y);
    float cz = cos(rotation.z);
    float sz = sin(rotation.z);
    mat3 r = mat3(cy, 0.0, -sy, 0.0, 1.0, 0.0, sy, 0.0, cy) *
        mat3(1.0, 0.0, 0.0, 0.0, cx, sx, 0.0, -sx, cx) *
        mat3(cz, sz, 0.0, -sz, cz, 0.0, 0.0, 0.0, 1.0);
    
    return r * (pos + offset) / scale;
}

vec3 camera(vec3 dir, vec3 rotation)
{
    float cx = cos(rotation.x);
    float sx = sin(rotation.x);
    float cy = cos(rotation.y);
    float sy = sin(rotation.y);
    float cz = cos(rotation.z);
    float sz = sin(rotation.z);
    mat3 r = mat3(cy, 0.0, -sy, 0.0, 1.0, 0.0, sy, 0.0, cy) *
        mat3(1.0, 0.0, 0.0, 0.0, cx, sx, 0.0, -sx, cx) *
        mat3(cz, sz, 0.0, -sz, cz, 0.0, 0.0, 0.0, 1.0);
    
    return dir * r;
}

vec3 UV2Normal(vec2 uv)
{
    float cy = cos(uv.y * PI - PI * 0.5);
    return vec3(cos(uv.x * PI * 2.0 + PI) * cy, sin(uv.x * PI * 2.0 + PI) * cy, sin(uv.y * PI - PI * 0.5));
}

vec2 normal2UV(vec3 normal)
{
    return vec2(atan(normal.y, normal.x) / PI / 2.0 + 0.5, atan(normal.z, length(normal.xy)) / PI + 0.5);
}

float hash2(vec2 d)
{
    return fract(731.38123 * sin(dot(d, vec2(16.231, 14.793))));
}

#define SKYCOL mix(vec3(0.3, 0.28, 0.25) * 1.8, vec3(0.5, 0.7, 0.9) * 1.8, cos(iTime * 0.1) * 0.5 + 0.5)
#define CLOUD0 normalize(vec3(0.3, 0.7, 2.0))
#define CLOUD1 normalize(vec3(-0.3, 0.2, 2.2))

#define C0COL vec3(0.9, 0.96, 0.94)
#define C1COL vec3(0.93, 0.98, 0.95)

#define SUN normalize(vec3(0.2, 0.10, -0.2))
#define SUNCOL mix(vec3(1.0, 0.96, 0.8) * 7.0, vec3(1.0, 0.96, 0.8) * 3.0, cos(iTime * 0.1) * 0.5 + 0.5)
#define SUNSIZE (1.0 / mix(0.1, 3.2, cos(iTime * 0.1) * 0.5 + 0.5))

#define E 0.0025
#define SE 0.055
#define FAR 200.0
#define MAXT 256.0
#define SMAXT 128.0
#define AOMAXT 8.0

#define FOG mix(vec3(0.3, 0.29, 0.275), vec3(0.5, 0.7, 0.9) * 1.3, cos(iTime * 0.1) * 0.5 + 0.5)
#define FOGSCALE 0.15
#define FOGEX 1.3

#define BLOCK 4
// >= 1, smaller to higher quality

#define BLOCKF float(BLOCK)

#define REAL_REFLECT
// #define MARCH_TEST





















