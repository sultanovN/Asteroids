#include "Player.h"

Player::Player(Vector2D Location, Vector2D Size = { 63, 95 }, float Speed = 300.f,
    uint32_t Color = Colors::Red, int8_t Health = 2,
    std::chrono::milliseconds projectilefrequency = std::chrono::milliseconds(300))
    : Entity(Location, Size,Color), Health(Health), projectilefrequency(projectilefrequency), Speed(Speed)
{
}

void Player::Update(const float dt)
{
    Control(dt);
    ProjComponent.Move({ Location.X + Size.X / 2 - 5.f, Location.Y - 20.f });
    ProjComponent.Update(dt);
}

bool Player::PressedExit()
{
    return is_key_pressed(VK_ESCAPE);
}

const void Player::Draw()
{
    DrawSprite(Location.X, Location.Y, CurrentSpriteRegion, Sprite, Colors::Magenta);


    /*if (Idle)
    {
        DrawSprite(Location.X, Location.Y, Idle_2, Sprite, Colors::Magenta);
        Idle = false;
    }
    else
    {
        DrawSprite(Location.X, Location.Y, Idle_1, Sprite, Colors::Magenta);
        Idle = true;
    }*/


    ProjComponent.Draw();
}

void Player::Control(float dt)
{
    if (!GetIsAlive())
    {
        ////rewrite in gameclass
       // GameMode = Inter::Menu;

        if (is_key_pressed(VK_SPACE))
        {
            isAlive = true;
            initialize();
        }

        if (PressedExit())
        {
            schedule_quit_game();
        }
    }

    if (Health == 0)
        isAlive = false;
    //if (is_key_pressed(VK_ESCAPE))
    //{
    //    //rewrite in gameclass
    //    //GameMode = Inter::PauseMenu;
    //    //schedule_quit_game();
    //}

    if ((is_key_pressed(VK_RIGHT) || is_key_pressed(VK_D)) && (GetLocation().X + GetSize().X < SCREEN_WIDTH))
    {
        SetLocation(GetLocation().X + 400.f * dt, GetLocation().Y);
        CurrentSpriteRegion = RightRegion;
    }
    else if ((is_key_pressed(VK_LEFT) || is_key_pressed(VK_A)) && (GetLocation().X > 0))
    {
        SetLocation(GetLocation().X - 400.f * dt, GetLocation().Y);
        CurrentSpriteRegion = LeftRegion;
    }
    else
    {
        CurrentSpriteRegion = Idle_1;
    }

    if (is_key_pressed(VK_SPACE) || is_mouse_button_pressed(0))
    {
        ProjComponent.Shoot(projectilefrequency);
    }

    //is_mouse_button_pressed(0) || is_mouse_button_pressed(1) || 

    if ((is_key_pressed(VK_RETURN)) && !MouseMode)
    {
        MouseMode = true;
    }

    if (is_key_pressed(VK_RETURN) && MouseMode)
        MouseMode = false;

    if (MouseMode && (get_cursor_x() < (SCREEN_WIDTH - GetSize().X / 2) && (get_cursor_x() > 0)))
    {
        if ((get_cursor_x() - PreviousCursorLocationX) < -3)
        {
            CurrentSpriteRegion = LeftRegion;
        }
        else if ((get_cursor_x() - PreviousCursorLocationX) > 3)
        {
            CurrentSpriteRegion = RightRegion;
        }
        else
            CurrentSpriteRegion = Idle_1;
        SetLocation(get_cursor_x() + 400.f * dt, GetLocation().Y);
        PreviousCursorLocationX = get_cursor_x();

    }
}

//bool Player::BonusCollision(const Vector2D BonusLocation, const Vector2D BonusSize, const EBonusTypes BonusType)
//{
//    if (Collision(Location, Size,
//        BonusLocation, BonusSize))
//    {
//        BonusEffect(BonusType);
//        return true;
//    }
//    return false;
//}
//

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
            color = Colors::MakeColor(0, 0, 255);
        }
        else if (Health < 3)
            Health++;
        break;
    }
    case EBonusTypes::ProjectileSpeed:
    {
        if (ProjComponent.GetSpeed() < 900.f)
        {
            ProjComponent.SetSpeed(ProjComponent.GetSpeed()*2.f);
            color = Colors::MakeColor(0, 160, 200);
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

//void Player::Damage(const uint8_t Damage, ProjectileComponent ProjComp)
//{
//    for (int i = 0; i < ProjComp.GetProjectiles().size(); i++)
//    {
//        if (ProjComp.GetProjectiles().at(i).Collision(Location, Size))
//        {
//            Health -= Damage;
//            ProjComp.GetProjectiles().erase(ProjComp.GetProjectiles().begin() + i);
//            SetLocation(500.0f, 600.0f );
//            //projectiles.at(i).SetLocation(Location.X, Location.Y);
//            if (Health <= 0)
//            {
//                isAlive = false;
//            }
//        }
//
//    }
//}
