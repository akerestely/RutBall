#include "Tools.h"
#include<ctime>
#include "Building.h"
#include "Texture.h"


Building::Building(Point center,double size, int type,double angleOfRotation)
:Drawable(center),size(size),type(type),angleOfRotation(angleOfRotation)
{
	
	int mytime = rand()%3;
	Texture tex=Texture::GetInstance();
}


void Building::Draw() 
{
	switch(this->type) {
		case 1:
			{
				double w=0.25,h=3.1; 
				model1(w,h);
				break;
			} 
		case 2:
			{
				double w=0.25,h=0.75; 
				model1(w,h);
				break;
			} 
		case 3:
			{
				double w=0.45,h=0.25; 

				model1(w,h);
				break;

			} 
	}
}
void Building::model1(double w, double h) 
{
	Texture tex=Texture::GetInstance();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.wallTex1);	
	glPushMatrix();
	glTranslatef(this->center.x, this->center.y+h*size, this->center.z);
	glRotated(this->angleOfRotation,0, 1, 0);
	
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	{
		// Top face (y = 1.0f)
		// Define vertices in counter-clockwise (CCW) order with normal pointing out
		glVertex3f( w*size, h*size, -w*size);
		glVertex3f( -w*size, h*size, -w*size);
		glVertex3f( -w*size, h*size, w*size);
		glVertex3f( w*size, h*size, w*size);
	}
	glEnd();
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	{
		// Bottom face (y = -1.0f)
		glVertex3f( w*size, -h*size, w*size);
		glVertex3f( -w*size, -h*size, w*size);
		glVertex3f( -w*size, -h*size, -w*size);
		glVertex3f( w*size, -h*size, -w*size);
	}
	glEnd();
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	{
		// Front face  (z = 1.0f)
		glTexCoord2f(2.0, 2.0); glVertex3f( w*size, h*size, w*size);
		glTexCoord2f(0.0, 2.0); glVertex3f( -w*size, h*size, w*size);
		glTexCoord2f(0.0, 0.0); glVertex3f( -w*size, -h*size, w*size);
		glTexCoord2f(2.0, 0.0); glVertex3f( w*size, -h*size, w*size);
	}
	glEnd();
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	{
		// Right face (x = 1.0f)
		glTexCoord2f(0.0, 2.0); glVertex3f( w*size, h*size, -w*size);
		glTexCoord2f(2.0, 2.0); glVertex3f( w*size, h*size, w*size);
		glTexCoord2f(2.0, 0.0); glVertex3f( w*size, -h*size, w*size);
		glTexCoord2f(0.0, 0.0); glVertex3f( w*size, -h*size, -w*size);
	}
	glEnd();
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	{
		// Left face (x = -1.0f)
		glTexCoord2f(0.0, 2.0); glVertex3f( -w*size, h*size, w*size);
		glTexCoord2f(2.0, 2.0); glVertex3f( -w*size, h*size, -w*size);
		glTexCoord2f(2.0, 0.0); glVertex3f( -w*size, -h*size, -w*size);
		glTexCoord2f(0.0, 0.0); glVertex3f( -w*size, -h*size, w*size);
	}
	glEnd();

//	glBindTexture(GL_TEXTURE_2D, tex.wallTex2);
	glBegin(GL_QUADS);
	{
		// Back face (z = -1.0f)
		glTexCoord2f(2.0, 0.0); glVertex3f( w*size, -h*size, -w*size);
		glTexCoord2f(0.0, 0.0); glVertex3f( -w*size, -h*size, -w*size);
		glTexCoord2f(0.0, 2.0); glVertex3f( -w*size, h*size, -w*size);
		glTexCoord2f(2.0, 2.0); glVertex3f(w*size, h*size, -w*size);
	}
	glEnd();  // End of drawing color-cube
	glPopMatrix();
	glDisable(GL_TEXTURE_2D); 
}

Building::~Building(void)
{
}
