#pragma once
#include"Drawable.h"
#include <glut.h>
class Building:public Drawable
{
private:
	//Point center;
	double size;
	int type;
	GLuint texName;
	void model1(double w, double h);
	void loadTexture();
public:
	Building(Point center,double size, int type);
	void Draw();
	~Building(void);
};
