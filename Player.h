#pragma once
#include "Utility.h"

class Player
{
private:
    Vector2D Location;
    Vector2D Size;
    uint32_t Color;
   // std::vector< Vector2D> projectilesLocation;
    //std::chrono::steady_clock::time_point startTime;
    //Vector2D ProjectileSize;

public:

    Player(Vector2D Location = { 500.0f, 600.0f }, Vector2D Size = { 50.f, 60.f },
        uint32_t Color = MakeColor(125, 0, 125))
        : Location(Location), Size(Size), Color(Color)
    {
    }

    ProjectileComponent ProjectileComponent;


    Vector2D GetLocation() { return Location; }

    Vector2D GetSize() { return Size; }

    void SetLocation(float X = 200.0f, float Y = 200.0f) { Location = { X, Y }; }

    void SetColor(uint32_t LColor) { Color = LColor; }

    uint32_t GetColor() { return Color; }

};