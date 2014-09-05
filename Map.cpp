#include "Map.h"
#include "cmath"
#include "glut.h"
Map::Map(char* fileName)
{
	if (!Tools::ReadNodesFromXML(fileName, this->nodes))
	{
		throw "Cannot load map!";
	}
	this->center.x=nodes[ROOTPOINT].getCenter().x;
	this->center.y=nodes[ROOTPOINT].getCenter().y;
	this->center.z=nodes[ROOTPOINT].getCenter().z;
	translateToCenter();
}

void Map::translateToCenter()
{
	for (std::map<int, Node>::iterator it = this->nodes.begin(); it != this->nodes.end(); ++it)
	{
		(*it).second.Translate(-center.x, -center.y, -center.z);
	}
}
Map::Map()
{
}
void Map::getIntersection(Node first, Node second, Point &firstPoint, Point &secondPoint)
{
	Point firstCenter = first.getCenter();
	Point secondCenter = second.getCenter();
	double radius = WIDTH / 2;
	double m;
	if (secondCenter.z == firstCenter.z)
		m = 0;
	else
		m = (firstCenter.x - secondCenter.x) / (secondCenter.z - firstCenter.z);
	double alpha = -2 * firstCenter.x;
	double beta = firstCenter.x * firstCenter.x - radius * radius / (1 + m * m);
	double delta = alpha * alpha - 4 * beta;
	if (delta <= 0)
	{
		firstPoint = firstCenter;
		secondPoint = firstCenter;
		return;
	}
	firstPoint.x = (-alpha + sqrt(delta)) / 2;
	secondPoint.x = (-alpha - sqrt(delta)) / 2;
	firstPoint.z = firstCenter.z + m * (firstPoint.x - firstCenter.x);
	secondPoint.z = firstCenter.z + m * (secondPoint.x - firstCenter.x);
	firstPoint.y = firstCenter.y;
	secondPoint.y = firstCenter.y;
}

CircleLineIntersection Map::BallCollision(int nodeKey, Point ballCenter)
{
	Point lastNodePosition = nodes[nodeKey].getCenter();
	double radius = WIDTH / 4;
	double m;
	if (lastNodePosition.z == ballCenter.z)
		m = 0;
	else
		m = (ballCenter.x - lastNodePosition.x) / (lastNodePosition.z - ballCenter.z);
	double alpha = -2 * ballCenter.x;
	double beta = ballCenter.x * ballCenter.x - radius * radius / (1 + m * m);
	double delta = alpha * alpha - 4 * beta;
	if (delta < 0)
		return CircleLineIntersection::NoIntersection;
	if (delta == 0)
		return CircleLineIntersection::Tangent;
	return CircleLineIntersection::Secant;

}

void Map::Draw()
{
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	Point first,second;
	for (std::map<int, Node>::iterator it = this->nodes.begin(); it != this->nodes.end(); ++it)
	{

		Node currentNode = (*it).second;
		std::vector<int> destinations=currentNode.getDestinations();
		currentNode.Draw();
		for (std::vector<int>::iterator vectorIt = destinations.begin(); vectorIt != destinations.end();++vectorIt)
		{
			glBegin(GL_QUADS);
			getIntersection(currentNode,nodes[*vectorIt],first,second);
			glVertex3d(first.x, first.y, first.z);
			glVertex3d(second.x, second.y, second.z);
			getIntersection(nodes[*vectorIt], currentNode, first, second);
			glVertex3d(second.x, second.y, second.z);
			glVertex3d(first.x, first.y, first.z);
			glEnd();
		}

	}
	glPopMatrix();
}