#pragma once
#include "Utility.h"
#include <iostream>

class Enemy
{
private:
    Vector2D Location;
    Vector2D Size;
    //bool alive;
    uint32_t Color;
    uint32_t ProjColor;
    bool MovingRight = true;
    bool MovingDown = true;

public:

    Enemy(Vector2D Location = { 500.0f, 500.0f }, int8_t Health = 1,
        uint32_t Color = MakeColor(255, 0, 0), Vector2D Size = { 40.f, 50.f }, uint32_t ProjColor = MakeColor(255, 0, 0))
        : Location(Location), Size(Size), Health(Health), Color(Color), ProjColor(ProjColor)
    {
    }


    ProjectileComponent ProjComponent{false, {10.f, 10.f}, ProjColor };
    //HealthComponent HealthComp;
    int8_t Health;
    bool isAlive = true;

    Vector2D GetLocation() const { return Location; }

    Vector2D GetSize() const { return Size; }

    void SetLocation(const float X = 200.0f, const float Y = 200.0f) { Location = { X, Y }; }

    void SetColor(const uint32_t LColor) { Color = LColor; }

    uint32_t GetColor() const { return Color; }

    void Move(const float dt, bool lines[], int linesNum,const int screenWidth = 1024, const float speed = 200.0f)
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

        //only first line usable
        if (MovingDown)
        {
            for (int j = 0; j < linesNum; j++)
            {
                if ((Location.Y < (100.0f * (j + 1))) && lines[j])
                {
                    Location.Y += speed * dt;

                    //lines[j] = false;
                }
                else if (Location.Y >= (100.0f * (j + 1)) && lines[j])
                {
                    MovingDown = false;
                    lines[j] = false;
                    break;

                }
            }
        }
        
        /*if (MovingDown)
        {
            Location.Y += speed * dt;

        }*/
    }

    
};