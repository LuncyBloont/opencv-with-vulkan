precision highp float;

/*
 * Copyright (c) 2022 LuncyTB. All rights reserved.
 */

vec2 toScreenScale(vec2 a, vec2 size)
{
    return a / size.xy * size.x;
}

float sigmod(float a)
{
    return 1.0 - cos(clamp(a, 0.0, 3.141592654)) * 0.5;
}

vec2 boat(float time, vec2 res)
{
    return vec2(cos(time), sin(time)) * 
        cos(time * 0.5 + sin(time * 0.3)) * 200.0 + vec2(0.5) * res;
}