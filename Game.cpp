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
Enemy enemy[3];
bool EnemyLines[3] = { 1, 1, 1 };

void EnemySpawn(Enemy enemy[], int enemyNum, bool lines[], int linesNum)
{
    for (int i = 0; i < enemyNum; i++)
    {
        for (int j = 0; j < linesNum; j++)
        {
            if (lines[j])
            {
                enemy[i].SetLocation(200.0f * (i + 1), 10.0f * (j+1));
                lines[j] = false;
            }
        }
    }
}

// initialize game data in this function
void initialize()
{
    EnemySpawn(enemy, 3, EnemyLines, 3);

}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
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



    for (int i = 0; i < 3; i++)
    {
        enemy[i].Move(dt, SCREEN_WIDTH);
        enemy[i].ProjComponent.Shoot(enemy[i].GetLocation(), enemy[i].GetSize().X);
        enemy[i].ProjComponent.ProjMove(dt);
        player.ProjectileComponent.CollisionRect(enemy[i].Health, 1, enemy[i].GetLocation(), enemy[i].GetSize());
        enemy[i].ProjComponent.CollisionRect(player.Health, 1, player.GetLocation(), player.GetSize());

        if (enemy[i].Health == 0)
        {
            enemy[i].SetColor(MakeColor(0, 0, 0));
        }
    }
    if (player.Health == 0)
    {
        player.SetColor(MakeColor(0, 0, 0));
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
            /*else 
            {
                buffer[y][x] = MakeColor(255, 255, 255);
            }*/
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


    for (int i = 0; i < 3; i++)
    {
        objectDraw(enemy[i].GetLocation().X, enemy[i].GetLocation().Y, enemy[i].GetSize().X,
            enemy[i].GetSize().Y, enemy[i].GetColor());
        enemy[i].ProjComponent.ProjDraw();

    }
    
}

// free game data in this function
void finalize()
{
}

