#include "Projectile.h"

void Projectile::Update(const float dt)
{
    Location.Y -= Speed * dt;
}
