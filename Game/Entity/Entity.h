#pragma once
#include "stdint.h"
#include "../Engine/Vector2D.h"
#include "../Engine/Color.h"

void DrawRectangle(float LocationX, float LocationY, float SizeX, float SizeY, uint32_t Color);

class Entity
{
protected:
    Vector2D Location;
    Vector2D Size;
    float Speed;
    uint32_t Color;

public:
    Entity(Vector2D Location, Vector2D Size, float Speed, uint32_t Color);

    Vector2D GetLocation() const { return Location; }

    Vector2D GetSize() const { return Size; }

    uint32_t& GetColor() { return Color; }

    float GetSpeed()const { return Speed; }

    virtual void SetLocation(const float X, const float Y) { Location = { X, Y }; }

    virtual void SetColor(const uint32_t LColor) { Color = LColor; }

    virtual bool Collision(const Entity obj)
    {
        return RectRectCollision(this->Location, this->Size,
            obj.GetLocation(), obj.GetSize());
    }

    virtual bool Collision(const Vector2D Location, const Vector2D Size)
    {
        return RectRectCollision(this->Location, this->Size,
            Location, Size);
    }
    
    //const int screen_width, const int screen_height

    virtual const void Draw();

    virtual void Update(const float dt);
};



