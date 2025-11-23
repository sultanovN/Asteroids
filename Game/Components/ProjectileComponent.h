#pragma once
#include <vector>
#include <chrono>
//#include "GTimer.h"
#include "Projectile.h"

//rewrite
class ProjectileComponent: public Entity
{
private:
    std::vector<Projectile> projectiles;
    std::chrono::steady_clock::time_point startTime;
    float Speed;
    Surface Sprite;
    Vector2D SpriteRegionLocation;
public:
    ProjectileComponent(Vector2D Location, Surface Sprite, Vector2D SpriteRegionLocation, Vector2D Size, float Speed, uint32_t Color);

    float GetSpeed()const { return Speed; };

    std::vector<Projectile>& GetProjectiles() { return projectiles; }

    void SetSpeed(const float Speed) { this->Speed = Speed; }

    Vector2D GetSize()const { return Size; }

    void Shoot(const std::chrono::milliseconds time);
    void Shoot(const std::chrono::milliseconds time, Vector2D fLocation);

    void Move(Vector2D Location);

    void CollisionRect(int8_t& EnemyHealth, const uint8_t Damage, bool& isAlive, const Vector2D EnemyLocation, const Vector2D EnemySize);

    void CollisionRect(std::vector<Projectile> &EnemyProjectiles, const bool destructable = true);

    //void EraseProjectile(const int i)
    //{
    //    projectiles.erase(projectiles.begin() + i);
    //}

    virtual void Update(const float dt) override;
    virtual const void Draw() override;

    //void ProjDraw()
    //{
    //    for (Projectile& proj : projectiles)
    //    {
    //        for (int x = 0; x < SCREEN_WIDTH; x++)
    //            for (int y = 0; y < SCREEN_HEIGHT; y++)
    //            {
    //                if ((x >= proj.GetLocation().X && (x <= proj.GetLocation().X + Size.X)) &&
    //                    (y >= proj.GetLocation().Y && (y <= proj.GetLocation().Y + Size.Y)))
    //                {
    //                    buffer[y][x] = Color;
    //                }
    //                /*else
    //                {
    //                    buffer[y][x] = MakeColor(255, 255, 255);
    //                }*/
    //            }
    //    }
    //}
};