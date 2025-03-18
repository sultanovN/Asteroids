#pragma once
#include "Utility.h"

class Entity
{
protected:
    Vector2D Location;
    Vector2D Size;
    float Speed;
    uint32_t Color;

public:

    Entity(Vector2D Location, Vector2D Size, float Speed, uint32_t Color)
        : Location(Location), Size(Size), Speed(Speed), Color(Color)
    {
    }

    Vector2D GetLocation() const { return Location; }

    Vector2D GetSize() const { return Size; }

    uint32_t& GetColor() { return Color; }

    float GetSpeed()const { return Speed; }

    void SetLocation(const float X, const float Y) { Location = { X, Y }; }

    void SetColor(const uint32_t LColor) { Color = LColor; }
};