#pragma once
#include <stdint.h>
#include "../Entity/Entity.h"

enum class EBonusTypes
{
    Health,
    ProjectileFreq,
    ProjectileSpeed,
    TwoProjectileShoot
};
//temporary or constant till damage

//Bonus will appear with the death of enemy at his place and slowly fall down
class Bonus: public Entity
{
    EBonusTypes BonusType;
    float Speed;
    Surface Sprite = Surface("Sprites/power-up_3x.bmp");
public:
    Bonus(Vector2D Location, EBonusTypes BonusType = EBonusTypes::ProjectileSpeed, 
        uint32_t Color = Colors::MakeColor(255, 0, 0), float Speed = 200.f, Vector2D Size = { 45.f, 30.f })
        : Entity(Location, Size, Color), BonusType(BonusType), Speed(Speed)
    {
    }
    float GetSpeed()const { return Speed; };

    EBonusTypes GetBonusType()const { return BonusType; }
    bool ColorIncreasing = true;
    uint32_t Interpolate(uint32_t Start, uint32_t End, float dt)
    {
        return Start + dt * (End - Start);
    }

    virtual void Update(const float dt) override
    {
        Location.Y += Speed * dt;
        //Color glow
        if (ColorIncreasing)
        {
            if (color.GetG() >= 253)
                ColorIncreasing = false;
            else
            {
                color = Color(color.GetR(), color.GetG() + 6, color.GetB() - 6);
            }
        }
        else
        {
            if (color.GetG() <= 20)
                ColorIncreasing = true;
            else
            {
                color = Color(color.GetR(), color.GetG() - 6, color.GetB() + 6);
            }
        }
    };

    virtual const void Draw() override
    {
        DrawSprite(Location.X, Location.Y, Entity{ {0, 0}, {47, 47}, Colors::Black }, Entity{ {0, 0}, { SCREEN_WIDTH, SCREEN_HEIGHT }, Colors::Black }, Sprite, Colors::Magenta);
    }
};