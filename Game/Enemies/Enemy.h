#pragma once

class Entity;
class ProjectileComponent;

class Enemy: public Entity
{
private:
    //uint32_t ProjColor;
    bool MovingRight = true;
    bool MovingDown = true;

public:
    Enemy(Vector2D Location, Vector2D Size, float Speed, int8_t Health, uint32_t Color, bool MovingRight);



    ProjectileComponent ProjComponent;
    //HealthComponent HealthComp;
    int8_t Health;
    bool isAlive = true;

    bool GetMovingRight()const { return MovingRight; }

    void SetMovingRight(bool Moving) { MovingRight = Moving; }


    void LineMove(const float dt, bool lines[], int linesNum);

    virtual void Move(const float dt, bool lines[], int linesNum, const int screenWidth, float playerX);
    
};
