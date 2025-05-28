#pragma once
#include <cmath>
void PixelDraw(int x, int y, uint32_t Color);

class Vector2D
{
public:
    float X, Y;

    Vector2D(float X = 0.f, float Y = 0.f)
        : X(X), Y(Y)
    {
    }

    Vector2D operator=(Vector2D second)
    {
        this->X = second.X;
        this->Y = second.Y;
        return *this;
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

inline bool RectRectCollision(const float r1x, const float r1y, const float r1w, const float r1h,
    const float r2x, const float r2y, const float r2w, const float r2h)
{
    return (r1x + r1w >= r2x &&
        r1x <= r2x + r2w &&
        r1y + r1h >= r2y &&
        r1y < r2y + r2h);
}

inline bool RectRectCollision(const Vector2D rec1Loc, const Vector2D rec1Size,
    const Vector2D rec2Loc, const Vector2D rec2Size)
{
    return RectRectCollision(rec1Loc.X, rec1Loc.Y, rec1Size.X, rec1Size.Y,
        rec2Loc.X, rec2Loc.Y, rec2Size.X, rec2Size.Y);
}

inline float Edge(Vector2D v0, Vector2D v1, Vector2D p)
{
    Vector2D a = p - v0;
    Vector2D b = v1 - v0;

    return a.X * b.Y - a.Y * b.X;
}

inline void drawTriangle(Vector2D v0, Vector2D v1, Vector2D v2, uint32_t Color)
{
    for (int x = 0; x < 1024; x++)
    {
        for (int y = 0; y < 768; y++)
        {
            Vector2D p = { (float)x, (float)y };

            float e10 = Edge(v1, v0, p);
            float e21 = Edge(v2, v1, p);
            float e02 = Edge(v0, v2, p);
            if (e10 >= 0.f && e21 >= 0.0f && e02 >= 0.0f)
            {
                PixelDraw(x, y, Color);
            }
        }
    }
            
}

inline void DrawCircle(Vector2D Center, const int res, const float radius, uint32_t Color)
{
    Vector2D v1;
    Vector2D v2;

    float angle1 = 2.f * 3.141592653589 * (static_cast<float>(0) / res);
    float x1 = Center.X + cos(angle1) * radius;
    float y1 = Center.Y + sin(angle1) * radius;
    v1 = { x1, y1 };

    for (int i = 0; i <= res; ++i)
    {
        float angle2 = 2.f * 3.141592653589 * (static_cast<float>(i + 1) / res);
        float x2 = Center.X + cos(angle2) * radius;
        float y2 = Center.Y + sin(angle2) * radius;
        v2 = { x2, y2 };
        drawTriangle(Center, v1, v2, Color);
        v1 = v2;
    }
}


