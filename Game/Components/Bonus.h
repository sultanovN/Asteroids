#pragma once
#include <stdint.h>
#include "../Entity.h"

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
        uint32_t Color = MakeColor(255, 0, 0), float Speed = 200.f, Vector2D Size = { 30.f, 30.f })
        : Entity(Location, Size, Speed, Color), BonusType(BonusType)
    {
    }

    EBonusTypes GetBonusType()const { return BonusType; }

    void Move(float dt){Location.Y += Speed * dt;}
};