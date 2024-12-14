#pragma once

#include "Enemy.h"

class LaserEnemy : public Enemy
{
private:
    
    float PlayerXLocation;
    bool MovingDown = true;

public:
    LaserEnemy(Vector2D Location = { 500.0f, 500.0f }, int8_t Health = 4, uint32_t Color = MakeColor(255, 0, 0),
        Vector2D Size = { 40.f, 50.f }, uint32_t ProjColor = MakeColor(255, 0, 0), float Speed = 200.f, bool MovingRight = false, float PlayerXLocation = 100.f)
        : Enemy(Location, Health, Color, Size, ProjColor, Speed, MovingRight), PlayerXLocation(PlayerXLocation)
    {

    }


    void Move(const float dt, bool lines[], int linesNum, const int screenWidth = 1024) override
    {
        if (PlayerXLocation < GetLocation().X - 5.f)
            SetMovingRight(true);
        if(PlayerXLocation > GetLocation().X + 50.f)
            SetMovingRight(false);

        if (GetMovingRight())
        {
            SetXLocation(GetLocation().X + GetSpeed() * dt);
        }
        else
        {
            SetXLocation(GetLocation().X - GetSpeed() * dt);
        }

        LineMove(dt, lines, linesNum);
    }

};


