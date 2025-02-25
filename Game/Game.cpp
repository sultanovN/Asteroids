#include "Engine/Engine.h"
#include <stdlib.h>
#include <memory.h>

#include "Player.h"
#include "Enemy.h"
#include "LaserEnemy.h"

//
// enemy smooth spawn, moving forward +-
// text render
// health visual
// levels +-
//   
// enums
// std::map
// std::set
// multithreads
// 
// player changes color when hit 
// 
// interface with enums+
// 
// different types of enemies
// 
// enemy that follows the player
// 
// laser attack, follows player, stops for attack
// 
// button hover function+
// 
// drawing objects in one(entity)
// 
// highest score in the menu
// 
// storing score in the file
// 
// pickable bonuses, higher damage more projectiles etc. +-
// 
// "freetype" text, font library
// 






//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

 

Vector2D StartGameSize{ 600.f, 80.f };
Vector2D StartGameLocation{ SCREEN_WIDTH/2.f - StartGameSize.X/2.f, SCREEN_HEIGHT/2.f - StartGameSize.Y / 2.f - 100.f };



void ButtonSelect()
{
    if ((RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
        StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y)) || is_key_pressed(VK_UP))
    {
        button = Button::Start;
    }


    if (RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
        StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y) || is_key_pressed(VK_DOWN))
    {
        button = Button::Second;
    }

    if (RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
        StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y * 2 + 50.f + 50.f, StartGameSize.X, StartGameSize.Y) || is_key_pressed(VK_DOWN))
    {
        button = Button::Exit;
    }
}

void StartGameInterface()
{
    if (button == Button::Start && ((is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN))))
    {
        initialize();
        GameMode = Inter::Game;
    }
    else if (button == Button::Exit && ((is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN))))
    {
        schedule_quit_game();
    }
    else if (button == Button::Second && ((is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN))))
    {
        GameMode = Inter::LevelSelect;

    }
}

Player player;
std::vector<Enemy> enemy;
//std::vector<ProjectileComponent> Rocks;
//Enemy enemy[3];
bool EnemyLines[3];

std::vector<Bonus>bonus;

int8_t level = 1;

void level1()
{
    enemy = { {{30.0f, -100.0f}}, {{400.0f, -100.0f}}, {{1000.0f, -100.0f}}};
}

void level2()
{
    enemy = { {{30.0f, -100.0f}}, {{400.0f, -200.0f}}, {{1000.0f, -300.0f}} };
}

void level3()
{
    enemy = { {{30.0f, -100.0f}, 2, MakeColor(0, 255, 0)}, LaserEnemy{ player.GetLocation().X, {900.0f, -400.0f}, 2, MakeColor(0, 0, 210), {60.f, 40.f},
        MakeColor(0, 0, 200), 100.f, false} };
    /*LaserEnemy Laser = { player.GetLocation().X, {900.0f, -400.0f}, 2, MakeColor(0, 0, 210), {60.f, 40.f},
        MakeColor(0, 0, 200), 100.f, false};{900.0f, -400.0f}, 2, MakeColor(0, 0, 210), {60.f, 40.f},
        MakeColor(0, 0, 200), 100.f, false, player.GetLocation().X}*/ /*{{100.0f, -200.0f}, 1, MakeColor(0, 0, 255)},
        {{500.0f, -300.0f}}, */
}

//level1
void levelChange()
{
    if (enemy.empty())
    {
        for (int j = 0; j < 3; j++)
        {
            EnemyLines[j] = true;
        }
        level++;

        switch (level)
        {
        case 1:
            level1();
            break;
        case 2:
            level2();
            break;
        case 3:
            level3();
            break;
        default:
            level2();
            break;
        }
    }

}



// initialize game data in this function
void initialize()
{
    player = Player{};
    enemy.reserve(6);
    level1();
    //EnemySpawn(enemy, EnemyLines, 3);

    for (int j = 0; j < 3; j++)
    {
        EnemyLines[j] = true;
    }
}
 
// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    switch (GameMode)
    {
    case Inter::Menu:
    {
        StartGameInterface();
        ButtonSelect();
        break;
    }

    case Inter::Game:
    {
        player.Control(dt);

        player.ProjectileComponent.ProjMove(dt, player.GetProjectileSpeed());

        for (int i = 0; i < enemy.size(); i++)
        {
            enemy.at(i).Move(dt, EnemyLines, 3, SCREEN_WIDTH, player.GetLocation().X);
            enemy.at(i).ProjComponent.Shoot({ enemy.at(i).GetLocation().X, enemy.at(i).GetLocation().Y + enemy.at(i).GetSize().Y + 3.f },
                enemy.at(i).GetSize().X, std::chrono::milliseconds(900));
            enemy.at(i).ProjComponent.ProjMove(dt, -300.f);

            player.ProjectileComponent.CollisionRect(enemy.at(i).Health, 1, enemy.at(i).isAlive,
                enemy.at(i).GetLocation(), enemy.at(i).GetSize());

            enemy.at(i).ProjComponent.CollisionRect(player.Health, 1, player.isAlive, player.GetLocation(),
                player.GetSize());

            //exception at less than 400f enemy proj speed 
            player.ProjectileComponent.CollisionProj(enemy.at(i).ProjComponent);
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
                        bonusColor = MakeColor(255, 0, 0);
                        break;
                    }
                    case 1:
                    {
                        bonustype = EBonusTypes::ProjectileFreq;
                        bonusColor = MakeColor(0, 100, 200);
                        break;
                    }
                    case 2:
                    {
                        bonustype = EBonusTypes::ProjectileSpeed;
                        bonusColor = MakeColor(0, 200, 100);

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

        levelChange();
        break;
    }
    case Inter::PauseMenu:
    {
        if (button == Button::Start && ((is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN))))
        {
            GameMode = Inter::Game;
        }
        else if (button == Button::Exit && ((is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN))))
        {
            schedule_quit_game();
        }
        ButtonSelect();

        break;
    }
    case Inter::GameOver:
    {

        break;
    }
    case Inter::LevelSelect:
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
    }
    case Inter::GameCompleted:
    {

        break;
    }
    default:
        break;
    }

    
}





// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

    //Background color
    for (int x = 0; x < SCREEN_WIDTH; x++)
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            buffer[y][x] = MakeColor(255, 255, 230);
        }

    switch (GameMode)
    {
    case Inter::Game:
    {
        objectDraw(player.GetLocation().X, player.GetLocation().Y, player.GetSize().X,
            player.GetSize().Y, player.GetColor());
        player.ProjectileComponent.ProjDraw();


        for (int i = 0; i < enemy.size(); i++)
        {
            objectDraw(enemy.at(i).GetLocation().X, enemy.at(i).GetLocation().Y, enemy.at(i).GetSize().X,
                enemy.at(i).GetSize().Y, enemy.at(i).GetColor());
            enemy.at(i).ProjComponent.ProjDraw();

        }
        for (int i = 0; i < bonus.size(); i++)
        {
            objectDraw(bonus.at(i).GetLocation().X, bonus.at(i).GetLocation().Y, bonus.at(i).GetSize().X,
                bonus.at(i).GetSize().Y, bonus.at(i).GetColor());
        }

        for (int i = 0; i < player.Health; i++)
        {
            objectDraw(50.f*(i+1) + (30.f * i), 700.f, 30.f,
                30.f, MakeColor(255, 0, 0));
        }
        break;
    }
    case Inter::Menu:
    {
        if (button == Button::Start)
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }

        if (button == Button::Second)
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }

        if (button == Button::Exit)
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + (StartGameSize.Y + 50.f) * 2, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + (StartGameSize.Y  + 50.f) * 2, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }
        break;
    }
    case Inter::PauseMenu:
    {
        if (button == Button::Start)
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }

        if (button == Button::Exit)
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + (StartGameSize.Y + 50.f) * 2, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + (StartGameSize.Y + 50.f) * 2, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }
        break;
    }
    case Inter::LevelSelect:
    {
        if (button == Button::Start)
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }

        if (button == Button::Second)
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }

        
    }
    }

    /*if (GameStarted)
    {
        
    }
    else
    {
        

    }*/
}

// free game data in this function
void finalize()
{
}

