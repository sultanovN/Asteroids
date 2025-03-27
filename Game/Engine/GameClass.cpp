#include "GameClass.h"
#include "Engine.h"
#include "RandomNumber.h"

void Game::GameMenu()
{
    if (GameMode == Inter::Menu && StartContinue.isClicking({ get_cursor_x() * 1.f, get_cursor_y() * 1.f },
        is_mouse_button_pressed(0) || is_key_pressed(13)))
    {
        GameMode = Inter::Game;
    }
    else if (GameMode == Inter::PauseMenu && StartContinue.isClicking({ get_cursor_x() * 1.f, get_cursor_y() * 1.f },
        is_mouse_button_pressed(0) || is_key_pressed(13)))
    {
        GameMode = Inter::Game;
    }
    else if ((GameMode == Inter::Menu || GameMode == Inter::PauseMenu) && Exit.isClicking({ get_cursor_x() * 1.f, get_cursor_y() * 1.f },
        is_mouse_button_pressed(0) || is_key_pressed(13)))
    {
        schedule_quit_game();
    }
}

void Game::EnemySpawn()
{
    if (enemy.empty())
    {
        for (int i = 0; i < RandomNumberInRange(1, 4); i++)
        {
            enemy.emplace_back(Vector2D{ (i+1)*100.f, (i+1)*100.f }, Vector2D{40.f, 50.f}, 400.f, 2, Colors::Red, true);
        }
    }
}

bool lines[] = { 0,1,0,1 };

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
        if (player.PressedExit())
        {
            GameMode = Inter::PauseMenu;
            break;
        }
        player.Update(dt);
        EnemySpawn();
        for (int i = 0; i < enemy.size(); i++)
        {
            //en.LineMove(dt, lines, 4);
            enemy.at(i).Move(dt, lines, 4, SCREEN_WIDTH, player.GetLocation().X);
            enemy.at(i).Update(dt);
            player.ProjComponent.CollisionRect(enemy.at(i).Health, 1,
                enemy.at(i).isAlive, enemy.at(i).GetLocation(), enemy.at(i).GetSize());
            enemy.at(i).ProjComponent.Shoot(std::chrono::milliseconds(200));
            enemy.at(i).ProjComponent.CollisionRect(player.Health, 1,
                player.isAlive, player.GetLocation(), player.GetSize());
            if (!enemy.at(i).isAlive)
                enemy.erase(enemy.begin() + i);
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


void Game::gameDraw()
{
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

    //Background color
    DrawRectangle(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT, 0xFFFFFF);

    switch (GameMode)
    {
    case Inter::Game:
    {
        player.Draw();
        for (auto en : enemy)
        {
            en.Draw();
            en.ProjComponent.Draw();
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
    }
}