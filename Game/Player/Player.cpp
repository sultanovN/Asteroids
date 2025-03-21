#include "Player.h"
#include "../Components/Bonus.h"
#include "../Components/Graphics.h"

//remove GInterface

Player::Player(Vector2D Location, Vector2D Size = { 40.f, 50.f }, float Speed = 300.f,
    uint32_t Color = Colors::Red, int8_t Health = 2, float ProjectileSpeed = 500.f,
    std::chrono::milliseconds projectilefrequency = std::chrono::milliseconds(300))
    : Entity(Location, Size, Speed, Color), Health(Health), ProjectileSpeed(ProjectileSpeed), projectilefrequency(projectilefrequency)
{
}

void Player::Control(float dt, Inter& GameMode)
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
        ProjComponent.Shoot(GetLocation(), GetSize().X, projectilefrequency);
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

bool Player::BonusCollision(const Vector2D BonusLocation, const Vector2D BonusSize, const EBonusTypes BonusType)
{
    if (RectRectCollision(Location.X, Location.Y, Size.X, Size.Y,
        BonusLocation.X, BonusLocation.Y, BonusSize.X, BonusSize.Y))
    {
        BonusEffect(BonusType);
        return true;
    }
    return false;
}

void Player::BonusEffect(EBonusTypes BonusType)
{
    switch (BonusType)
    {
    case EBonusTypes::Health:
    {
        if (Health < 3)
            Health++;
        break;
    }
    case EBonusTypes::ProjectileFreq:
    {
        if (projectilefrequency > std::chrono::milliseconds(140))
        {
            projectilefrequency = std::chrono::milliseconds(150);
            Color = Colors::MakeColor(0, 0, 255);
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
            Color = Colors::MakeColor(0, 160, 200);
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

void Player::Update()
{
}
