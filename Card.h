#pragma once
#include "glut.h"
#include "Point.h"
#include "Drawable.h"
#define WIDTH 1.5
#define HEIGHT 2.5
class Card : public Drawable
{
	double angle;
public:
	Card(Point center);
	~Card(void);
	void Draw();
};
