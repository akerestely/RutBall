#pragma once
#include<vector>
#include<map>
#include "Point.h"
#include "Node.h"
#include "Building.h"

enum BallStreetPosition{
	Inside,
	Outside,
};
class Tools
{
public:
	Tools(void);
	static int ReadNodesFromXML(char *fileName, std::map<int,Node> &nodes);
	static int ReadBuildingsFromXML(char *fileName, std::vector<Building> &buildings);
	~Tools(void);
};
