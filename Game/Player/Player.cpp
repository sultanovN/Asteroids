#include "Player.h"
#include "../Components/GTimer.h"
#include "../Utility.h"
//remove GInterface
#include "../Engine/Engine.h"
Inter GameMode = Inter::Menu;

void Player::Control(float dt)
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