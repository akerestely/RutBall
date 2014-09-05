#pragma once
#include "Node.h"
#include "map"
#include "Tools.h"
#define ROOTPOINT 5
class Map: public Drawable
{
	std::map<int, Node> nodes;
	void getIntersection(Node first, Node second, Point &firstPoint, Point &secondPoint);
	void translateToCenter();
public:
	Map(char* fileName);
	Map();
	void Draw() override;
	CircleLineIntersection BallCollision(int nodeKey, Point ballCenter);
};
