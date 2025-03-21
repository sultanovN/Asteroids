#pragma once
#include <vector>
#include "GTimer.h"
#include "../Entity.h"

class Projectile: public Entity
{
public:
    Projectile(Vector2D Location, Vector2D Size, float Speed, uint32_t Color)
        : Entity(Location, Size, Speed, Color)
    {
    }
};

//rewrite
class ProjectileComponent
{
private:
    std::vector<Projectile> projectiles;
    Vector2D Size;
    uint32_t Color;
    std::chrono::steady_clock::time_point startTime;

public:

    ProjectileComponent(Vector2D ProjectileSize = { 10.f, 10.f }, uint32_t Color = Colors::MakeColor(255, 0, 255), Vector2D Destination = { 0.f, 0.f })
        : Size(ProjectileSize), Color(Color)
    {
        projectiles.reserve(18);
    }

    std::vector<Projectile> GetProjectilesLocation() { return projectiles; }

    Vector2D GetSize()const { return Size; }

    // launching projectile at the location, with milliseconds delay
    void Shoot(const Vector2D Location, const float width, const std::chrono::milliseconds time)
    {
        if (DidTimerEnd(startTime, time))
        {
            //projectilesLocation.push_back({ Location.X + width / 2 - Size.X/2, Location.Y - 3.f });
            projectiles.emplace_back(Location.X + width / 2 - Size.X / 2, Location.Y - 2.f);
            StartTimer(startTime);
        }

    }

    void EraseProjectile(const int i)
    {
        projectiles.erase(projectiles.begin() + i);
    }

    void ProjMove(const float dt, const float speed)
    {
        for (int i = 0; i < projectiles.size(); i++)
        {
            projectiles.at(i).SetLocation(projectiles.at(i).GetLocation().X, projectiles.at(i).GetLocation().Y - speed * dt);
            if (projectiles.at(i).GetLocation().Y < 0.f || projectiles.at(i).GetLocation().Y > 768)
            {
                projectiles.erase(projectiles.begin() + i);
            }
            /*if (UpDirection)
            {

            }*/
            /*else
            {
                projectilesLocation.at(i).Y += speed * dt;
                if (projectilesLocation.at(i).Y > SCREEN_HEIGHT)
                    projectilesLocation.erase(projectilesLocation.begin() + i);
            }*/
        }
    }

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

    void CollisionRect(int8_t& EnemyHealth, const uint8_t Damage, bool& isAlive, const Vector2D EnemyLocation, const Vector2D EnemySize)
    {
        for (int i = 0; i < projectiles.size(); i++)
        {
            if (RectRectCollision(EnemyLocation.X, EnemyLocation.Y, EnemySize.X, EnemySize.Y,
                projectiles.at(i).GetLocation().X, projectiles.at(i).GetLocation().Y, Size.X, Size.Y))
            {
                EnemyHealth -= Damage;

                EraseProjectile(i);
                if (EnemyHealth <= 0)
                {
                    isAlive = false;
                }
            }
        }
    }

    //Collision with enemy projectiles
    void CollisionProj(ProjectileComponent& proj)
    {
        for (int i = 0; i < projectiles.size(); i++)
        {
            for (int j = 0; j < proj.projectiles.size(); j++)
            {
                if (RectRectCollision(proj.projectiles.at(j).GetLocation().X, proj.projectiles.at(j).GetLocation().Y, proj.GetSize().X, proj.GetSize().Y,
                    projectiles.at(i).GetLocation().X, projectiles.at(i).GetLocation().Y, Size.X, Size.Y))
                {
                    proj.EraseProjectile(j);
                    projectiles.erase(projectiles.begin() + i);

                }
            }

        }
    }
};