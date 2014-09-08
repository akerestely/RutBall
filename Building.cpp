#include "Tools.h"
#include "Building.h"
#include "Texture.h"

Building::Building(Point center,double size, int type)
	:Drawable(center), size(size), type(type), mode(false)
{
}

Building::Building(Point center, double l, double w, double h, double s)
	: Drawable(center), length(l), width(w), height(h), size(s), mode(false)
{
}
void Building::Draw() 
{
	switch(this->type) {
		case 1:
			{
				double l=0.30,w=0.25,h=3.1;

				model1(l,w,h);
				break;
			} 
		case 2:
			{
				double l=0.45,w=0.25,h=3.25; 
				model1(l,w,h);
				break;
			} 
		case 3:
			{
				double l=0.55, w=0.45,h=0.25; 
				model1(l,w,h);
				break;
			} 
	}
}
void Building::model1(double l,double w, double h) 
{
	length = l;
	width = w;
	height = h;
	Texture tex=Texture::GetInstance();
	glEnable(GL_TEXTURE_2D);
	if (mode)
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glBindTexture(GL_TEXTURE_2D, tex.wallTex1);	
	glPushMatrix();
	glTranslatef(this->center.x, this->center.y+h*size, this->center.z);
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	{
		// Top face (y = 1.0f)
		// Define vertices in counter-clockwise (CCW) order with normal pointing out
		glVertex3f( w*size, h*size, -l*size);
		glVertex3f( -w*size, h*size, -l*size);
		glVertex3f( -w*size, h*size, l*size);
		glVertex3f( w*size, h*size, l*size);
	}
	glEnd();
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	{
		// Bottom face (y = -1.0f)
		glVertex3f( w*size, -h*size, l*size);
		glVertex3f( -w*size, -h*size, l*size);
		glVertex3f( -w*size, -h*size, -l*size);
		glVertex3f( w*size, -h*size, -l*size);
	}
	glEnd();
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	{
		// Front face  (z = 1.0f)
		glTexCoord2f(2.0, 2.0); glVertex3f( w*size, h*size, l*size);
		glTexCoord2f(0.0, 2.0); glVertex3f( -w*size, h*size, l*size);
		glTexCoord2f(0.0, 0.0); glVertex3f( -w*size, -h*size, l*size);
		glTexCoord2f(2.0, 0.0); glVertex3f( w*size, -h*size, l*size);
	}
	glEnd();
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	{
		// Right face (x = 1.0f)
		glTexCoord2f(0.0, 2.0); glVertex3f( w*size, h*size, -l*size);
		glTexCoord2f(2.0, 2.0); glVertex3f( w*size, h*size, l*size);
		glTexCoord2f(2.0, 0.0); glVertex3f( w*size, -h*size, l*size);
		glTexCoord2f(0.0, 0.0); glVertex3f( w*size, -h*size, -l*size);
	}
	glEnd();
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	{
		// Left face (x = -1.0f)
		glTexCoord2f(0.0, 2.0); glVertex3f( -w*size, h*size, l*size);
		glTexCoord2f(2.0, 2.0); glVertex3f( -w*size, h*size, -l*size);
		glTexCoord2f(2.0, 0.0); glVertex3f( -w*size, -h*size, -l*size);
		glTexCoord2f(0.0, 0.0); glVertex3f( -w*size, -h*size, l*size);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, tex.wallTex2);
	glBegin(GL_QUADS);
	{
		// Back face (z = -1.0f)
		glTexCoord2f(2.0, 0.0); glVertex3f( w*size, -h*size, -l*size);
		glTexCoord2f(0.0, 0.0); glVertex3f( -w*size, -h*size, -l*size);
		glTexCoord2f(0.0, 2.0); glVertex3f( -w*size, h*size, -l*size);
		glTexCoord2f(2.0, 2.0); glVertex3f(w*size, h*size, -l*size);
	}
	glEnd();  // End of drawing color-cube
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D); 
}

double getLength(Point A, Point B)
{
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.z - B.z) * (A.z - B.z));
}
void Building::SwitchMode(Point p)
{
	Point A = Point((this->center.x + width)* size, 0, (this->center.z + length)*size);
	Point B = Point(-(this->center.x + width)* size, 0, (this->center.z + length)*size);
	Point C = Point(-(this->center.x + width)* size, 0, -(this->center.z + length)*size);
	Point D = Point((this->center.x + width)* size, 0, -(this->center.z + length)*size);
	double rectArea = getLength(A, D) * getLength(A, B);

	// triange with vertexes: C, B, ballCenter
	double l1 = getLength(C, B);
	double l2 = getLength(C, p);
	double l3 = getLength(p, B);
	double sp = (l1 + l2 + l3) / 2;
	double firstTriangle = sqrt(sp * (sp - l1) * (sp - l2) * (sp - l3));

	// triange with vertexes: A, D ballCenter
	l1 = getLength(A, D);
	l2 = getLength(A, p);
	l3 = getLength(p, D);
	sp = (l1 + l2 + l3) / 2;
	double secondTriangle = sqrt(sp * (sp - l1) * (sp - l2) * (sp - l3));

	// triange with vertexes: D, C, ballCenter
	l1 = getLength(D, C);
	l2 = getLength(C, p);
	l3 = getLength(D, p);
	sp = (l1 + l2 + l3) / 2;
	double thirdTriangle = sqrt(sp * (sp - l1) * (sp - l2) * (sp - l3));

	if (firstTriangle + secondTriangle + thirdTriangle > rectArea)
		mode = false;
	else
		mode = true;
}


Building::~Building(void)
{
}
