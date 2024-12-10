#include "Engine.h"
#include <stdlib.h>
#include <memory.h>

#include "Player.h"
#include "Enemy.h"


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



Player player;
std::vector<Enemy> enemy;

//std::vector<ProjectileComponent> Rocks;
//Enemy enemy[3];
bool EnemyLines[3] = { 1, 1, 1 };
//
//void EnemySpawn(std::vector<Enemy> enemy, int enemyNum, bool lines[], int linesNum)
//{
//    for (int i = 0; i < enemy.size(); i++)
//    {
//        for (int j = 0; j < linesNum; j++)
//        {
//            if (lines[j])
//            {
//                enemy.at(i).SetLocation(200.0f * (i + 1), 10.0f * (j + 1));
//                lines[j] = false;
//            }
//        }
//    }
//}

// initialize game data in this function
void initialize()
{
    player = Player{};
    enemy = { {{100.0f, 100.0f} }, {{200.0f, 200.0f}}, {{400.0f, 400.0f}}
};
    //EnemySpawn(enemy, 3, EnemyLines, 3);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    if (!player.GetIsAlive())
    {
        while (1)
        {
            if (is_key_pressed(VK_SPACE))
            {
                player.isAlive = true;
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

    if (is_key_pressed(VK_RIGHT) && (player.GetLocation().X + player.GetSize().X < SCREEN_WIDTH))
    {
        player.SetLocation(player.GetLocation().X + 400.f * dt, player.GetLocation().Y);
    }

    if (is_key_pressed(VK_LEFT) && (player.GetLocation().X > 0))
    {
        player.SetLocation(player.GetLocation().X - 400.f * dt, player.GetLocation().Y);
    }

    if (is_key_pressed(VK_SPACE))
    {
        player.ProjectileComponent.Shoot(player.GetLocation(), player.GetSize().X);
    }

    player.ProjectileComponent.ProjMove(dt);



    for (int i = 0; i < enemy.size(); i++)
    {
        enemy.at(i).Move(dt, SCREEN_WIDTH);
        enemy.at(i).ProjComponent.Shoot(enemy.at(i).GetLocation(), enemy.at(i).GetSize().X);
        enemy.at(i).ProjComponent.ProjMove(dt);
        player.ProjectileComponent.CollisionRect(enemy.at(i).Health, 1, enemy.at(i).isAlive,
            enemy.at(i).GetLocation(), enemy.at(i).GetSize());
        enemy.at(i).ProjComponent.CollisionRect(player.Health, 1, player.isAlive, player.GetLocation(), player.GetSize());

        if (!enemy.at(i).isAlive)
        {
            enemy.erase(enemy.begin() + i);
            //enemy[i].SetColor(MakeColor(0, 0, 0));
        }
    }
}


void objectDraw(float X, float Y, float width, float height, uint32_t objectColor)
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
    /*for (int x = 0; x < SCREEN_WIDTH; x++)
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            buffer[y][x] = MakeColor(200, 200, 200);
        }*/

    objectDraw(player.GetLocation().X, player.GetLocation().Y, player.GetSize().X,
        player.GetSize().Y, player.GetColor());
    player.ProjectileComponent.ProjDraw();


    for (int i = 0; i < enemy.size(); i++)
    {
        objectDraw(enemy.at(i).GetLocation().X, enemy.at(i).GetLocation().Y, enemy.at(i).GetSize().X,
            enemy.at(i).GetSize().Y, enemy.at(i).GetColor());
        enemy.at(i).ProjComponent.ProjDraw();

    }
    
}

// free game data in this function
void finalize()
{
}

