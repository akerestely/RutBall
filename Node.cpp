#include "Node.h"
#include "glut.h"
Node::Node(int id, Point center)
:Drawable(center),id(id)
{
	
}
void Node::Draw()
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1., 0, 0);
	glVertex3d(center.x + WIDTH / 2, center.y, center.z + WIDTH / 2);
	glVertex3d(center.x - WIDTH / 2, center.y, center.z + WIDTH / 2);
	glVertex3d(center.x - WIDTH / 2, center.y, center.z - WIDTH / 2);
	glVertex3d(center.x + WIDTH / 2, center.y, center.z - WIDTH / 2);
	glEnd();
}