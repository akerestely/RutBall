#pragma once
#include "Drawable.h"
#include<vector>

#define WIDTH 0.05
#define SCALLING 100
class Node:public Drawable
{
	int id;
	std::vector<int> destinations;
public:
	Node();
	Node(int id, Point center);
	std::vector<int>& getDestinations();
	Point getCenter();
	void Draw() override;
};
