#include "Enemy.h"

Enemy::Enemy(Vector2D Location, Vector2D Size = { 40.f, 50.f }, float Speed = 300.f, int8_t Health = 2, uint32_t Color = Colors::Red,
    bool MovingRight = true)
    :Entity(Location, Size, Color), Health(Health), MovingRight(MovingRight), Speed(Speed)
{
}

void Enemy::LineMove(const float dt, int lines[], int linesNum)
{
    if (MovingDown)
    {
        for (int j = 0; j < linesNum; j++)
        {
            if ((Location.Y < (100.0f * (j + 1))) && lines[j] < 4)
            {
                Location.Y += (Speed/2.f) * dt;
            }
            else if (Location.Y >= (100.0f * (j + 1)) && lines[j] < 4)
            {
                MovingDown = false;
                lines[j] += 1;
                break;
            }
        }
    }
}

void Enemy::Move(const float dt, int lines[], int linesNum, const int screenWidth, float playerX)
{
    if (Location.X < 50.0f)
        MovingRight = true;

    if (Location.X + Size.X > (screenWidth - 50.0f))
        MovingRight = false;

    if (MovingRight)
    {
        Location.X += Speed * dt;
        //Location.Y += 100 * dt;
        if (Location.X >= 500)
            Location.Y += cos(100 * dt);
        else
            Location.Y -= cos(100 * dt);

    }
    else
    {
        //Location.Y -= 100 * dt;
        if(Location.X < 520)
            Location.Y += cos(100 * dt);
        else
            Location.Y -= cos(100 * dt);
        Location.X -= Speed * dt;
    }

    LineMove(dt, lines, linesNum);
}

const void Enemy::Draw()
{
    if(!(Location.Y < 0))
        DrawSprite(Location.X, Location.Y, IdleRegion, Entity{ {0, 0}, { SCREEN_WIDTH, SCREEN_HEIGHT }, Colors::Black }, Sprite, Colors::Magenta);
    
    //Entity::Draw();
}
