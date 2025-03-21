#pragma once

#include "Enemy.h"

class LaserEnemy : public Enemy
{
private:
    
    float PlayerXLocation;
    bool MovingDown = true;

public:
    LaserEnemy(float PlayerXLocation, Vector2D Location = { 500.0f, 500.0f }, int8_t Health = 4, uint32_t Color = Colors::MakeColor(0, 0, 190),
        Vector2D Size = { 60.f, 40.f }, uint32_t ProjColor = Colors::MakeColor(0, 0, 200), float Speed = 200.f, bool MovingRight = false)
        : Enemy(Location, Size, Speed, Color, Health, MovingRight), PlayerXLocation(PlayerXLocation)
    {
        Size = { 100.f, 40.f };
    }


    void Move(const float dt, bool lines[], int linesNum, const int screenWidth, float playerX) override
    {
        if (PlayerXLocation < GetLocation().X - 5.f)
            SetMovingRight(true);
        if(PlayerXLocation > GetLocation().X + 50.f)
            SetMovingRight(false);

        if (GetMovingRight())
        {
            SetLocation(GetLocation().X - GetSpeed() * dt, GetLocation().Y);
        }
        else
        {
            SetLocation(GetLocation().X - GetSpeed() * dt, GetLocation().Y);
        }

        LineMove(dt, lines, linesNum);
    }

};


