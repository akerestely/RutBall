#pragma once
#include "Drawable.h"
#include<vector>

#define SCALLING 900
class Node:public Drawable
{
	int id;
	std::vector<int> destinations;
public:
	Node();
	Node(int id, Point center);
	std::vector<int>& getDestinations();
	Point getCenter();
	void Translate(double dx, double dy, double dz);
	void Draw() override;
};
