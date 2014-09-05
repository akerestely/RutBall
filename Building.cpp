#include "Building.h"
#include "Tools.h"
#include <glut.h>

Building::Building(Point center,double size, int type)
:Drawable(center),size(size),type(type)
{
}
void Building::loadTexture() 
{
	char* buffer = Tools::esLoadTGA("wall.tga", &width, &height);
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
   free(buffer);
}
void Building::Draw() 
{
	switch(this->type) {
		case 1:
			{
				double w=0.25,h=0.45; 
				model1(w,h);
			} 
		case 2:
			{
				double w=0.25,h=0.25; 
				model1(w,h);
			} 
		case 3:
			{
				double w=0.45,h=0.25; 

				model1(w,h);
				
			} 
	}
}
void Building::model1(double w, double h) 
{

   glBindTexture(GL_TEXTURE_2D, texName);	
	glPushMatrix();
	glTranslatef(this->center.x, this->center.y+h*size, this->center.z);
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	  glVertex3f( w*size, h*size, -w*size);
	  glVertex3f( -w*size, h*size, -w*size);
	  glVertex3f( -w*size, h*size, w*size);
	  glVertex3f( w*size, h*size, w*size);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	  glVertex3f( w*size, -h*size, w*size);
	  glVertex3f( -w*size, -h*size, w*size);
	  glVertex3f( -w*size, -h*size, -w*size);
	  glVertex3f( w*size, -h*size, -w*size);
     
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
	  glVertex3f( w*size, h*size, w*size);
	  glVertex3f( -w*size, h*size, w*size);
	  glVertex3f( -w*size, -h*size, w*size);
	  glVertex3f( w*size, -h*size, w*size);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	  glVertex3f( w*size, -h*size, -w*size);
	  glVertex3f( -w*size, -h*size, -w*size);
	  glVertex3f( -w*size, h*size, -w*size);
	  glVertex3f(w*size, h*size, -w*size);

 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue

	  glVertex3f( -w*size, h*size, w*size);
	  glVertex3f( -w*size, h*size, -w*size);
	  glVertex3f( -w*size, -h*size, -w*size);
	  glVertex3f( -w*size, -h*size, w*size);
    
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	  glVertex3f( w*size, h*size, -w*size);
	  glVertex3f( w*size, h*size, w*size);
	  glVertex3f( w*size, -h*size, w*size);
	  glVertex3f( w*size, -h*size, -w*size);
   glEnd();  // End of drawing color-cube
   glPopMatrix();
 
}


Building::~Building(void)
{
}
