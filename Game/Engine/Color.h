#pragma once
#include <stdint.h>


class Color
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
public:
    Color(uint8_t Red, uint8_t Green, uint8_t Blue)
        : Red(Red), Green(Green), Blue(Blue)
    {
    }

    Color(uint32_t color)
        :Red((color >> 16) & 0xff), Green((color >> 8) & 0xff), Blue((color) & 0xff)
    {
    }

    const uint8_t GetR() const { return Red; }
    const uint8_t GetG() const { return Green; }
    const uint8_t GetB() const { return Blue; }
};

namespace Colors
{
    static constexpr uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b)
    {
        return r << 16 | g << 8 | b;
    }
    
    static uint32_t MakeColor(Color color)
    {
        return color.GetR() << 16 | color.GetG() << 8 | color.GetB();
    }

    static constexpr uint32_t Red =       MakeColor(255u, 0u, 0u);
    static constexpr uint32_t Green =     MakeColor(0u, 255u, 0u);
    static constexpr uint32_t Blue =      0x0000FF;//255
    static constexpr uint32_t Orange =    MakeColor(255u, 128u, 0u);
    static constexpr uint32_t Yellow =    MakeColor(255u, 255u, 0u);
    static constexpr uint32_t LightBlue = 0x00FFFF;
    static constexpr uint32_t White =     0xFFFFFF;
    static constexpr uint32_t Black =     0x000000;

};

