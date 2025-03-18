#pragma once
#include <stdint.h>

namespace Colors
{
    const uint32_t Red = 255 << 16;
    const uint32_t Green = 255 << 8;
    const uint32_t Blue = 0x0000FF;//255
    const uint32_t Orange = 255 << 16 | 128 << 8;
    const uint32_t Yellow = 255 << 16 | 255 << 8;
    const uint32_t LightBlue = 0x00FFFF;
};

uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b)
{
    return r << 16 | g << 8 | b;
}