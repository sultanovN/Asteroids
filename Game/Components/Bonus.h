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
    bool changing = true;
    uint32_t Interpolate(uint32_t Start, uint32_t End, float dt)
    {
        return Start + dt * (End - Start);
    }

    virtual void Update(const float dt) override
    {
        Location.Y += Speed * dt;
        //Color glow
        if (changing)
        {
            Color = Interpolate(Color, Colors::Blue, 1);
            if (Color == Colors::Blue)
                changing = 0;
        }
        else
        {
            Color = Interpolate(Color, Colors::Red,1);
            if (Color == Colors::Red)
                changing = 1;
        }
    };
};