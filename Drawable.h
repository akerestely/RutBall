#pragma once
#include "Point.h"

class Drawable
{
	Point center;
public:
	Drawable(Point center);
	virtual void Draw() = 0;
};
