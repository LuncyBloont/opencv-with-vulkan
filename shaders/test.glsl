#version 420

layout(binding = 0, std140) uniform UniObject
{
    mat4 mats[8];
    vec4 vecs[17];
} _uni;

layout(binding = 2) uniform sampler2D _textures[3];
layout(binding = 1) uniform sampler2D _references[3];

layout(location = 1) in vec4 _uv;
layout(location = 0) out vec4 _outColor;
layout(location = 0) in vec4 _position;

float scene(vec2 pos)
{
    return texture(_textures[0], pos / _uni.vecs[11].xy).x / 0.00999999977648258209228515625;
}

void _frag(vec4 coord, inout vec4 fragColor)
{
    vec2 light = _uni.vecs[16].xy;
    vec2 pos = coord.zw;
    vec2 dir = normalize(pos - light);
    vec2 stop = light;
    float dis2l = distance(pos, light);
    float time = 0.0;
    float dis = 3.0;
    float hit = 0.0;
    for (int i = 0; i < 256; i++)
    {
        time += 1.0;
        stop = light + (dir * dis);
        vec2 param = stop;
        float d = scene(param);
        dis += d;
        hit = (dis >= dis2l) ? 0.0 : 1.0;
    }
    bvec3 _119 = bvec3(hit > 0.5);
    fragColor = vec4(vec3(_119.x ? vec3(0.0).x : vec3(1.0).x, _119.y ? vec3(0.0).y : vec3(1.0).y, _119.z ? vec3(0.0).z : vec3(1.0).z), 1.0);
}

void main()
{
    vec4 coord = vec4(_uv.xy, _uv.xy * _uni.vecs[15].xy);
    vec4 param = coord;
    vec4 param_1;
    _frag(param, param_1);
    _outColor = param_1;
}

