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
public:
    Bonus(Vector2D Location, EBonusTypes BonusType = EBonusTypes::ProjectileSpeed, 
        uint32_t Color = Colors::MakeColor(255, 0, 0), float Speed = 200.f, Vector2D Size = { 30.f, 30.f })
        : Entity(Location, Size, Speed, Color), BonusType(BonusType)
    {
    }

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
            if (color.GetR() >= 253)
                ColorIncreasing = false;
            else
            {
                color = Color(color.GetR() + 6, 0, color.GetB() - 6);
            }
        }
        else
        {
            if (color.GetR() <= 20)
                ColorIncreasing = true;
            else
            {
                color = Color(color.GetR() - 6, 0, color.GetB() + 6);
            }
        }
    };
};