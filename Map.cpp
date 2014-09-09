#include "Map.h"
#include "cmath"
#include "vector"
#include "glut.h"
#include "Texture.h"
Map::Map(char* fileName)
{
	if (!Tools::ReadNodesFromXML(fileName, this->nodes))
	{
		throw "Cannot load map!";
	}
	this->center.x=nodes[STARTPOINT].getCenter().x;
	this->center.y=nodes[STARTPOINT].getCenter().y;
	this->center.z=nodes[STARTPOINT].getCenter().z;
	translateToCenter();
	computeStreets();
	textureRoad();
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
	double radius = WIDTH / 8;
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
	}
	return BallStreetPosition::Outside;
}

void Map::Draw()
{
	
	Texture tex=Texture::GetInstance();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex.roadTex);
	Point first,second;
	for (std::map<int, Node>::iterator it = this->nodes.begin(); it != this->nodes.end(); ++it)
	{

		Node currentNode = (*it).second;
		currentNode.Draw();
		std::vector<int> destinations=currentNode.getDestinations();
		for (int i = 0; i < destinations.size(); i++)
		{
			glBegin(GL_QUADS);
			Street street = currentNode.GetStreet(i);
			
			glColor3f(116 / 255., 125 / 255., 135 / 255.);
			
			glTexCoord2d(0, 0);  glVertex3d(street.corners[0].x, street.corners[0].y, street.corners[0].z);
			glTexCoord2d(0, 10);  glVertex3d(street.corners[1].x, street.corners[1].y, street.corners[1].z);
			glTexCoord2d(10, 10);  glVertex3d(street.corners[2].x, street.corners[2].y, street.corners[2].z);
			glTexCoord2d(10, 0);  glVertex3d(street.corners[3].x, street.corners[3].y, street.corners[3].z);
			glEnd();
		}
		
	}
	glDisable(GL_TEXTURE_2D);
}
Node Map::GetPoint(int key)
{
	if (nodes.count(key) == 0)
		return nodes[0];
	return nodes[key];
}
bool Map::ballInsideStreet(int firstNodeKey, int adjacentIndex, Point ballCenter)
{
	double radius = WIDTH / 8;
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
void Map::textureRoad()
{	
	 int width,height;
	 char* buffer = Tools::esLoadTGA("Texture/football.tga",&width,&height);
	 glGenTextures ( 1, &texName);
	 glBindTexture ( GL_TEXTURE_2D, texName);
	 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	 glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	 free ( buffer );

}