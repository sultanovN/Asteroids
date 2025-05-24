#pragma once
#include "../Components/ProjectileComponent.h"

class Enemy: public Entity
{
private:
    bool MovingRight = true;
    bool MovingDown = true;
    float Speed;

public:
    Enemy(Vector2D Location, Vector2D Size, float Speed, int8_t Health, uint32_t Color, bool MovingRight);

    //ProjectileComponent ProjComponent{ {Location.X + Size.X / 2 - Size.X / 2, Location.Y - Size.Y + 2.f}, {10.f, 25.f}, -400.f, Colors::Red};
    //HealthComponent HealthComp;
    int8_t Health;
    bool isAlive = true;
    float GetSpeed()const { return Speed; };

    bool GetMovingRight()const { return MovingRight; }

    void SetMovingRight(bool Moving) { MovingRight = Moving; }

    void LineMove(const float dt, int lines[], int linesNum);

    virtual void Move(const float dt, int lines[], int linesNum, const int screenWidth, float playerX);
    
};
