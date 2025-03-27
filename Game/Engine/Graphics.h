#pragma once
#include <stdint.h>
#include <vector>
#include "Vector2D.h"
#include "../Engine/Engine.h"

//try uint32_t** buffer
//const void objectDraw(float X, float Y, float width, float height, uint32_t objectColor)
//{
//    for (int x = 0; x < SCREEN_WIDTH; x++)
//        for (int y = 0; y < SCREEN_HEIGHT; y++)
//        {
//            if ((x >= X && (x <= X + width)) && (y >= Y && (y <= Y + height)))
//            {
//                buffer[y][x] = objectColor;
//            }
//        }
//}
//
//const void objectDraw(std::vector<Vector2D>& objects, Vector2D Size, uint32_t objectColor)
//{
//    for (Vector2D& proj : objects)
//    {
//        for (int x = 0; x < SCREEN_WIDTH; x++)
//            for (int y = 0; y < SCREEN_HEIGHT; y++)
//            {
//                if ((x >= proj.X && (x <= proj.X + Size.X)) &&
//                    (y >= proj.Y && (y <= proj.Y + Size.Y)))
//                {
//                    buffer[y][x] = objectColor;
//                }
//            }
//    }
//}

//inline const void objectDraw(Vector2D Location, Vector2D Size, uint32_t objectColor)
//{
//    for (int x = 0; x < SCREEN_WIDTH; x++)
//        for (int y = 0; y < SCREEN_HEIGHT; y++)
//        {
//            if ((x >= Location.X && (x <= Location.X + Size.X)) && (y >= Location.Y && (y <= Location.Y + Size.Y)))
//            {
//                buffer[y][x] = objectColor;
//            }
//        }
//}