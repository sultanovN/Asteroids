#include "GameClass.h"
#include "../Utility.h"

void Game::GameMenu()
{
    if (GameMode == Inter::Menu && StartContinue.isClicking({ get_cursor_x() * 1.f, get_cursor_y() * 1.f },
        is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN)))
    {
        GameMode = Inter::Game;
    }
    else if (GameMode == Inter::PauseMenu && StartContinue.isClicking({ get_cursor_x() * 1.f, get_cursor_y() * 1.f },
        is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN)))
    {
        GameMode = Inter::Game;
    }
    else if (GameMode == Inter::Menu && Exit.isClicking({ get_cursor_x() * 1.f, get_cursor_y() * 1.f },
        is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN)))
    {
        schedule_quit_game();
    }
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
        player.Control(dt, GameMode);

        player.ProjComponent.ProjMove(dt, player.GetProjectileSpeed());

        for (int i = 0; i < enemy.size(); i++)
        {
            enemy.at(i).Move(dt, EnemyLines, 3, SCREEN_WIDTH, player.GetLocation().X);
            enemy.at(i).ProjComponent.Shoot({ enemy.at(i).GetLocation().X, enemy.at(i).GetLocation().Y + enemy.at(i).GetSize().Y + 3.f },
                enemy.at(i).GetSize().X, std::chrono::milliseconds(900));
            enemy.at(i).ProjComponent.ProjMove(dt, -300.f);

            player.ProjComponent.CollisionRect(enemy.at(i).Health, 1, enemy.at(i).isAlive,
                enemy.at(i).GetLocation(), enemy.at(i).GetSize());

            enemy.at(i).ProjComponent.CollisionRect(player.Health, 1, player.isAlive, player.GetLocation(),
                player.GetSize());

            //exception at less than 400f enemy proj speed 
            player.ProjComponent.CollisionProj(enemy.at(i).ProjComponent);
            //player.ProjectileComponent.CollisionProj(enemy.at(i).ProjComponent);

            if (!enemy.at(i).isAlive)
            {
                player.KillCount++;
                //bonus roll chance of appearing
                if (RandomNumberInRange(0, 1) == 1)
                {
                    //fix: other bonus if player already has it
                    EBonusTypes bonustype;
                    uint32_t bonusColor;
                    switch (RandomNumberInRange(0, 2))
                    {
                    case 0:
                    {
                        bonustype = EBonusTypes::Health;
                        bonusColor = Colors::MakeColor(255, 0, 0);
                        break;
                    }
                    case 1:
                    {
                        bonustype = EBonusTypes::ProjectileFreq;
                        bonusColor = Colors::MakeColor(0, 100, 200);
                        break;
                    }
                    case 2:
                    {
                        bonustype = EBonusTypes::ProjectileSpeed;
                        bonusColor = Colors::MakeColor(0, 200, 100);

                        break;
                    }
                    /*case 3:
                    {
                        bonustype = EBonusTypes::TwoProjectileShoot;
                        break;
                    }*/
                    }
                    bonus.emplace_back(enemy.at(i).GetLocation(), bonustype, bonusColor);
                }

                enemy.erase(enemy.begin() + i);
                //enemy[i].SetColor(MakeColor(0, 0, 0));
            }
        }

        for (int i = 0; i < bonus.size(); i++)
        {
            bonus.at(i).Move(dt);
            if (player.BonusCollision(bonus.at(i).GetLocation(), bonus.at(i).GetSize(), bonus.at(i).GetBonusType()))
                bonus.erase(bonus.begin() + i);
        }
        //levelChange();
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
    /*case Inter::LevelSelect:
    {
        ButtonSelect();

        switch (button)
        {
        case Button::Start:
            level1();
            break;
        case Button::Second:
            level2();
            break;
        default:
            level2();
            break;
        }
    }*/
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
    for (int x = 0; x < SCREEN_WIDTH; x++)
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            buffer[y][x] = Colors::MakeColor(255, 255, 230);
        }

    switch (GameMode)
    {
    case Inter::Game:
    {
        objectDraw(player.GetLocation().X, player.GetLocation().Y, player.GetSize().X,
            player.GetSize().Y, player.GetColor());
        for (auto proj : player.ProjComponent.GetProjectilesLocation())
        {
            proj.Draw(SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        for (int i = 0; i < enemy.size(); i++)
        {
            objectDraw(enemy.at(i).GetLocation().X, enemy.at(i).GetLocation().Y, enemy.at(i).GetSize().X,
                enemy.at(i).GetSize().Y, enemy.at(i).GetColor());
            enemy.at(i).ProjComponent.ProjDraw();

        }

        //objectDraw(, { 40.f, 50.f }, Colors::Red);

        for (int i = 0; i < bonus.size(); i++)
        {
            objectDraw(bonus.at(i).GetLocation().X, bonus.at(i).GetLocation().Y, bonus.at(i).GetSize().X,
                bonus.at(i).GetSize().Y, bonus.at(i).GetColor());
        }

        for (int i = 0; i < player.Health; i++)
        {
            objectDraw(50.f * (i + 1) + (30.f * i), 700.f, 30.f,
                30.f, MakeColor(255, 0, 0));
        }
        break;
    }
    case Inter::Menu:
    {
        objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, Colors::Red);
        //objectDraw(StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));
        objectDraw(StartGameLocation.X, StartGameLocation.Y + (StartGameSize.Y + 50.f) * 2, StartGameSize.X, StartGameSize.Y, Colors::Red);
        break;
    }
    case Inter::PauseMenu:
    {
        objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, Colors::Red);
        objectDraw(StartGameLocation.X, StartGameLocation.Y + (StartGameSize.Y + 50.f) * 2, StartGameSize.X, StartGameSize.Y, Colors::Red);
        break;
    }
    }
}