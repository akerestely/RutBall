#include "Node.h"
#include "glut.h"
#include "cmath"
Node::Node(int id, Point center)
:Drawable(center),id(id)
{
	this->center.x = -(center.x - 36) * SCALLING;
	this->center.y = center.y;
	this->center.z = (center.z - 39) * SCALLING;
}

Node::Node()
{
	center=Point();
	id=-1;
}
void Node::Draw()
{
	/*glBegin(GL_LINE_LOOP);
	glColor3f(1., 0, 0);
	glVertex3d(-((center.x - 36) * SCALLING + WIDTH / 2), center.y, (center.z - 39) * SCALLING + WIDTH / 2);
	glVertex3d(-((center.x - 36) * SCALLING - WIDTH / 2), center.y, (center.z - 39) * SCALLING + WIDTH / 2);
	glVertex3d(-((center.x - 36) * SCALLING - WIDTH / 2), center.y, (center.z - 39) * SCALLING - WIDTH / 2);
	glVertex3d(-((center.x - 36) * SCALLING + WIDTH / 2), center.y, (center.z - 39) * SCALLING - WIDTH / 2);
	glEnd();*/
	
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(center.x, center.y, center.z);
	for(int theta = 0; theta <= 360; theta++)
	{
		glVertex3d(center.x + WIDTH / 2 * cos(theta * PI / 180), center.y, center.z + WIDTH / 2 * sin(theta * PI / 180));
	}
	glEnd();

	//glBegin(GL_LINE_LOOP);
	//glColor3f(1., 0, 0);
	//glVertex3d(center.x - WIDTH / 2, center.y, center.z + WIDTH / 2);
	//glVertex3d(center.x + WIDTH / 2, center.y, center.z + WIDTH / 2);
	//glVertex3d(center.x + WIDTH / 2, center.y, center.z - WIDTH / 2);
	//glVertex3d(center.x - WIDTH / 2, center.y, center.z - WIDTH / 2);
	//glEnd();

}

Point Node::getCenter()
{
	return center;
}

std::vector<int>& Node::getDestinations()
{
	return destinations;
}

void Node::Translate(double dx, double dy, double dz)
{
	this->center.x += dx;
	this->center.y += dy;
	this->center.z += dz;
}