#pragma once
#include <vector>
#include "../Player/Player.h"
#include "../Enemies/Enemy.h"
//#include "../Enemies/LaserEnemy.h"
#include "../Components/Bonus.h"
#include "../UI/UserInterface.h"
#include "../Engine/Surface.h"

static class Game
{
    Player player = Player{ { 500.0f, 600.0f }, { 50.f, 60.f }, 500.f, Colors::MakeColor(125, 0, 125),
    3, std::chrono::milliseconds(300) };
    std::vector<Enemy> enemy;
    std::vector<Bonus> bonuses;
    //Start game and continue game
    //Button StartContinue{ { ScreenCenter.X - (600.f / 2.f), ScreenCenter.Y - (80.f / 2.f) - 100.f }, {600.f, 80.f} };

    Button StartContinue{ { 200, 200 }, {300.f, 80.f}, 0 };
    Button Exit{ {StartContinue.GetLocation().X, StartContinue.GetLocation().Y + StartContinue.GetSize().Y * 2}, 
        StartContinue.GetSize(), 1};

    enum class Inter
    {
        Menu,
        Game,
        PauseMenu,
        GameOver,
        LevelSelect,
        GameCompleted
    };
    //C:/Projects/Asteroids/Game
    Surface TestSprite = Surface( "C:/Projects/Asteroids/Game/Images/Backgrounds/blue.bmp" );
    Surface BackGroundSprite = Surface( "C:/Projects/Asteroids/Game/Images/Backgrounds/blue(2).bmp" );

public:
    Game();
    

    void gameLoop(float dt);
    void gameDraw();
    void GameMenu();
    Vector2D ScreenCenter{ SCREEN_WIDTH / 2.f , SCREEN_HEIGHT / 2.f };
    Inter GameMode = Inter::Menu;
    void EnemySpawn();
    void BonusSpawn(Vector2D Location);
    void ReSpawn();
};