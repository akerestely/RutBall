#pragma once
#include "glut.h"
#include "Point.h"
#include "Drawable.h"

class Card : public Drawable
{
	double angle;
	bool isMiniCard;
	void DrawBigCard();
	void DrawMiniCard();
public:
	Card(Point center,bool isMiniCard);
	Card(){}
	
	~Card(void);
	void Draw();

};
