#pragma once
#include "../Entity/Entity.h"

//create button order function
class Button: public Entity
{
    uint8_t buttonOrderNum;
public:
    Button(Vector2D Location, Vector2D Size, uint8_t buttonOrderNum, uint32_t Color = 0xCD0000)
        : Entity(Location, Size, Color), buttonOrderNum(buttonOrderNum)
    {
    }

    bool isHovering(Vector2D mouseLoc)
    {
        if (RectRectCollision(Location, Size, mouseLoc, { 0.f, 0.f }))
        {
            return true;
        }
        return false;
    }

    //bSelect == (is_mouse_button_pressed(0) || is_key_pressed(VK_RETURN), mouse location: get_cursor_x(), get_cursor_y()
    bool isClicking(Vector2D mouseLoc, bool bSelect)
    {
        if (isHovering(mouseLoc) && bSelect)
        {
            return true;
        }
        return false;
    }
};
//enum class Button
//{
//    Start,
//    Second,
//    Exit //level select
//};


//Vector2D StartGameSize{ 600.f, 80.f };
//Vector2D StartGameLocation{ SCREEN_WIDTH / 2.f - StartGameSize.X / 2.f, 
//SCREEN_HEIGHT / 2.f - StartGameSize.Y / 2.f - 100.f };



//void ButtonSelect()
//{
//    if ((RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
//        StartGameLocation.X, StartGameLocation.Y, StartGameSize.X, StartGameSize.Y)) ||
//        is_key_pressed(VK_UP))
//    {
//        button = Button::Start;
//    }
//
//    if (RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
//        StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y + 50.f,
//        StartGameSize.X, StartGameSize.Y) || is_key_pressed(VK_DOWN))
//    {
//        button = Button::Second;
//    }
//
//    if (RectRectCollision(get_cursor_x(), get_cursor_y(), 0, 0,
//        StartGameLocation.X, StartGameLocation.Y + StartGameSize.Y * 2 + 50.f + 50.f,
//        StartGameSize.X, StartGameSize.Y) || is_key_pressed(VK_DOWN))
//    {
//        button = Button::Exit;
//    }
//}

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