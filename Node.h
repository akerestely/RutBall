#pragma once
#include "Drawable.h"

#define WIDTH 20
class Node:public Drawable
{
	int id;
public:
	Node(int id, Point center);
	void Draw() override;
};
