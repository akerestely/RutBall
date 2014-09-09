#pragma once
#include"Drawable.h"
#include <glut.h>
class Building:public Drawable
{
private:
	double size;
	int type;
	bool mode;
	void model1(double l,double w, double h);

	double length;
	double width;
	double height;
public:
	Building(Point center,double size, int type);
	Building(Point center,double l, double w,double h,double size);
	void SwitchMode(Point p,double rotY);
	void Draw();
	~Building(void);
};
