#include "Projectile.h"

void Projectile::Update(const float dt)
{
    SetLocation(GetLocation().X, GetLocation().Y - Speed * dt);
}
