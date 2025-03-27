#include "Entity.h"

Entity::Entity(Vector2D Location, Vector2D Size, float Speed = 0.f, uint32_t Color = 0)
    : Location(Location), Size(Size), Speed(Speed), Color(Color)
{
}

const void Entity::Draw()
{
    DrawRectangle(Location.X, Location.Y, Size.X, Size.Y, Color);
}

void Entity::Update(const float dt)
{
}

