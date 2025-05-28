#pragma once
#include <stdint.h>


class Color
{
public:
    uint32_t fullColor;

    constexpr Color() : fullColor() {}

    constexpr Color(uint8_t r, uint8_t g, uint8_t b)
        : fullColor(r << 16u | g << 8u | b)
    {
    }

    constexpr Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
        : fullColor(a << 24u | r << 16u | g << 8u | b)
    {
    }

    constexpr Color(const Color& col) : fullColor(col.fullColor){}

    Color& operator=(Color rhs)
    {
        fullColor = rhs.fullColor;
        return *this;
    }

    Color(uint32_t color)
        :fullColor(color)
    {
    }

    //uint8_t Red;
    //uint8_t Green;
    //uint8_t Blue;

    //Color(uint8_t Red = 255u, uint8_t Green = 0u, uint8_t Blue = 255u)
    //    : Red(Red), Green(Green), Blue(Blue)
    //{
    //}



    

    const uint8_t GetR() const { return (fullColor >> 16u)  & 0xffu; }
    const uint8_t GetG() const { return (fullColor >> 8u) & 0xffu;}
    const uint8_t GetB() const { return (fullColor) & 0xffu;}
};

namespace Colors
{
    static constexpr uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b)
    {
        return r << 16u | g << 8u | b;
    }
    
    static uint32_t MakeColor(Color color)
    {
        return color.GetR() << 16u | color.GetG() << 8u | color.GetB();
    }

    static constexpr uint32_t Red =       MakeColor(255u, 0u, 0u);
    static constexpr uint32_t Green =     MakeColor(0u, 255u, 0u);
    static constexpr uint32_t Blue =      0x0000FF;//255
    static constexpr uint32_t Orange =    MakeColor(255u, 128u, 0u);
    static constexpr uint32_t Yellow =    MakeColor(255u, 255u, 0u);
    static constexpr uint32_t LightBlue = 0x00FFFFu;
    static constexpr uint32_t White =     0xFFFFFFu;
    static constexpr uint32_t Black =     0x000000u;
    static constexpr uint32_t Brown =     MakeColor(88u, 57u, 39u);

};

