#include "Entity.h"

Entity::Entity(Vector2D Location, Vector2D Size, float Speed = 0.f, uint32_t Color = Colors::Red)
    : Location(Location), Size(Size), Speed(Speed), color(Color)
{
}

const void Entity::Draw()
{
    DrawRectangle(Location.X, Location.Y, Size.X, Size.Y, Colors::MakeColor(color));
}

void Entity::Update(const float dt)
{
}

