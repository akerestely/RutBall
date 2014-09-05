#pragma once
#include "Node.h"
#include "map"
#include "Tools.h"
class Map: public Drawable
{
	std::map<int, Node> nodes;
	void GetIntersection(Node first, Node second, Point &firstPoint, Point &secondPoint);
public:
	Map(std::map<int, Node> nodes);
	Map();
	void Draw() override;

};
