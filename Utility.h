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