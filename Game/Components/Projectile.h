#pragma once
#include "../Entity/Entity.h"
#include "../Engine/Engine.h"

class Projectile : public Entity
{
    float Speed;

    Surface Sprite = Surface("Sprites/laser-bolts_4x.bmp");
    Vector2D SpriteRegionLocation;
public:
    Projectile(Vector2D Location, Vector2D Size, float Speed, uint32_t Color, Surface Sprite, Vector2D SpriteRegionLocation)
        : Entity(Location, Size, Color), Speed(Speed), Sprite(Sprite), SpriteRegionLocation(SpriteRegionLocation)
    {
    }
    float GetSpeed()const { return Speed; };

    Projectile(Vector2D Location, Vector2D Size, float Speed, Color Color, Surface Sprite, Vector2D SpriteRegionLocation)
        : Entity(Location, Size, Color), Speed(Speed), Sprite(Sprite), SpriteRegionLocation(SpriteRegionLocation)
    {
    }

    virtual void Update(const float dt) override;

    virtual const void Draw() override;
};