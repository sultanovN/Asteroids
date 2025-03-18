#pragma once
#include <vector>
#include "GTimer.h"
#include "Vector2D.h"
#include "Color.h"

class ProjectileComponent
{
private:
    std::vector<Vector2D> projectilesLocation;
    Vector2D Size;
    uint32_t Color;
    std::chrono::steady_clock::time_point startTime;

public:

    ProjectileComponent(Vector2D ProjectileSize = { 10.f, 10.f }, uint32_t Color = MakeColor(255, 0, 255), Vector2D Destination = { 0.f, 0.f })
        : Size(ProjectileSize), Color(Color)
    {
        projectilesLocation.reserve(18);
    }

    std::vector<Vector2D> GetProjectilesLocation() { return projectilesLocation; }

    Vector2D GetSize()const { return Size; }

    // launching projectile at the location, with milliseconds delay
    void Shoot(const Vector2D Location, const float width, const std::chrono::milliseconds time)
    {
        if (DidTimerEnd(startTime, time))
        {
            //projectilesLocation.push_back({ Location.X + width / 2 - Size.X/2, Location.Y - 3.f });
            projectilesLocation.emplace_back(Location.X + width / 2 - Size.X / 2, Location.Y - 2.f);
            StartTimer(startTime);
        }

    }

    void EraseProjectile(const int i)
    {
        projectilesLocation.erase(projectilesLocation.begin() + i);
    }

    void ProjMove(const float dt, const float speed)
    {
        for (int i = 0; i < projectilesLocation.size(); i++)
        {
            projectilesLocation.at(i).Y -= speed * dt;
            if (projectilesLocation.at(i).Y < 0.f || projectilesLocation.at(i).Y > SCREEN_HEIGHT)
                projectilesLocation.erase(projectilesLocation.begin() + i);
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

    void ProjDraw()
    {

        for (Vector2D& proj : projectilesLocation)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
                for (int y = 0; y < SCREEN_HEIGHT; y++)
                {
                    if ((x >= proj.X && (x <= proj.X + Size.X)) &&
                        (y >= proj.Y && (y <= proj.Y + Size.Y)))
                    {
                        buffer[y][x] = Color;
                    }
                    /*else
                    {
                        buffer[y][x] = MakeColor(255, 255, 255);
                    }*/
                }
        }

    }

    void CollisionRect(int8_t& EnemyHealth, const uint8_t Damage, bool& isAlive, const Vector2D EnemyLocation, const Vector2D EnemySize)
    {
        for (int i = 0; i < projectilesLocation.size(); i++)
        {
            if (RectRectCollision(EnemyLocation.X, EnemyLocation.Y, EnemySize.X, EnemySize.Y,
                projectilesLocation.at(i).X, projectilesLocation.at(i).Y, Size.X, Size.Y))
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

    void CollisionProj(ProjectileComponent& proj)
    {
        for (int i = 0; i < projectilesLocation.size(); i++)
        {
            for (int j = 0; j < proj.projectilesLocation.size(); j++)
            {
                if (RectRectCollision(proj.projectilesLocation.at(j).X, proj.projectilesLocation.at(j).Y, proj.GetSize().X, proj.GetSize().Y,
                    projectilesLocation.at(i).X, projectilesLocation.at(i).Y, Size.X, Size.Y))
                {
                    proj.EraseProjectile(j);
                    projectilesLocation.erase(projectilesLocation.begin() + i);

                }
            }

        }
    }
};