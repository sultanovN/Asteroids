#pragma once
#include "Utility.h"

class Player
{
private:
    Vector2D Location;
    Vector2D Size;
    uint32_t Color;
    float ProjectileSpeed;
    std::chrono::milliseconds projectilefrequency;
   // std::vector< Vector2D> projectilesLocation;
    //std::chrono::steady_clock::time_point startTime;
    //Vector2D ProjectileSize;

public:

    Player(Vector2D Location = { 500.0f, 600.0f }, Vector2D Size = { 50.f, 60.f }, int8_t Health = 3,
        uint32_t Color = MakeColor(125, 0, 125), bool MouseMode = false, float ProjectileSpeed = 500.f, 
        std::chrono::milliseconds projectilefrequency = std::chrono::milliseconds(300))
        : Location(Location), Size(Size), Health(Health), Color(Color), MouseMode(MouseMode), 
        projectilefrequency(projectilefrequency), ProjectileSpeed(ProjectileSpeed)
    {
    }

    ProjectileComponent ProjectileComponent;
    //HealthComponent HealthComp;
    int8_t Health;
    bool isAlive = true;
    bool MouseMode = false;
    int KillCount = 0;


    void Control(float dt)
    {
        if (!GetIsAlive())
        {
            GameMode = Inter::Menu;

            if (is_key_pressed(VK_SPACE))
            {

                isAlive = true;
                initialize();
            }

            if (is_key_pressed(VK_ESCAPE))
            {
                schedule_quit_game();
            }
        }

        if (is_key_pressed(VK_ESCAPE))
        {
            GameMode = Inter::PauseMenu;
            //schedule_quit_game();
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
            ProjectileComponent.Shoot(GetLocation(), GetSize().X, projectilefrequency);
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

    bool BonusCollision(const Vector2D BonusLocation, const Vector2D BonusSize, const EBonusTypes BonusType)
    {
        if (RectRectCollision(Location.X, Location.Y, Size.X, Size.Y,
            BonusLocation.X, BonusLocation.Y, BonusSize.X, BonusSize.Y))
        {
            BonusEffect(BonusType);
            return true;
        }
        return false;
    }
    
    void BonusEffect(EBonusTypes BonusType)
    {
        switch (BonusType)
        {
        case EBonusTypes::Health:
        {
            if(Health < 3)
                Health++;
            break;
        }
        case EBonusTypes::ProjectileFreq:
        {
            if (projectilefrequency > std::chrono::milliseconds(140))
            {
                projectilefrequency = std::chrono::milliseconds(150);
                Color = MakeColor(0, 0, 255);
            }
            else if (Health < 3)
                Health++;
            break;
        }
        case EBonusTypes::ProjectileSpeed:
        {
            if (ProjectileSpeed < 900.f)
            {
                ProjectileSpeed *= 2.f;
                Color = MakeColor(0, 160, 200);
            }
            else if (Health < 3)
                Health++;
            break;
        }
        //case EBonusTypes::TwoProjectileShoot:
        default:
        {
            if (Health < 3)
                Health++;
            break;
        }
        }
    }

    Vector2D GetLocation() const { return Location; }

    Vector2D GetSize() const { return Size; }

    void SetLocation(const float X = 200.0f, const float Y = 600.0f) { Location = { X, Y }; }

    void SetColor(const uint32_t LColor) { Color = LColor; }

    uint32_t &GetColor() { return Color; }
    
    bool GetIsAlive() const { return isAlive; }
    float GetProjectileSpeed() const { return ProjectileSpeed; }
};