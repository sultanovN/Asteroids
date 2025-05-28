#pragma once
#include "Color.h"

class Surface
{
public:
	Surface(int width, int height);
	Surface(const Surface& rhs);
	~Surface(); 
	Surface& operator=(const Surface&);

	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;

	int GetWidth()const { return width; };
	int GetHeight()const { return height; };
private:
	Color* pPixels = nullptr;
	int width;
	int height;
};