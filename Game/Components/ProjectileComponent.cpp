#include "ProjectileComponent.h"
#include "../Engine/GTimer.h"

ProjectileComponent::ProjectileComponent(Vector2D Location, Vector2D Size = { 10.f, 25.f }, float Speed = 400.f,
    uint32_t Color = Colors::MakeColor(255, 0, 255))
    : Entity(Location, Size, Color), Speed(Speed)
{
    projectiles.reserve(18);
}

//try buffering projectiles that out of bound or collided
// launching projectile at the location, with delay between
void ProjectileComponent::Shoot(const std::chrono::milliseconds time)
{
    if (DidTimerEnd(startTime, time))
    {
        //projectilesLocation.push_back({ Location.X + width / 2 - Size.X/2, Location.Y - 3.f });
        projectiles.emplace_back(Location, Size, Speed, color);
        StartTimer(startTime);
    }
}

//rewrite for parent class of player and enemy to projectile
void ProjectileComponent::CollisionRect(int8_t& EnemyHealth, const uint8_t Damage, bool& isAlive, const Vector2D EnemyLocation, const Vector2D EnemySize)
{
    for (int i = 0; i < projectiles.size(); i++)
    {
        if (projectiles.at(i).Collision(EnemyLocation, EnemySize))
        {
            EnemyHealth -= Damage;
            projectiles.erase(projectiles.begin() + i);
            //projectiles.at(i).SetLocation(Location.X, Location.Y);
            if (EnemyHealth <= 0)
            {
                isAlive = false;
            }
        }
    }
}

//Collision with enemy projectiles
void ProjectileComponent::CollisionRect(std::vector<Projectile>& EnemyProjectiles)
{
    for (int i = 0; i < projectiles.size(); i++)
    {
        for (int j = 0; j < EnemyProjectiles.size(); j++)
        {
            //proj.projectiles.at(j).Collision(projectiles.at(i))
            if (projectiles.at(i).Collision(EnemyProjectiles.at(j)))
            {
                //proj.EraseProjectile(j);
              
                projectiles.erase(projectiles.begin() + i);

                EnemyProjectiles.erase(EnemyProjectiles.begin() + j);
                //projectiles.at(i).SetLocation(Location.X, Location.Y);
                //StartTimer(startTime);
            }
        }
    }
}

void ProjectileComponent::Move(Vector2D Location)
{
    SetLocation(Location.X, Location.Y);
}

void ProjectileComponent::Update(const float dt)
{
    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles.at(i).Update(dt);
        if((projectiles.at(i).GetLocation().Y < 0.f || projectiles.at(i).GetLocation().Y > 768))
            projectiles.erase(projectiles.begin() + i);
    }
}

const void ProjectileComponent::Draw()
{
    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles.at(i).Draw();
    }
}


