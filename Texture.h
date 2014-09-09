#pragma once
#include <vector>
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
	GLuint ballTex[5];
	GLuint cardTex[2];
	GLuint skyCube[6];
	GLuint roadTex;
	GLuint textures[10];
	GLuint doorTex;
	GLuint winTex;
};
