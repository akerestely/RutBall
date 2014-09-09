#pragma once
#include"Drawable.h"

#define DIST_FROM_SKY 200.0f
#define GROUND_TEXTURE_MULTIPLIER 500

class SkyCube : public Drawable
{
public:
	SkyCube();
	void Draw();
	void SetPoz(Point p);
};
