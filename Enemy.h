#pragma once
#include "Utility.h"
#include <iostream>

class Enemy
{
private:
    Vector2D Location;
    Vector2D Size;
    uint32_t Color;
    uint32_t ProjColor;
    float Speed;
    bool MovingRight = true;
    bool MovingDown = true;

public:

    Enemy(Vector2D Location = { 500.0f, 500.0f }, int8_t Health = 4,
        uint32_t Color = MakeColor(255, 0, 0), Vector2D Size = { 40.f, 50.f }, 
        uint32_t ProjColor = MakeColor(255, 0, 0), float Speed = 200.f, bool MovingRight = true)
        : Location(Location), Size(Size), Health(Health), Color(Color), ProjColor(ProjColor), Speed(Speed)
    {
    }


    ProjectileComponent ProjComponent{{10.f, 10.f}, ProjColor };
    //HealthComponent HealthComp;
    int8_t Health;
    bool isAlive = true;

    Vector2D GetLocation() const { return Location; }

    Vector2D GetSize() const { return Size; }

    void SetLocation(const float X = 200.0f, const float Y = 200.0f) { Location = { X, Y }; }
    void SetXLocation(const float X = 200.0f) { Location.X = X; }

    void SetColor(const uint32_t LColor) { Color = LColor; }

    uint32_t GetColor() const { return Color; }

    float GetSpeed()const { return Speed; }

    bool GetMovingRight()const { return MovingRight; }

    void SetMovingRight(bool Moving) { MovingRight = Moving; }

    void LineMove(const float dt, bool lines[], int linesNum)
    {
        if (MovingDown)
        {
            for (int j = 0; j < linesNum; j++)
            {
                if ((Location.Y < (100.0f * (j + 1))) && lines[j])
                {
                    Location.Y += Speed * dt;
                }
                else if (Location.Y >= (100.0f * (j + 1)) && lines[j])
                {
                    MovingDown = false;
                    lines[j] = false;
                    break;

                }
            }
        }
    }

    virtual void Move(const float dt, bool lines[], int linesNum, const int screenWidth = 1024)
    {
        if (Location.X < 50.0f)
            MovingRight = true;

        if (Location.X + Size.X > (screenWidth - 50.0f))
            MovingRight = false;

        if (MovingRight)
        {
            Location.X += Speed * dt;
        }
        else
        {
            Location.X -= Speed * dt;
        }

        LineMove(dt, lines, linesNum);
    }

    
};

//class Follower: public Enemy
//{
//private:
//    Vector2D Location;
//    Vector2D Size;
//    //bool alive;
//    uint32_t Color;
//    uint32_t ProjColor;
//    bool MovingRight = true;
//    bool MovingDown = true;
//
//public:
//
//    Follower(Vector2D Location = { 500.0f, 500.0f }, int8_t Health = 1,
//        uint32_t Color = MakeColor(255, 0, 0), Vector2D Size = { 40.f, 50.f }, uint32_t ProjColor = MakeColor(255, 0, 0))
//        : Location(Location), Size(Size), Health(Health), Color(Color), ProjColor(ProjColor)
//    {
//    }
//
//    ProjectileComponent ProjComponent{ false, {10.f, 10.f}, ProjColor };
//    //HealthComponent HealthComp;
//    int8_t Health;
//    bool isAlive = true;
//};

