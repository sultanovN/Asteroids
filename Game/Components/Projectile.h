#pragma once
#include "../Entity/Entity.h"

class Projectile : public Entity
{
public:
    Projectile(Vector2D Location, Vector2D Size, float Speed, uint32_t Color)
        : Entity(Location, Size, Speed, Color)
    {
    }

    virtual void Update(const float dt) override;
};