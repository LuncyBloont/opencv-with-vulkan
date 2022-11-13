#version 420

#extension GL_GOOGLE_include_directive : require

#include "../../shaderLib/templateHead.frag.glsl"

#include "../waveWater/common.frag.glsl"

#include "./funclib.frag.glsl"

#define iChannel0 _tex0

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord / iResolution.xy;
    vec3 normal = UV2Normal(uv);
    
    vec2 cloudUV = normal.xy / normal.z * 0.1;
    
    vec3 cloud0 = texture(iChannel0, cloudUV).r * C0COL * SKYCOL;
    vec3 cloud1 = texture(iChannel0, cloudUV * 0.7).r * C1COL * SKYCOL;
    
    vec3 sky = SKYCOL * mix(texture(iChannel0, cloudUV * 0.5).r, 1.0, 0.8);
    
    sky = mix(sky, cloud0, 0.7 * pow(max(0.0, dot(normal, CLOUD0)), 1.0));
    sky = mix(sky, cloud1, 0.6 * pow(max(0.0, dot(normal, CLOUD1)), 1.5));
    
    sky = mix(sky, SUNCOL, 0.1 * pow(max(0.0, dot(normal, -SUN)), 36.0 / SUNSIZE));
    
    if (normal.z > 0.0)
    {
        fragColor = vec4(sky, 1.0);
    }
    else
    {
        fragColor = vec4(SKYCOL * 0.8, 1.0);
    }
}

#include "../../shaders/waveWater/execute.frag.glsl"
#include "../../shaderLib/templateEnd.frag.glsl"