#include "Texture.h"
#include "Card.h"


Card::Card(Point center)
:Drawable(center)
{
	angle=0.;
}

Card::~Card(void)
{
}

void Card::Draw()
{
	
	angle+=1;
	Texture tex=Texture::GetInstance();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex.cardTex);
	glPushMatrix();
	glTranslatef(center.x,center.y,center.z);
	glRotatef(angle, 0., center.y, 0.);
	

	glBegin(GL_QUADS);  
	glColor3f(1.0f, 1.0f, 1.0f);  
	glTexCoord2f(0.0,0.0);
	glVertex3f( center.x-WIDTH/2, center.y,0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(center.x+WIDTH/2, center.y,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(center.x+WIDTH/2, center.y+HEIGHT,  0);
	glTexCoord2f(0.0,1.0);
	glVertex3f( center.x-WIDTH/2, center.y+HEIGHT,  0);
	glEnd();
	
	double distanceToGroundUnit=center.y/11;
	glPushMatrix();
	glTranslatef(0.,8*distanceToGroundUnit,0.);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex.ballTex[0]);
	glutSolidSphere(0.20,30,10);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.,4*distanceToGroundUnit,0.);
	glutSolidSphere(0.10,30,10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.,1*distanceToGroundUnit,0.);
	glutSolidSphere(0.05,30,10);
	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}