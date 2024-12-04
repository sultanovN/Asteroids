#pragma once
#include "Utility.h"

class Enemy
{
private:
    Vector2D Location;
    Vector2D Size;
    uint32_t Color;

public:

    Enemy(Vector2D Location = { 500.0f, 600.0f }, Vector2D Size = { 100.f, 80.f },
        uint32_t Color = MakeColor(125, 0, 125))
        : Location(Location), Size(Size), Color(Color)
    {
    }

    Vector2D GetLocation() { return Location; }

    Vector2D GetSize() { return Size; }

    void SetLocation(float X = 200.0f, float Y = 200.0f) { Location = { X, Y }; }

    void SetColor(uint32_t LColor) { Color = LColor; }

    uint32_t GetColor() { return Color; }
};