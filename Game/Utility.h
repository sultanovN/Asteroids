#pragma once
#include <stdint.h>
#include <chrono>
#include <vector>
#include <thread>
#include <random>

std::random_device randDev;
std::mt19937 gen(randDev());

int RandomNumberInRange(int min, int max)
{
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

class HealthComponent;

const void objectDraw(float X, float Y, float width, float height, uint32_t objectColor)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            if ((x >= X && (x <= X + width)) && (y >= Y && (y <= Y + height)))
            {
                buffer[y][x] = objectColor;
            }
        }
}

enum class Inter
{
    Menu,
    Game,
    PauseMenu,
    GameOver,
    LevelSelect,
    GameCompleted,
};

enum class Button
{
    Start,
    Second,
    Exit //level select
};

Inter GameMode = Inter::Menu;

Button button = Button::Start;



//how timer works
// in a loop
//if (DidTimerEnd(startTime))
//{
//    doStuff
//    StartTimer(startTime);
//}

void StartTimer(std::chrono::steady_clock::time_point& startTime)
{
    startTime = std::chrono::steady_clock::now(); //auto
}

bool DidTimerEnd(const std::chrono::steady_clock::time_point& startTime, const std::chrono::milliseconds time)
{
    using namespace std::chrono_literals;
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime) >= time)
    {
        return true;
    }
    return false;
}



uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b)
{
    return r << 16 | g << 8 | b;
}

struct Vector2D
{
    float X, Y;

    Vector2D(float X, float Y)
        : X(X), Y(Y)
    {

    }
};

bool RectRectCollision(float r1x, float r1y, float r1w, float r1h,
    float r2x, float r2y, float r2w, float r2h)
{
    if (r1x + r1w >= r2x &&
        r1x <= r2x + r2w &&
        r1y + r1h >= r2y &&
        r1y < r2y + r2h)
        return true;
    return false;
}

//struct Projectile
//{
//    Vector2D Location;
//    Vector2D ProjectileSize;
//    uint32_t Color;
//};


class ProjectileComponent
{
private:
    std::vector<Vector2D> projectilesLocation;
    Vector2D Size;
    uint32_t Color;
    std::chrono::steady_clock::time_point startTime;


    //bool UpDirection;

public:

    ProjectileComponent(Vector2D ProjectileSize = { 10.f, 10.f }, uint32_t Color = MakeColor(255, 0, 255), Vector2D Destination = {0.f, 0.f})
        :  Size(ProjectileSize), Color(Color)
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
        for (Vector2D &proj : projectilesLocation)
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

    void CollisionRect( int8_t &EnemyHealth, const uint8_t Damage, bool& isAlive, const Vector2D EnemyLocation, const Vector2D EnemySize)
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

    /*if (DidTimerEnd(color, std::chrono::milliseconds(1000)))
    {
        StartTimer(now);

        if (shot)
        {
            EnemyColor = MakeColor(200, 0, 0);
            shot = false;
        }
        else
        {
            EnemyColor = MakeColor(200, 0, 200);
            shot = true;

        }
    }*/


    void CollisionProj(ProjectileComponent &proj)
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

enum class EBonusTypes
{
    Health,
    ProjectileFreq,
    ProjectileSpeed,
    TwoProjectileShoot,
};

//Bonus will appear with the death of enemy at his place and slowly fall down
class Bonus
{
    Vector2D Location;
    Vector2D Size;
    float speed;
    EBonusTypes BonusType;
    uint32_t Color;

public:
    Bonus(Vector2D Location, EBonusTypes BonusType = EBonusTypes::ProjectileSpeed, uint32_t Color = MakeColor(255, 0, 0), float speed = 200.f, Vector2D Size = {30.f, 30.f})
        : Location(Location), BonusType(BonusType), Color(Color), speed(speed), Size(Size)
    {
        //randomize bonus type
    }

    //temporary or constant till damage
    
    void Move(float dt)
    { 
        Location.Y += speed * dt;
    }

    EBonusTypes GetBonusType()const { return BonusType; }

    Vector2D GetLocation() const { return Location; }
    Vector2D GetSize() const { return Size; }
    uint32_t GetColor() const { return Color; }
};

//class HealthComponent
//{
//    uint8_t Health;
//
//public:
//    HealthComponent()
//        : Health(2)
//    {
//
//    }
//
//    void ReduceHealth(uint8_t Damage)
//    {
//        Health -= Damage;
//    }
//};