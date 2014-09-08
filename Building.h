#pragma once
#include"Drawable.h"
#include <glut.h>
class Building:public Drawable
{
private:
	double size;
	int type;
	void model1(double w, double h);
	double angleOfRotation;
	GLuint myTexture;
public:
	Building(Point center,double size, int type,double angleOfRotation);
	void Draw();
	~Building(void);
};
