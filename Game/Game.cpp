#include <stdlib.h>
#include <memory.h>
#include "GameClass/GameClass.h"

Game game;

void initialize()
{
}
 
void act(float dt)
{
    game.gameLoop(dt);
}

void draw()
{
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
    game.gameDraw();
}

// free game data in this function
void finalize()
{
}

