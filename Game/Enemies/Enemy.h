#pragma once
#include "../Entity.h"

class Enemy: public Entity
{
private:
    uint32_t ProjColor;
    bool MovingRight = true;
    bool MovingDown = true;

public:

    Enemy(Vector2D Location, Vector2D Size = {40.f, 50.f}, float Speed = 300.f, uint32_t Color = Colors::Red,
        int8_t Health = 2, uint32_t ProjColor = Colors::Red, bool MovingRight = true)
        :Entity(Location, Size, Speed, Color), Health(Health), ProjColor(ProjColor), MovingRight(MovingRight)
    {
    }

    bool shot = false;

    ProjectileComponent ProjComponent{{10.f, 10.f}, ProjColor };
    //HealthComponent HealthComp;
    int8_t Health;
    bool isAlive = true;

    bool GetMovingRight()const { return MovingRight; }

    void SetMovingRight(bool Moving) { MovingRight = Moving; }

    void LineMove(const float dt, bool lines[], int linesNum);

    virtual void Move(const float dt, bool lines[], int linesNum, const int screenWidth, float playerX);
    
};
