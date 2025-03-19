#pragma once
#include "../Player/Player.h"
#include "UserInterface.h"
#include "../Enemies/Enemy.h"
#include "../Enemies/LaserEnemy.h"
#include <vector>

Player player{ { 500.0f, 600.0f } , { 50.f, 60.f } , 3 , MakeColor(125, 0, 125) ,
false , 500.f , std::chrono::milliseconds(300) };
std::vector<Enemy> enemy;
//std::vector<ProjectileComponent> Rocks;
//Enemy enemy[3];
bool EnemyLines[3];

std::vector<Bonus>bonus;

int8_t level = 1;

void level1()
{
    enemy = { {{30.0f, -100.0f}}, {{400.0f, -100.0f}}, {{1000.0f, -100.0f}} };
}

void level2()
{
    enemy = { {{30.0f, -100.0f}}, {{400.0f, -200.0f}}, {{1000.0f, -300.0f}} };
}

void level3()
{
    enemy = { {{30.0f, -100.0f}}, LaserEnemy{ player.GetLocation().X, {900.0f, -400.0f}, 2, MakeColor(0, 0, 210), {60.f, 40.f},
        MakeColor(0, 0, 200), 100.f, false} };
    /*LaserEnemy Laser = { player.GetLocation().X, {900.0f, -400.0f}, 2, MakeColor(0, 0, 210), {60.f, 40.f},
        MakeColor(0, 0, 200), 100.f, false};{900.0f, -400.0f}, 2, MakeColor(0, 0, 210), {60.f, 40.f},
        MakeColor(0, 0, 200), 100.f, false, player.GetLocation().X}*/ /*{{100.0f, -200.0f}, 1, MakeColor(0, 0, 255)},
        {{500.0f, -300.0f}}, */
}



Inter GameMode = Inter::Menu;

class Game
{
    Player player = Player{ { 500.0f, 600.0f }, { 50.f, 60.f }, 3, MakeColor(125, 0, 125),
    false, 500.f, std::chrono::milliseconds(300) };

    //Start game and continue game
    Button StartContinue{ { ScreenCenter.X - 600.f / 2.f, ScreenCenter.Y - 80.f / 2.f - 100.f }, {600.f, 80.f} };
    Button Exit{ StartContinue.GetLocation() + 50.f, StartContinue.GetSize()};
public:
    Game()
    {
        player = Player{ { 500.0f, 600.0f }, { 50.f, 60.f }, 3, MakeColor(125, 0, 125),
    false, 500.f, std::chrono::milliseconds(300) };
        enemy.reserve(6);
        level1();

        for (int j = 0; j < 3; j++)
        {
            EnemyLines[j] = true;
        }
    }

    void gameLoop(float dt);
    void gameDraw();
    void GameMenu();
    Vector2D ScreenCenter{ SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f };

};


//void StartGameInterface()
//{
//    if (button == Button::Start && ((is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN))))
//    {
//        initialize();
//        GameMode = Inter::Game;
//    }
//    else if (button == Button::Exit && ((is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN))))
//    {
//        schedule_quit_game();
//    }
//    else if (button == Button::Second && ((is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN))))
//    {
//        GameMode = Inter::LevelSelect;
//
//    }
//}



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


