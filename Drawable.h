#pragma once
#include "Point.h"

class Drawable
{
protected:
	Point center;
public:
	Drawable(Point center);
	Drawable();
	virtual void Draw() = 0;
};
