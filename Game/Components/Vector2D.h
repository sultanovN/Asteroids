#pragma once
#ifndef vec2D
#define vec2D

struct Vector2D
{
    float X, Y;

    Vector2D(float X = 0.f, float Y = 0.f)
        : X(X), Y(Y)
    {
    }

    Vector2D operator+(Vector2D second)
    {
        return Vector2D(this->X + second.X, this->Y + second.Y);
    }

    Vector2D operator-(Vector2D second)
    {
        return Vector2D(this->X - second.X, this->Y - second.Y);
    }

	Vector2D& operator +=(const Vector2D& second)
	{
		this->X += second.X;
		this->Y += second.Y;
		return *this;
	}

	Vector2D& operator -=(const Vector2D& second)
	{
		this->X -= second.X;
		this->Y -= second.Y;
		return *this;
	}
};

bool RectRectCollision(float r1x, float r1y, float r1w, float r1h,
    float r2x, float r2y, float r2w, float r2h)
{
    if (r1x + r1w >= r2x &&
        r1x <= r2x + r2w &&
        r1y + r1h >= r2y &&
        r1y < r2y + r2h)
        return true;
    return false;
}
#endif