#include "Engine.h"
#include <stdlib.h>
#include <memory.h>

#include "Player.h"
#include "Enemy.h"


//
// enemy smooth spawn, moving forward +-
// text render
// health visual
// levels +-
// 
// enums
// std::map
// 
// player changes color when hit
// 
// interface with enums
// 
// different types of enemies
// 
// enemy that follows the player
// 
// laser attack, follows player, stops for attack
// 
// button hover function
// 



//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()



Vector2D StartGameSize{ 600.f, 150.f };
Vector2D StartGameLocation{ SCREEN_WIDTH/2.f - StartGameSize.X/2.f, SCREEN_HEIGHT/2.f - StartGameSize.Y / 2.f - 100.f };


void StartGameInterface()
{
    if (is_mouse_button_pressed(0) && RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0, 
        StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y))
    {
        initialize();
        GameMode = Inter::Game;
    }
    else if (is_mouse_button_pressed(0) && RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
        StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y))
    {
        schedule_quit_game();
    }
}

Player player;
std::vector<Enemy> enemy;
//std::vector<ProjectileComponent> Rocks;
//Enemy enemy[3];
bool EnemyLines[3];



int8_t level = 1;

void level1()
{
    enemy = { {{30.0f, -100.0f}}, {{400.0f, -200.0f}}, {{1000.0f, -300.0f}}};
}

void level2()
{
    enemy = { {{30.0f, -100.0f}, 2, MakeColor(0, 255, 0)}, {{100.0f, -200.0f}, 1, MakeColor(0, 0, 255)}, {{500.0f, -300.0f}}, {{900.0f, -400.0f}}};
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
        StartGameInterface();
        break;
    case Inter::Game:
        if (GameMode == Inter::Game)
        {
            player.Control(dt);

            player.ProjectileComponent.ProjMove(dt);

            for (int i = 0; i < enemy.size(); i++)
            {
                enemy.at(i).Move(dt, EnemyLines, 3, SCREEN_WIDTH);
                enemy.at(i).ProjComponent.Shoot({ enemy.at(i).GetLocation().X, enemy.at(i).GetLocation().Y + enemy.at(i).GetSize().Y + 3.f }, enemy.at(i).GetSize().X, std::chrono::milliseconds(500));
                enemy.at(i).ProjComponent.ProjMove(dt);
                player.ProjectileComponent.CollisionRect(enemy.at(i).Health, 1, enemy.at(i).isAlive,
                    enemy.at(i).GetLocation(), enemy.at(i).GetSize());

                enemy.at(i).ProjComponent.CollisionRect(player.Health, 1, player.isAlive, player.GetLocation(), player.GetSize());

                //player.ProjectileComponent.CollisionProj(enemy.at(i).ProjComponent);

                if (!enemy.at(i).isAlive)
                {
                    enemy.erase(enemy.begin() + i);
                    //enemy[i].SetColor(MakeColor(0, 0, 0));
                }

            }

            levelChange();
        }
        break;
    case Inter::PauseMenu:
        if (is_mouse_button_pressed(0) && RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
            StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y))
        {
            GameMode = Inter::Game;
        }
        else if (is_mouse_button_pressed(0) && RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
            StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y))
        {
            schedule_quit_game();
        }
        break;
    default:
        break;
    }

    
}


const void objectDraw(float X, float Y, float width, float height, uint32_t objectColor)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            if ((x >= X && (x <= X + width)) && (y >= Y && (y <= Y + height)))
            {
                buffer[y][x] = objectColor;
            }
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
        break;
    }
    case Inter::Menu:
    {
        if (RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
            StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y))
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }

        if (RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
            StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y))
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }
        break;
    }
    case Inter::PauseMenu:
    {
        if (RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
            StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y))
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }

        if (RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
            StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y))
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y, MakeColor(200, 0, 0));
        }
        else
        {
            objectDraw(StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y, MakeColor(255, 0, 0));

        }
        break;
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

