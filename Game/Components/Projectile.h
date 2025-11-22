#pragma once
#include "../Entity/Entity.h"
#include "../Engine/Engine.h"

class Projectile : public Entity
{
    float Speed;

    Surface Sprite = Surface("C:/Projects/Asteroids/Game/Images/laser-bolts_4x.bmp");
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

    virtual const void Draw() override;
};