#pragma once
#include<vector>
#include "Point.h"
#include "Node.h"
class Tools
{
public:
	Tools(void);
	static int ReadNodesFromXML(char *fileName, std::vector<Node> &nodes);
	static char*  esLoadTGA(char *fileName, double *width, double *height);
	~Tools(void);
};
