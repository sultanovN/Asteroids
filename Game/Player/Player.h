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
    float Speed;
    //Surface Sprite = Surface("C:/Projects/Asteroids/Game/Images/playerShip1_blue.bmp");
    Surface Sprite = Surface("C:/Projects/Asteroids/Game/Images/ship_4x.bmp");

    bool Idle = false;
    Entity Idle_1{ {128, 0}, {63, 95}, Colors::Black };
    Entity Idle_2{ {128, 96}, {63, 95}, Colors::Black };
    Entity RightRegion{ {196, 0}, {63, 95}, Colors::Black };
    Entity LeftRegion{ {68, 0}, {63, 95}, Colors::Black };

    Entity CurrentSpriteRegion = Idle_1;

    int PreviousCursorLocationX = 0;
   // std::vector< Vector2D> projectilesLocation;
    //std::chrono::steady_clock::time_point startTime;
    //Vector2D ProjectileSize;

public:
    
    Player(Vector2D Location, Vector2D Size, float Speed, uint32_t Color, int8_t Health, std::chrono::milliseconds projectilefrequency);
    int8_t Health;
    bool isAlive = true;
    bool MouseMode = false;
    int KillCount = 0;

    float GetSpeed()const { return Speed; };

    ProjectileComponent ProjComponent{ {Location.X + Size.X / 2 - 5.f, Location.Y - 20.f}, Surface("C:/Projects/Asteroids/Game/Images/laser-bolts_4x.bmp"), {24, 28}, {19, 19}, 500.f, Colors::Blue};

    void Control(float dt);

    void BonusEffect(EBonusTypes BonusType);

    //void Damage(const uint8_t Damage, ProjectileComponent ProjComp);

    //bool BonusCollision(const Vector2D BonusLocation, const Vector2D BonusSize, const EBonusTypes BonusType);
    
    //void BonusEffect(EBonusTypes BonusType);

    bool GetIsAlive() const { return isAlive; }

    virtual void Update(const float dt) override;

    bool PressedExit();

    virtual const void Draw() override;

    const Vector2D GetSpriteSize() { return CurrentSpriteRegion.GetSize(); }
};

//int Loafa = 123;
