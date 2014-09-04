#pragma once
#include<vector>
#include<map>
#include "Point.h"
#include "Node.h"
class Tools
{
public:
	Tools(void);
	static int ReadNodesFromXML(char *fileName, std::map<int,Node> &nodes);
	~Tools(void);
};
