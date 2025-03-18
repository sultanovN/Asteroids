#include <stdlib.h>
#include <memory.h>

#include "Components/GInterface.h"
//Goals:
// 
// enemy smooth spawn, moving forward +-
// text render
// health visual
// levels +-
//   
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
// mouse press release function
// 
// ignoring mouse when using keyboard(when mouse is above button, keyboard control issue, 
// save mouse location when opening menu or using keyboard, if it stays in place ignore, can be included to the game loop too)
// 
// engine data not visible to files when changing files structure
// 
// add static constexpr(one variable for all class instances, doesnt get copied for each class)
// 
// randomizer for enemies
// 

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

// initialize game data in this function
void initialize()
{
    player = Player{ { 500.0f, 600.0f }, { 50.f, 60.f }, 3, MakeColor(125, 0, 125),
false, 500.f, std::chrono::milliseconds(300) };
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
    gameLoop(dt);
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
    gameDraw();
}

// free game data in this function
void finalize()
{
}

