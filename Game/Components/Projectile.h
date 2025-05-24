#pragma once
#include "../Entity/Entity.h"

class Projectile : public Entity
{
    float Speed;
public:
    Projectile(Vector2D Location, Vector2D Size, float Speed, uint32_t Color)
        : Entity(Location, Size, Color), Speed(Speed)
    {
    }
    float GetSpeed()const { return Speed; };

    Projectile(Vector2D Location, Vector2D Size, float Speed, Color Color)
        : Entity(Location, Size, Color), Speed(Speed)
    {
    }

    virtual void Update(const float dt) override;
};