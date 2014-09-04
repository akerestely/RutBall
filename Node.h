#pragma once
#include "Drawable.h"
#include<vector>

#define WIDTH 0.02
class Node:public Drawable
{
	int id;
	std::vector<int> destinations;
public:
	Node();
	Node(int id, Point center);
	std::vector<int>& getDestinations();
	void Draw() override;
};
