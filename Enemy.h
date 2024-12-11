#pragma once
#include "Utility.h"

class Enemy
{
private:
    Vector2D Location;
    Vector2D Size;
    //bool alive;
    uint32_t Color;
    bool MovingRight = true;

public:

    Enemy(Vector2D Location = { 500.0f, 500.0f }, Vector2D Size = { 40.f, 50.f }, int8_t Health = 1,
        uint32_t Color = MakeColor(255, 0, 0))
        : Location(Location), Size(Size), Health(Health), Color(Color)
    {
    }


    ProjectileComponent ProjComponent{false, {10.f, 10.f}, MakeColor(255, 0, 0) };
    //HealthComponent HealthComp;
    int8_t Health;
    bool isAlive = true;

    Vector2D GetLocation() const { return Location; }

    Vector2D GetSize() const { return Size; }

    void SetLocation(const float X = 200.0f, const float Y = 200.0f) { Location = { X, Y }; }

    void SetColor(const uint32_t LColor) { Color = LColor; }

    uint32_t GetColor() const { return Color; }

    void Move(const float dt, const int screenWidth = 1024, const float speed = 200.0f)
    {
        if (Location.X < 50.0f)
            MovingRight = true;
        if (Location.X + Size.X > (screenWidth - 50.0f))
            MovingRight = false;
        if (MovingRight)
        {
            Location.X += speed * dt;
        }
        else
        {
            Location.X -= speed * dt;
        }
    }

    
};