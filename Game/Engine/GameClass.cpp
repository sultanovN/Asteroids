#include "GameClass.h"
#include "Engine.h"
#include "RandomNumber.h"

int lines[] = { 0,0,0,0 };

ProjectileComponent EnemyProjComponent{ {20.f, 20.f}, {10.f, 25.f}, -400.f, Colors::Red};



void Game::GameMenu()
{
    if ((GameMode == Inter::Menu || GameMode == Inter::GameOver) && StartContinue.isClicking({ get_cursor_x() * 1.f, get_cursor_y() * 1.f },
        is_mouse_button_pressed(0) || is_key_pressed(13)))
    {
        ReSpawn();
        GameMode = Inter::Game;
    }
    else if (GameMode == Inter::PauseMenu && StartContinue.isClicking({ get_cursor_x() * 1.f, get_cursor_y() * 1.f },
        is_mouse_button_pressed(0) || is_key_pressed(13)))
    {
        GameMode = Inter::Game;
    }
    else if ((GameMode == Inter::Menu || GameMode == Inter::PauseMenu || GameMode == Inter::GameOver) && Exit.isClicking({ get_cursor_x() * 1.f, get_cursor_y() * 1.f },
        is_mouse_button_pressed(0) || is_key_pressed(13)))
    {
        schedule_quit_game();
    }
}

void Game::EnemySpawn()
{
    if (enemy.empty())
    {
        for (int &line : lines)
        {
            line = 0;
        }
        for (int i = 0; i < RandomNumberInRange(6, 16); i++)
        {
            //enemy.emplace_back(Vector2D{ (i+1)*100.f, (i+1)*100.f }, Vector2D{40.f, 50.f}, 400.f, 2, Colors::Red, true);
            enemy.emplace_back(Vector2D{ (i+1)*100.f, -100.f }, Vector2D{40.f, 50.f}, 400.f, 2, Colors::Red, true);
        }
    }
}

void Game::BonusSpawn(Vector2D Location)
{
    const int Roll = RandomNumberInRange(0, 20);
    EBonusTypes BonusType;
    switch (Roll)
    {
    case 0:
    {
        BonusType = EBonusTypes::Health;
        break;
    }
    case 1:
    {
        BonusType = EBonusTypes::ProjectileFreq;
        break;
    }
    case 2:
    {
        BonusType = EBonusTypes::ProjectileSpeed;
        break;
    }
    default:
        return;
    }
    bonuses.emplace_back(Location, BonusType);
}

void Game::ReSpawn()
{
    enemy.clear();
    EnemyProjComponent.GetProjectiles().clear();
    player = Player{ { 500.0f, 600.0f }, { 50.f, 60.f }, 500.f, Colors::MakeColor(125, 0, 125),
    3, std::chrono::milliseconds(300) };
}


void Game::gameLoop(float dt)
{
    switch (GameMode)
    {
    case Inter::Menu:
    {
        GameMenu();
        break;
    }
    case Inter::Game:
    {
        if (!player.GetIsAlive())
        {
            GameMode = Inter::GameOver;
            break;
        }

        if (player.PressedExit())
        {
            GameMode = Inter::PauseMenu;
            break;
        }
        player.Update(dt);

        for (int i = 0; i < bonuses.size(); i++)
        {
            bonuses.at(i).Update(dt);
            if (bonuses.at(i).Collision(player))
            {
                player.BonusEffect(bonuses.at(i).GetBonusType());
                bonuses.erase(bonuses.begin() + i);
            }
        }

        EnemySpawn();
        EnemyProjComponent.Shoot(std::chrono::milliseconds(RandomNumberInRange(500, 800)),
            enemy.at(RandomNumberInRange(0, enemy.size() - 1)).GetLocation());
        //EnemyProjComponent.Move({ Location.X + Size.X / 2 - 5.f, Location.Y - 20.f });
        EnemyProjComponent.Update(dt);
        EnemyProjComponent.CollisionRect(player.Health, 1, player.isAlive, player.GetLocation(), player.GetSize());

        player.ProjComponent.CollisionRect(EnemyProjComponent.GetProjectiles());
        for (int i = 0; i < enemy.size(); i++)
        {
            //en.LineMove(dt, lines, 4);
            enemy.at(i).Move(dt, lines, 4, SCREEN_WIDTH, player.GetLocation().X);
            enemy.at(i).Update(dt);

            player.ProjComponent.CollisionRect(enemy.at(i).Health, 1,
                enemy.at(i).isAlive, enemy.at(i).GetLocation(), enemy.at(i).GetSize());
            int timeShoot;

            // change enemy proj component
            // right now projectiles dissapear if enemy gets destroyed
            // external one proj component for all enemies
            // proj comp randomly selects existing enemy from array and shoots from its location
            // done?
            //enemy.at(i).ProjComponent.Shoot(std::chrono::milliseconds(RandomNumberInRange(30, 80) * 100));

            //enemy.at(i).ProjComponent.CollisionRect(player.Health, 1,player.isAlive, player.GetLocation(), player.GetSize());

            //enemy.at(i).ProjComponent.CollisionProj(player.ProjComponent);

            if (!enemy.at(i).isAlive)
            {
                BonusSpawn(enemy.at(i).GetLocation());
                enemy.erase(enemy.begin() + i);
            }
        }
        

        break;
    }
    case Inter::PauseMenu:
    {
        GameMenu();
        break;
    }
    case Inter::GameOver:
    {
        GameMenu();
        break;
    }
    case Inter::GameCompleted:
    {
        break;
    }
    default:
        break;
    }
}

Entity Background{ Vector2D(0,0), Vector2D(SCREEN_WIDTH, SCREEN_HEIGHT) , Colors::White };

void Game::gameDraw()
{
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

    //Background color
    Background.Draw();
    //DrawRectangle(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT, 0xFFFFFF);

    switch (GameMode)
    {
    case Inter::Game:
    {
        player.Draw();
        for (auto en : enemy)
        {
            en.Draw();
        }
        EnemyProjComponent.Draw();

        for (auto bonus : bonuses)
        {
            bonus.Draw();
        }

        for (int i = 1; i < player.Health + 1; i++)
        {
            DrawRectangle(50.f * i, 700.f, 20.f, 20.f, Colors::Red);
        }
        break;
    }
    case Inter::Menu:
    {
        StartContinue.Draw();
        Exit.Draw();
        break;
    }
    case Inter::PauseMenu:
    {
        StartContinue.Draw();
        Exit.Draw();
        break;
    }
    case Inter::GameOver:
    {
        player.Draw();
        for (auto en : enemy)
        {
            en.Draw();
        }
        EnemyProjComponent.Draw();

        for (auto bonus : bonuses)
        {
            bonus.Draw();
        }

        for (int i = 1; i < player.Health + 1; i++)
        {
            DrawRectangle(50.f * i, 700.f, 20.f, 20.f, Colors::Red);
        }
        StartContinue.Draw();
        Exit.Draw();
        break;
    }
    }
}