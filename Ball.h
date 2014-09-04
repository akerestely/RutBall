#pragma once
#include <vector>
#include "glut.h"
#include "Point.h"
#include "math.h"
#include "Drawable.h"

class Ball : public Drawable
{
private:
	std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;
	static const int rings=50;
	static const int sectors=100;
	bool isUp;
	double oldY, alphaX, alphaY, alphaZ;
public:
	~Ball(void);
	Ball(float radius, Point center);
	void Draw();
	bool IsCollision();
	void MoveX(double dx);
	void MoveZ(double dz);
	void RotateY(double sy);
	void Jump(double dy);
};
