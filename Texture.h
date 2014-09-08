#pragma once
#include <stdlib.h> 
#include <iostream>
#include <glut.h>

class Texture
{
private:
	char* esLoadTGA(char *fileName, double *width, double *height);
	Texture();
public:
	static Texture& GetInstance();
	GLuint wallTex1;
	GLuint wallTex2;
	GLuint ball;
	GLuint skyCube[6];
};
