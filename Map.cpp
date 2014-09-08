#include "Map.h"
#include "cmath"
#include "vector"
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
	computeStreets();
}

void Map::computeStreets()
{
	Point first, second;
	for (std::map<int, Node>::iterator it = this->nodes.begin(); it != this->nodes.end(); ++it)
	{

		Node currentNode = (*it).second;
		std::vector<int> destinations = currentNode.getDestinations();
		Street newStreet;
		for (int i = 0; i < destinations.size(); i++)
		{
			getIntersection(currentNode, nodes[destinations[i]], first, second);
			newStreet.corners[0] = first;
			newStreet.corners[1] = second;
			getIntersection(nodes[destinations[i]], currentNode, first, second);
			newStreet.corners[2] = second;
			newStreet.corners[3] = first;
			it->second.addStreet(newStreet);
		}
	}
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

BallStreetPosition Map::BallCollision(int &nodeKey, Point ballCenter)
{
	Point lastNodePosition = nodes[nodeKey].getCenter();
	double radius = WIDTH / 4;
	double insideNode = radius + sqrt((ballCenter.x - lastNodePosition.x) * (ballCenter.x - lastNodePosition.x) + (ballCenter.z - lastNodePosition.z) * (ballCenter.z - lastNodePosition.z));
	if (insideNode <= WIDTH / 2)
	{
		return BallStreetPosition::Inside;
	}
	double m;
	std::vector<int> destinations = nodes[nodeKey].getDestinations();

	for (int i = 0; i < destinations.size(); i++)
	{
		Point nextNodePosition = nodes[destinations[i]].getCenter();
		insideNode = radius + sqrt((ballCenter.x - nextNodePosition.x) * (ballCenter.x - nextNodePosition.x) + (ballCenter.z - nextNodePosition.z) * (ballCenter.z - nextNodePosition.z));
		if (insideNode <= WIDTH / 2)
		{
			nodeKey = destinations[i];
			return BallStreetPosition::Inside;
		}
		if (ballInsideStreet(nodeKey, i, ballCenter))
			return BallStreetPosition::Inside;
		/*if (lastNodePosition.x == nextNodePosition.x)
			m = 0;
		else
			m = (nextNodePosition.z - lastNodePosition.z) / (nextNodePosition.x - lastNodePosition.x);
		double factor = lastNodePosition.z - ballCenter.z;
		double alpha = 1 + m * m;
		double beta = -2 * ballCenter.x - m * m * lastNodePosition.x + 2 * m * factor;
		double gama = ballCenter.x * ballCenter.x + m * m * lastNodePosition.x * lastNodePosition.x - 2 * m * lastNodePosition.x * factor + factor * factor - radius * radius; 
		double delta = beta * beta - 4 * alpha * gama;
		if (delta == 0)
			return CircleLineIntersection::Tangent;
		else if (delta > 0)
			return CircleLineIntersection::Secant;
		else
			continue;*/
		
	}
	return BallStreetPosition::Outside;
}

void Map::Draw()
{
	Point first,second;
	for (std::map<int, Node>::iterator it = this->nodes.begin(); it != this->nodes.end(); ++it)
	{

		Node currentNode = (*it).second;
		std::vector<int> destinations=currentNode.getDestinations();
		currentNode.Draw();
		for (int i = 0; i < destinations.size(); i++)
		{
			glBegin(GL_QUADS);
			Street street = currentNode.GetStreet(i);
			glVertex3d(street.corners[0].x, street.corners[0].y, street.corners[0].z);
			glVertex3d(street.corners[1].x, street.corners[1].y, street.corners[1].z);
			glVertex3d(street.corners[2].x, street.corners[2].y, street.corners[2].z);
			glVertex3d(street.corners[3].x, street.corners[3].y, street.corners[3].z);
			glEnd();
		}
	}
}
Node Map::GetStartPoint()
{
	if (nodes.count(STARTPOINT) == 0)
		return nodes[0];
	return nodes[STARTPOINT];
}
Node Map::GetEndPoint()
{
	if (nodes.count(ENDPOINT) == 0)
		return nodes[0];
	return nodes[ENDPOINT];
}
bool Map::ballInsideStreet(int firstNodeKey, int adjacentIndex, Point ballCenter)
{
	double radius = WIDTH / 4;
	Street street = nodes[firstNodeKey].GetStreet(adjacentIndex);
	if (!centerInsideStreet(street, ballCenter))
	{
		return false;
	}

	Point A = street.corners[0];
	Point B = street.corners[3];
	double f1 = A.z - B.z;
	double f2 = A.x - B.x;
	double firstDistance = abs(f1 * ballCenter.x - A.x * f1 - f2 * ballCenter.z + A.z * f2);
	double firstNorm = sqrt(f1 * f1 + f2 * f2);

	A = street.corners[1];
	B = street.corners[2];
	f1 = A.z - B.z;
	f2 = A.x - B.x;
	double secondDistance = abs(f1 * ballCenter.x - A.x * f1 - f2 * ballCenter.z + A.z * f2);
	double secondNorm = sqrt(f1 * f1 + f2 * f2);

	if (firstDistance < secondDistance)
		return radius * firstNorm <= firstDistance;
	return radius * secondNorm <= secondDistance;
}

bool Map::centerInsideStreet(Street street, Point ballCenter)
{
	Point A = street.corners[0];
	Point B = street.corners[1];
	Point C = street.corners[2];
	Point D = street.corners[3];
	double rectArea = getLength(A, D) * getLength(A, B);

	// triange with vertexes: C, B, ballCenter
	double l1 = getLength(C, B);
	double l2 = getLength(C, ballCenter);
	double l3 = getLength(ballCenter, B);
	double sp = (l1 + l2 + l3) / 2;
	double firstTriangle = sqrt(sp * (sp - l1) * (sp - l2) * (sp - l3));
	
	// triange with vertexes: A, D ballCenter
	l1 = getLength(A, D);
	l2 = getLength(A, ballCenter);
	l3 = getLength(ballCenter, D);
	sp = (l1 + l2 + l3) / 2;
	double secondTriangle = sqrt(sp * (sp - l1) * (sp - l2) * (sp - l3));
	
	// triange with vertexes: D, C, ballCenter
	l1 = getLength(D, C);
	l2 = getLength(C, ballCenter);
	l3 = getLength(D, ballCenter);
	sp = (l1 + l2 + l3) / 2;
	double thirdTriangle = sqrt(sp * (sp - l1) * (sp - l2) * (sp - l3));

	return firstTriangle + secondTriangle + thirdTriangle <= rectArea;
	
}

double Map::getLength(Point A, Point B)
{
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.z - B.z) * (A.z - B.z));
}