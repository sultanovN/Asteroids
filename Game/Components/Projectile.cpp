#include "Projectile.h"

void Projectile::Update(const float dt)
{
    Location.Y -= Speed * dt;
}

const void Projectile::Draw()
{
    //DrawSprite(GetLocation().X, GetLocation().Y, Entity{ {24, 72}, {19, 47}, Colors::Black }, Sprite, Colors::Magenta);
    Entity::Draw();
}
