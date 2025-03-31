#pragma once
#include <chrono>
//#include "../Components/ProjectileComponent.h"
#include "../Entity/Entity.h"
#include "../Engine/Engine.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/Bonus.h"

class Player: public Entity
{
private:
    std::chrono::milliseconds projectilefrequency;
   // std::vector< Vector2D> projectilesLocation;
    //std::chrono::steady_clock::time_point startTime;
    //Vector2D ProjectileSize;

public:
    
    Player(Vector2D Location, Vector2D Size, float Speed, uint32_t Color, int8_t Health, std::chrono::milliseconds projectilefrequency);
    int8_t Health;
    bool isAlive = true;
    bool MouseMode = false;
    int KillCount = 0;

    ProjectileComponent ProjComponent{ {Location.X + Size.X / 2 - 5.f, Location.Y - 20.f}, {10.f, 10.f}, 500.f, Colors::Blue};

    void Control(float dt);

    void BonusEffect(EBonusTypes BonusType);

    //bool BonusCollision(const Vector2D BonusLocation, const Vector2D BonusSize, const EBonusTypes BonusType);
    
    //void BonusEffect(EBonusTypes BonusType);

    bool GetIsAlive() const { return isAlive; }

    virtual void Update(const float dt) override;

    bool PressedExit();

    virtual const void Draw() override;
};

//int Loafa = 123;
