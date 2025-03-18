#pragma once
#include "../Entity.h"

class Player: public Entity
{
private:
    Vector2D Location;
    Vector2D Size;
    uint32_t Color;
    float Speed;
    float ProjectileSpeed;
    std::chrono::milliseconds projectilefrequency;
   // std::vector< Vector2D> projectilesLocation;
    //std::chrono::steady_clock::time_point startTime;
    //Vector2D ProjectileSize;

public:

    Player(Vector2D Location, Vector2D Size = { 40.f, 50.f }, float Speed = 300.f,
        uint32_t Color = Colors::Red, int8_t Health = 2, float ProjectileSpeed = 500.f,
        std::chrono::milliseconds projectilefrequency = std::chrono::milliseconds(300))
        : Entity(Location, Size, Speed, Color), ProjectileSpeed(ProjectileSpeed), projectilefrequency(projectilefrequency)
    {
    }

    ProjectileComponent ProjectileComponent;
    int8_t Health;
    bool isAlive = true;
    bool MouseMode = false;
    int KillCount = 0;

    void Control(float dt);

    bool BonusCollision(const Vector2D BonusLocation, const Vector2D BonusSize, const EBonusTypes BonusType);
    
    void BonusEffect(EBonusTypes BonusType);

    Vector2D GetLocation() const { return Location; }

    Vector2D GetSize() const { return Size; }

    void SetLocation(const float X = 200.0f, const float Y = 600.0f) { Location = { X, Y }; }

    void SetColor(const uint32_t LColor) { Color = LColor; }

    uint32_t &GetColor() { return Color; }
    
    bool GetIsAlive() const { return isAlive; }
    float GetProjectileSpeed() const { return ProjectileSpeed; }
};