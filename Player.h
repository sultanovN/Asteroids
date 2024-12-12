#pragma once
#include "Utility.h"

class Player
{
private:
    Vector2D Location;
    Vector2D Size;
    uint32_t Color;
   // std::vector< Vector2D> projectilesLocation;
    //std::chrono::steady_clock::time_point startTime;
    //Vector2D ProjectileSize;

public:

    Player(Vector2D Location = { 500.0f, 600.0f }, Vector2D Size = { 50.f, 60.f }, int8_t Health = 100,
        uint32_t Color = MakeColor(125, 0, 125), bool MouseMode = false)
        : Location(Location), Size(Size), Health(Health), Color(Color), MouseMode(MouseMode)
    {
    }

    ProjectileComponent ProjectileComponent;
    //HealthComponent HealthComp;
    int8_t Health;
    bool isAlive = true;
    bool MouseMode = false;

    void Control(float dt)
    {
        if (!GetIsAlive())
        {
            while (1)
            {
                if (is_key_pressed(VK_SPACE))
                {
                    isAlive = true;
                    initialize();
                    break;
                }

                if (is_key_pressed(VK_ESCAPE))
                {
                    schedule_quit_game();
                }
            }
        }

        if (is_key_pressed(VK_ESCAPE))
        {
            schedule_quit_game();
        }

        if (is_key_pressed(VK_RIGHT) && (GetLocation().X + GetSize().X < SCREEN_WIDTH))
        {
            SetLocation(GetLocation().X + 400.f * dt, GetLocation().Y);
        }

        if (is_key_pressed(VK_LEFT) && (GetLocation().X > 0))
        {
            SetLocation(GetLocation().X - 400.f * dt, GetLocation().Y);
        }

        if (is_key_pressed(VK_SPACE) || is_mouse_button_pressed(0))
        {
            ProjectileComponent.Shoot(GetLocation(), GetSize().X, std::chrono::milliseconds(500));
        }


        if ((is_mouse_button_pressed(0) || is_mouse_button_pressed(1) || is_key_pressed(VK_RETURN)) && !MouseMode)
        {
            MouseMode = true;
        }

        if (is_key_pressed(VK_RETURN) && MouseMode)
            MouseMode = false;

        if (MouseMode && (get_cursor_x() < (SCREEN_WIDTH - GetSize().X / 2) && (get_cursor_x() > 0)))
        {
            SetLocation(get_cursor_x() + 400.f * dt, GetLocation().Y);
        }
    }

    

    Vector2D GetLocation() const { return Location; }

    Vector2D GetSize() const { return Size; }

    void SetLocation(const float X = 200.0f, const float Y = 600.0f) { Location = { X, Y }; }

    void SetColor(const uint32_t LColor) { Color = LColor; }

    uint32_t GetColor() const { return Color; }
    
    bool GetIsAlive() const { return isAlive; }
};