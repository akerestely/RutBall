#include "Map.h"
#include "cmath"
#include "glut.h"
Map::Map(std::map<int, Node> nodes)
{
	this->nodes.insert(nodes.begin(), nodes.end());
}
Map::Map()
{

}
void Map::GetIntersection(Node first, Node second, Point &firstPoint, Point &secondPoint)
{
	Point firstCenter = first.getCenter();
	Point secondCenter = second.getCenter();
	double radius = first.GetRadius();
	double m;
	if (secondCenter.z == firstCenter.z)
		m = 0;
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
void Map::Draw()
{
	Point first,second;
	for (std::map<int, Node>::iterator it = this->nodes.begin(); it != this->nodes.end(); ++it)
	{
	
		Node currentNode = (*it).second;
		std::vector<int> destinations=currentNode.getDestinations();
		currentNode.Draw();
		for (std::vector<int>::iterator vectorIt = destinations.begin(); vectorIt != destinations.end();++vectorIt)
		{
			glBegin(GL_QUADS);
			GetIntersection(currentNode,nodes[*vectorIt],first,second);
			glVertex3d(first.x, first.y, first.z);
			glVertex3d(second.x, second.y, second.z);
			GetIntersection(nodes[*vectorIt], currentNode, first, second);
			glVertex3d(second.x, second.y, second.z);
			glVertex3d(first.x, first.y, first.z);
			glEnd();
			/*glBegin(GL_LINES);
			glVertex3d(currentNode.getCenter().x, currentNode.getCenter().y, currentNode.getCenter().z);
			glVertex3d(nodes[*vectorIt].getCenter().x, nodes[*vectorIt].getCenter().y, nodes[*vectorIt].getCenter().z);
			glEnd();*/
		}
		
	}
}