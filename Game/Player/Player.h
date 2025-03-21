#pragma once
#include "../Components/GTimer.h"
#include "../Components/ProjectileComponent.h"

class Entity;

enum class EBonusTypes;

enum class Inter
{
    Menu,
    Game,
    PauseMenu,
    GameOver,
    LevelSelect,
    GameCompleted
};

class Player: public Entity
{
private:
    float ProjectileSpeed;
    std::chrono::milliseconds projectilefrequency;
   // std::vector< Vector2D> projectilesLocation;
    //std::chrono::steady_clock::time_point startTime;
    //Vector2D ProjectileSize;

public:
    Player(Vector2D Location, Vector2D Size, float Speed, uint32_t Color, int8_t Health, float ProjectileSpeed, std::chrono::milliseconds projectilefrequency);

    int8_t Health;
    bool isAlive = true;
    bool MouseMode = false;
    int KillCount = 0;

    ProjectileComponent ProjComponent;

    void Control(float dt, Inter& GameMode);

    bool BonusCollision(const Vector2D BonusLocation, const Vector2D BonusSize, const EBonusTypes BonusType);
    
    void BonusEffect(EBonusTypes BonusType);

    Vector2D GetLocation() const { return Location; }

    Vector2D GetSize() const { return Size; }

    void SetLocation(const float X = 200.0f, const float Y = 600.0f) { Location = { X, Y }; }

    void SetColor(const uint32_t LColor) { Color = LColor; }

    uint32_t &GetColor() { return Color; }
    
    bool GetIsAlive() const { return isAlive; }
    float GetProjectileSpeed() const { return ProjectileSpeed; }

    void Update();
};

