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

bool RectRectCollision(const float r1x, const float r1y, const float r1w, const float r1h,
    const float r2x, const float r2y, const float r2w, const float r2h)
{
    if (r1x + r1w >= r2x &&
        r1x <= r2x + r2w &&
        r1y + r1h >= r2y &&
        r1y < r2y + r2h)
        return true;
    return false;
}

bool RectRectCollision(const Vector2D rec1Loc, const Vector2D rec1Size,
    const Vector2D rec2Loc, const Vector2D rec2Size)
{
    return RectRectCollision(rec1Loc.X, rec1Loc.Y, rec1Size.X, rec1Size.Y,
        rec2Loc.X, rec2Loc.Y, rec2Size.X, rec2Size.Y);
}

#endif