#pragma once
#include "Node.h"
#include "map"
#include "Tools.h"
#define ROOTPOINT 5
//#define STARTPOINT 15
#define STARTPOINT 5
#define ENDPOINT 5
class Map: public Drawable
{
	std::map<int, Node> nodes;
	void getIntersection(Node first, Node second, Point &firstPoint, Point &secondPoint);
	void translateToCenter();
	void computeStreets();
	bool ballInsideStreet(int firstNodeKey, int adjacentIndex, Point ballCenter);
	bool Map::centerInsideStreet(Street street, Point ballCenter);
	double getLength(Point A, Point B);
public:
	Map(char* fileName);
	Map();
	void Draw() override;
	BallStreetPosition BallCollision(int &nodeKey, Point ballCenter);
	Node GetStartPoint();
	Node GetEndPoint();
};
