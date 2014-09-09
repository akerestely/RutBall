#include "Tools.h"
#include "Building.h"
#include "Texture.h"
#include "CameraSpectator.h"

Building::Building(Point center, double size, int type)
	:Drawable(center), size(size), type(type), mode(false)
{
}

Building::Building(Point center, double l, double w, double h, double s)
	: Drawable(center), length(l), width(w), height(h), size(s), mode(false)
{
}
void Building::Draw()
{
	switch (this->type) {
	case 1:
	{
		double l = 0.30, w = 0.25, h = 3.1;

		model1(l, w, h);
		break;
	}
	case 2:
	{
		double l = 0.45, w = 0.25, h = 3.25;
		model1(l, w, h);
		break;
	}
	case 3:
	{
		double l = 0.55, w = 0.45, h = 0.25;
		model1(l, w, h);
		break;
	}
	}
}
void Building::model1(double l, double w, double h)
{
	length = l;
	width = w;
	height = h;
	Texture tex = Texture::GetInstance();
	glEnable(GL_TEXTURE_2D);
	if (!mode)
	{
		glBindTexture(GL_TEXTURE_2D, tex.wallTex1);
		glPushMatrix();
		glTranslatef(this->center.x, this->center.y + h*size, this->center.z);
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		{
			// Top face (y = 1.0f)
			// Define vertices in counter-clockwise (CCW) order with normal pointing out
			glVertex3f(w*size, h*size, -l*size);
			glVertex3f(-w*size, h*size, -l*size);
			glVertex3f(-w*size, h*size, l*size);
			glVertex3f(w*size, h*size, l*size);
		}
		glEnd();
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		{
			// Bottom face (y = -1.0f)
			glVertex3f(w*size, -h*size, l*size);
			glVertex3f(-w*size, -h*size, l*size);
			glVertex3f(-w*size, -h*size, -l*size);
			glVertex3f(w*size, -h*size, -l*size);
		}
		glEnd();
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		{
			// Front face  (z = 1.0f)
			glTexCoord2f(2.0, 2.0); glVertex3f(w*size, h*size, l*size);
			glTexCoord2f(0.0, 2.0); glVertex3f(-w*size, h*size, l*size);
			glTexCoord2f(0.0, 0.0); glVertex3f(-w*size, -h*size, l*size);
			glTexCoord2f(2.0, 0.0); glVertex3f(w*size, -h*size, l*size);
		}
		glEnd();
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		{
			// Right face (x = 1.0f)
			glTexCoord2f(0.0, 2.0); glVertex3f(w*size, h*size, -l*size);
			glTexCoord2f(2.0, 2.0); glVertex3f(w*size, h*size, l*size);
			glTexCoord2f(2.0, 0.0); glVertex3f(w*size, -h*size, l*size);
			glTexCoord2f(0.0, 0.0); glVertex3f(w*size, -h*size, -l*size);
		}
		glEnd();
		glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
		{
			// Left face (x = -1.0f)
			glTexCoord2f(0.0, 2.0); glVertex3f(-w*size, h*size, l*size);
			glTexCoord2f(2.0, 2.0); glVertex3f(-w*size, h*size, -l*size);
			glTexCoord2f(2.0, 0.0); glVertex3f(-w*size, -h*size, -l*size);
			glTexCoord2f(0.0, 0.0); glVertex3f(-w*size, -h*size, l*size);
		}
		glEnd();
		glBindTexture(GL_TEXTURE_2D, tex.wallTex2);
		glBegin(GL_QUADS);
		{
			// Back face (z = -1.0f)
			glTexCoord2f(2.0, 0.0); glVertex3f(w*size, -h*size, -l*size);
			glTexCoord2f(0.0, 0.0); glVertex3f(-w*size, -h*size, -l*size);
			glTexCoord2f(0.0, 2.0); glVertex3f(-w*size, h*size, -l*size);
			glTexCoord2f(2.0, 2.0); glVertex3f(w*size, h*size, -l*size);
		}
		glEnd();  // End of drawing color-cube

		glPopMatrix();
	}
}
void Building::SwitchMode(Point p,double rotY)
{
	rotY += 90;
	Point A = Point(center.x + width*size, 0, center.z + length*size);
	Point D = Point(center.x - width*size, 0, center.z + length*size);
	Point C = Point(center.x - width*size, 0, center.z - length*size);
	Point B = Point(center.x + width*size, 0, center.z - length*size);

	double cosAlfa = cos(rotY*PI / 180);
	double sinAlfa = sin(rotY*PI / 180);
	for (double r = 1; r < 10; r++)
	{
		Point M(p.x,0,p.z);
		M.x += r*cosAlfa;
		M.z += r*sinAlfa;
		SF3dVector AP(A, M), AB(A, B), AD(A, D);
		if (((0 < (AP*AB)) && ((AP*AB) < (AB*AB))) &&
			((0 < (AP*AD)) && ((AP*AD) < (AD*AD))))
		{
			mode = true;
			break;
		}
		else
			mode = false;
	}
}


Building::~Building(void)
{
}
