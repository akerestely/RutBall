#pragma once
#include "Drawable.h"

#define WIDTH 0.02
class Node:public Drawable
{
	int id;
public:
	Node(int id, Point center);
	void Draw() override;
};
