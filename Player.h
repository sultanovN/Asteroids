#pragma once
#include "Utility.h"
#include <vector>



class Player
{
private:
    Vector2D Location;
    Vector2D Size;
    uint32_t Color;
    std::vector<Projectile> projectiles;

public:

    Player(Vector2D Location = { 500.0f, 600.0f }, Vector2D Size = { 50.f, 60.f },
        uint32_t Color = MakeColor(125, 0, 125))
        : Location(Location), Size(Size), Color(Color)
    {
    }

    Vector2D GetLocation() { return Location; }

    Vector2D GetSize() { return Size; }

    void SetLocation(float X = 200.0f, float Y = 200.0f) { Location = { X, Y }; }

    void SetColor(uint32_t LColor) { Color = LColor; }

    uint32_t GetColor() { return Color; }

    void Shoot()
    {
        projectiles.push_back(Projectile{ {GetLocation().X, GetLocation().Y - 3.f}, {5.f, 5.f}, 
            MakeColor(255, 0, 255)});
    }

    void ProjMove(float dt)
    {
        for (int i = 0; i < projectiles.size(); i++)
        {
            projectiles.at(i).Location.Y -= 200.f * dt;
            if (projectiles.at(i).Location.Y < 0.f)
                projectiles.erase(projectiles.begin() + i);
        }
    }

    void ProjDraw()
    {
        for (Projectile proj : projectiles)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
                for (int y = 0; y < SCREEN_HEIGHT; y++)
                {
                    if ((x >= proj.Location.X && (x <= proj.Location.X + proj.Size.X)) &&
                        (y >= proj.Location.Y && (y <= proj.Location.Y + proj.Size.Y)))
                    {
                        buffer[y][x] = proj.Color;
                    }
                    /*else
                    {
                        buffer[y][x] = MakeColor(255, 255, 255);
                    }*/
                }
        }
        
    }
    
};