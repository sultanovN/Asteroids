#include "Engine/Engine.h"
#include <stdlib.h>
#include <memory.h>

#include "Utility.h"



Vector2D StartGameSize{ 600.f, 80.f };
Vector2D StartGameLocation{ SCREEN_WIDTH/2.f - StartGameSize.X/2.f, SCREEN_HEIGHT/2.f - StartGameSize.Y / 2.f - 100.f };


//void ButtonSelect()
//{
//    if ((RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
//        StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y)) || is_key_pressed(VK_UP))
//    {
//        button = Button::Start;
//    }
//
//
//    if (RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
//        StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f, StartGameSize.X, StartGameSize.Y) || is_key_pressed(VK_DOWN))
//    {
//        button = Button::Second;
//    }
//
//    if (RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
//        StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y * 2 + 50.f + 50.f, StartGameSize.X, StartGameSize.Y) || is_key_pressed(VK_DOWN))
//    {
//        button = Button::Exit;
//    }
//}
//
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

int gamespeed = 1;
const int rows = 20;
const int cols = 20;
bool mat[rows][cols];
int cellSize = 20;
int borderSize = 3;

// initialize game data in this function
void initialize()
{
}

int countNeighbours(int x, int y)
{

}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            if (mat[x][y])
            {
                //if(mat[x-1][y-1])
            }
            else
            {
                if ((RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
                    (x * cellSize) + ((x + 1) * borderSize),
                    (y * cellSize) + ((y + 1) * borderSize), cellSize,
                    cellSize) && is_mouse_button_pressed(0)))
                {
                    mat[x][y] = 1;
                }
            }
        }
    }
    
}



void createEmptyGrid()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = 0;
        }
    }
}

void drawGrid()
{
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            if (mat[x][y] == 1)
            {
                objectDraw((x * cellSize) + ((x+1) * borderSize), 
                    (y * cellSize) + ((y + 1) * borderSize), cellSize,
                    cellSize, MakeColor(255, 0, 0));
            }
            else if (mat[x][y] == 0)
            {
                objectDraw((x * cellSize) + ((x + 1) * borderSize),
                    (y * cellSize) + ((y + 1) * borderSize), cellSize,
                    cellSize, MakeColor(255, 255, 255));
            }
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
            buffer[y][x] = MakeColor(0, 0, 0);
        }

    drawGrid();

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

