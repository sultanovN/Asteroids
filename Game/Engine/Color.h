#pragma once
#include <stdint.h>

namespace Colors
{
    static constexpr uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b)
    {
        return r << 16 | g << 8 | b;
    }

    static constexpr uint32_t Red =       MakeColor(255u, 0u, 0u);
    static constexpr uint32_t Green =     MakeColor(0u, 255u, 0u);
    static constexpr uint32_t Blue =      0x0000FF;//255
    static constexpr uint32_t Orange =    MakeColor(255u, 128u, 0u);
    static constexpr uint32_t Yellow =    MakeColor(255u, 255u, 0u);
    static constexpr uint32_t LightBlue = 0x00FFFF;
};

