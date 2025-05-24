#include "Entity.h"

Entity::Entity(Vector2D Location, Vector2D Size, uint32_t Color = Colors::Red)
    : Location(Location), Size(Size), color(Color)
{
}

Entity::Entity(Vector2D Location, Vector2D Size, Color Color = Colors::Red)
    : Location(Location), Size(Size), color(Color)
{
}

const void Entity::Draw()
{
    DrawRectangle(Location.X, Location.Y, Size.X, Size.Y, Colors::MakeColor(color));
}

void Entity::Update(const float dt)
{
}

