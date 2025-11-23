#include "Projectile.h"

void Projectile::Update(const float dt)
{
    Location.Y -= Speed * dt;
}

const void Projectile::Draw()
{
    //Entity::Draw();

    DrawSprite(GetLocation().X, GetLocation().Y, Entity{ SpriteRegionLocation, {Size.X, Size.Y}, Colors::Black }, Entity{ {0, 0}, { SCREEN_WIDTH, SCREEN_HEIGHT }, Colors::Black }, Sprite, Colors::Magenta);
}
