#pragma once
#include <vector>
#include "glut.h"
#include "Point.h"
#include "math.h"
#include "Drawable.h"
#include "Tools.h"
#include "glut.h"

class Ball : public Drawable
{
private:
	std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;
	static const int rings=50;
	static const int sectors=100;
	bool isUp, boolX, boolZ;
	double oldY, alphaX, alphaZ, rotY;
	GLuint texName;

	void textureBall();
public:
	~Ball(void);
	Ball(float radius, Point center);
	void Draw();
	bool IsCollision();
	void MoveX(double dx);
	void MoveZ(double dz);
	void RotateY(double ry);
	void Jump(double dy);
};
