#pragma once
#include "Point.h"

class Drawable
{
protected:
	Point center;
public:
	Drawable(Point center);
	virtual void Draw() = 0;
};
