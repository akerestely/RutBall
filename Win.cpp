#include "Texture.h"
#include "Win.h"
#define	DOORWIDTH 1.5
#define DOORHEIGHT 4

Win::Win(Point center)
     :Drawable(center)
{
	this->win=false;
}

Win::~Win(void)
{

}

void Win::SetWin(bool win){
	this->win=win;
}

void Win::Draw(){

	Texture tex=Texture::GetInstance();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex.winTex);
	glPushMatrix();
	glRotated(10, 0, 1, 0);
	glTranslatef(center.x,center.y,center.z);
	
	if(win==true && dx<=DOORWIDTH){
		dx+=0.015;
	}
	
	glPushMatrix();
	if(win==true)
	{
		glBegin(GL_QUADS);  
		glTexCoord2f(0.0,0.0);
		glVertex3f(-DOORWIDTH, -DOORHEIGHT/2, 0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(DOORWIDTH, -DOORHEIGHT/2,0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(DOORWIDTH, DOORHEIGHT/2,  0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-DOORWIDTH, DOORHEIGHT/2,  0);
		glEnd();
	}
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);
	//begin drawing the doors
	tex=Texture::GetInstance();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex.doorTex);

	glPushMatrix();
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0);
	glVertex3f(-2*DOORWIDTH, -DOORHEIGHT/2, 0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(-DOORWIDTH, -DOORHEIGHT/2,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(-DOORWIDTH, DOORHEIGHT/2,  0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-2*DOORWIDTH, DOORHEIGHT/2,  0);
	glEnd();
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	if(win==true)
		glTranslatef(-dx, 0, 0);
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0);
	glVertex3f(-DOORWIDTH, -DOORHEIGHT/2, 0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(0, -DOORHEIGHT/2,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(0, DOORHEIGHT/2,  0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-DOORWIDTH, DOORHEIGHT/2,  0);
	glEnd();
	glPopMatrix();
	//glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	if(win==true)
		glTranslatef(dx, 0, 0);
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0);
	glVertex3f(0, -DOORHEIGHT/2, 0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(DOORWIDTH, -DOORHEIGHT/2,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(DOORWIDTH, DOORHEIGHT/2,  0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(0, DOORHEIGHT/2,  0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glBegin(GL_QUADS);  
	glTexCoord2f(0.0,0.0);
	glVertex3f(DOORWIDTH, -DOORHEIGHT/2, 0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(2*DOORWIDTH, -DOORHEIGHT/2,0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(2*DOORWIDTH, DOORHEIGHT/2,  0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(DOORWIDTH, DOORHEIGHT/2,  0);
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

