#pragma once
#include "../Components/ProjectileComponent.h"

class Enemy: public Entity
{
private:
    bool MovingRight = true;
    bool MovingDown = true;

public:
    Enemy(Vector2D Location, Vector2D Size, float Speed, int8_t Health, uint32_t Color, bool MovingRight);

    ProjectileComponent ProjComponent{ {Location.X + Size.X / 2 - Size.X / 2, Location.Y - 2.f}, {10.f, 10.f}, Colors::Red, -400.f };
    //HealthComponent HealthComp;
    int8_t Health;
    bool isAlive = true;

    bool GetMovingRight()const { return MovingRight; }

    void SetMovingRight(bool Moving) { MovingRight = Moving; }

    void LineMove(const float dt, bool lines[], int linesNum);

    virtual void Move(const float dt, bool lines[], int linesNum, const int screenWidth, float playerX);
    
    virtual void Update(const float dt) override;
};
