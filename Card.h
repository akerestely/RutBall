#pragma once
#include "glut.h"
#include "Point.h"
#include "Drawable.h"

class Card : public Drawable
{
	double angle;
public:
	Card(Point center);
	Card(){}
	~Card(void);
	void Draw();
};
