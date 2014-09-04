#pragma once

class Arc
{
private:
	int source,destination;
public:
	Arc(int source,int destination);
	int getSource();
	int getDestination(); 
	~Arc(void);
};
