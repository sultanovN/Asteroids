#pragma once
#include <stdint.h>
#include <chrono>
#include <vector>


//how timer works
// in a loop
//if (DidTimerEnd(startTime))
//{
//    doStuff
//    StartTimer(startTime);
//}

void StartTimer(std::chrono::steady_clock::time_point &startTime)
{
    startTime = std::chrono::steady_clock::now(); //auto
}

bool DidTimerEnd(std::chrono::steady_clock::time_point startTime)
{
    using namespace std::chrono_literals;
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(now - startTime) >= 1s)
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
    std::vector< Vector2D> projectilesLocation;
    Vector2D Size;
    uint32_t Color;
    std::chrono::steady_clock::time_point startTime;
    bool UpDirection;

public:

    ProjectileComponent(bool UpDirection = true,Vector2D ProjectileSize = { 10.f, 10.f }, uint32_t Color = MakeColor(255, 0, 255))
        : UpDirection(UpDirection), Size(ProjectileSize), Color(Color)
    {

    }

    void Shoot(Vector2D Location, float width)
    {
        if (DidTimerEnd(startTime))
        {
            projectilesLocation.push_back({ Location.X + width / 2 - Size.X/2, Location.Y - 3.f });
            StartTimer(startTime);
        }

    }

    void ProjMove(float dt)
    {
        for (int i = 0; i < projectilesLocation.size(); i++)
        {
            if (UpDirection)
            {
                projectilesLocation.at(i).Y -= 200.f * dt;
                if (projectilesLocation.at(i).Y < 0.f)
                    projectilesLocation.erase(projectilesLocation.begin() + i);
            }
            else
            {
                projectilesLocation.at(i).Y += 200.f * dt;
                if (projectilesLocation.at(i).Y > SCREEN_HEIGHT)
                    projectilesLocation.erase(projectilesLocation.begin() + i);
            }
        }
    }

    void ProjDraw()
    {
        for (Vector2D proj : projectilesLocation)
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
};
