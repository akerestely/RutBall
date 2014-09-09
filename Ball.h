#pragma once
#include <vector>
#include "glut.h"
#include "Point.h"
#include "math.h"
#include "Drawable.h"

#define POWER 0.5
#define GRAVITY 0.05
class Ball : public Drawable
{
private:
	std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;
	static const int rings=50;
	static const int sectors=100;
	bool boolX, boolZ;
	bool canJump;
	double energy;
	double oldY, alphaX, alphaZ, rotY;
	int texnr;
public:
	~Ball(void);
	Ball(float radius, Point center);
	void SetTexNr(int nr);
	void Draw();
	void MoveX(double dx);
	void MoveZ(double dz);
	void Jump(bool &isJump);
};
