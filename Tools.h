#pragma once
#include<vector>
#include<map>
#include "Point.h"
#include "Node.h"

enum BallStreetPosition{
	Inside,
	Outside,
};
class Tools
{
public:
	Tools(void);
	static int ReadNodesFromXML(char *fileName, std::map<int,Node> &nodes);
	~Tools(void);
	static char*  esLoadTGA ( char *fileName, int *width, int *height );
};
