#pragma once
#include <stdint.h>

uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b)
{
    return r << 16 | g << 8 | b;
}

struct Vector2D
{
    float X, Y;
};

bool RectRectCollision(float r1x, float r1y, float r1w, float r1h,
    float r2x, float r2y, float r2w, float r2h)
{
    if (r1x + r1w >= r2x &&
        r1x <= r2x + r2w &&
        r1y + r1h >= r2y &&
        r1y < r2y + r2h)
        return true;
    return false;
}

struct Projectile
{
    Vector2D Location;
    Vector2D Size;
    uint32_t Color;
    

};