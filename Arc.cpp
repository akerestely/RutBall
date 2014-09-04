#include "Arc.h"

Arc::Arc(int source,int destination)
{
	this->source=source;
	this->destination=destination;
}

int Arc::getSource()
{
	return source;
}

int Arc::getDestination()
{
	return destination;
}
Arc::~Arc(void)
{
}
