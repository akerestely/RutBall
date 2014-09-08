#pragma once
#include "Drawable.h"
#include<vector>

#define SCALLING 1000
struct Street{
	Point corners[4];
};
class Node:public Drawable
{
	int id;
	std::vector<int> destinations;
	std::vector<Street> streets;
public:
	Node();
	Node(int id, Point center);
	std::vector<int>& getDestinations();
	Point getCenter();
	void Translate(double dx, double dy, double dz);
	void Draw() override;
	void addStreet(Street street);
	Street GetStreet(int index);
};
