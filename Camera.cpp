#include "Camera.h"
#include <glut.h>

Camera::Camera()
{
	dx=dz=ry;
}
void Camera::MoveX(double dx)
{
	this->dx+=dx;
}
void Camera::MoveZ(double dz)
{
	this->dz+=dz;
}
void Camera::RoateY(double ry)
{
	this->ry+=ry;
}
void Camera::Render()
{
	glTranslatef(dx,0,dz);
	glRotatef(ry,0,1,0);
}
