#pragma once
#include "Node.h"
#include "map"
#include "Tools.h"
#include "glut.h"
#define STARTPOINT 5
#define ENDPOINT 5
#define CHECKPOINT 0
class Map: public Drawable
{
	std::map<int, Node> nodes;
	void getIntersection(Node first, Node second, Point &firstPoint, Point &secondPoint);
	void translateToCenter();
	void computeStreets();
	bool ballInsideStreet(int firstNodeKey, int adjacentIndex, Point ballCenter);
	bool Map::centerInsideStreet(Street street, Point ballCenter);
	double getLength(Point A, Point B);
	GLuint texName;
	void textureRoad();
public:
	Map(char* fileName);
	Map();
	void Draw() override;
	BallStreetPosition BallCollision(int &nodeKey, Point ballCenter);
	Node GetPoint(int key);
};
