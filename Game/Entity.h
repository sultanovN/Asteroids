#pragma once
#include "Components/Vector2D.h"
#include "stdint.h"
#include "Components/Color.h"

class Entity
{
protected:
    Vector2D Location;
    Vector2D Size;
    float Speed;
    uint32_t Color;

public:

    Entity(Vector2D Location, Vector2D Size, float Speed = 0.f, uint32_t Color = 0)
        : Location(Location), Size(Size), Speed(Speed), Color(Color)
    {
    }

    Vector2D GetLocation() const { return Location; }

    Vector2D GetSize() const { return Size; }

    uint32_t& GetColor() { return Color; }

    float GetSpeed()const { return Speed; }

    void SetLocation(const float X, const float Y) { Location = { X, Y }; }

    void SetColor(const uint32_t LColor) { Color = LColor; }

    bool Collision(const Entity obj)
    {
        return RectRectCollision(this->Location, this->Size,
            obj.GetLocation(), obj.GetSize());
    }

    const void Draw(const int screen_width, const int screen_height, uint32_t** buffer)
    {
        for (int x = 0; x < screen_width; x++)
            for (int y = 0; y < screen_height; y++)
            {
                if ((x >= Location.X && (x <= Location.X + Size.X)) && (y >= Location.Y && (y <= Location.Y + Size.Y)))
                {
                    //if this does not work return Color, uint32_t and assign it in game to buffer
                    buffer[y][x] = Color;
                }
            }
    }
};


