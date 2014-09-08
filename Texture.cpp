#include "Texture.h"


Texture::Texture(void)
{
	double tWidth, tHeight;
	char* buffer ;

	buffer = esLoadTGA("Texture/7.tga", &tWidth, &tHeight);
	glGenTextures(1, &wallTex1);
	glBindTexture(GL_TEXTURE_2D, wallTex1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/5.tga", &tWidth, &tHeight);
	glGenTextures(2, &wallTex2);
	glBindTexture(GL_TEXTURE_2D, wallTex2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);

	buffer = esLoadTGA("Texture/Skybox-000.tga", &tWidth, &tHeight);
	glGenTextures(3, skyCube);
	glBindTexture(GL_TEXTURE_2D, skyCube[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
	buffer = esLoadTGA("Texture/Skybox-001.tga", &tWidth, &tHeight);
	glGenTextures(4, skyCube+1);
	glBindTexture(GL_TEXTURE_2D, skyCube[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
	buffer = esLoadTGA("Texture/Skybox-002.tga", &tWidth, &tHeight);
	glGenTextures(5, skyCube+2);
	glBindTexture(GL_TEXTURE_2D, skyCube[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
	buffer = esLoadTGA("Texture/Skybox-003.tga", &tWidth, &tHeight);
	glGenTextures(6, skyCube+3);
	glBindTexture(GL_TEXTURE_2D, skyCube[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
	buffer = esLoadTGA("Texture/Skybox-004.tga", &tWidth, &tHeight);
	glGenTextures(7, skyCube+4);
	glBindTexture(GL_TEXTURE_2D, skyCube[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
	buffer = esLoadTGA("Texture/Skybox-005.tga", &tWidth, &tHeight);
	glGenTextures(8, skyCube+5);
	glBindTexture(GL_TEXTURE_2D, skyCube[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer);
	free(buffer);
}

char* Texture::esLoadTGA(char *fileName, double *width, double *height)
{
	 char *buffer = NULL;
	 FILE *f;
	 unsigned char tgaheader[12];
	 unsigned char attributes[6];
	 unsigned int imagesize;
	 fopen_s(&f, fileName, "rb");
	 if (f == NULL) return NULL;
	 if (fread(&tgaheader, sizeof(tgaheader), 1, f) == 0)
	 {
	  fclose(f);
	  return NULL;
	 }

	 if (fread(attributes, sizeof(attributes), 1, f) == 0)
	 {
	  fclose(f);
	  return 0;
	 }

	 *width = attributes[1] *256 + attributes[0];
	 *height = attributes[3] * 256 + attributes[2];
	 imagesize = attributes[4] / 8 * *width * *height;
	 buffer = (char*)malloc(imagesize);
	 if (buffer == NULL)
	 {
	  fclose(f);
	  return 0;
	 }

	 if (fread(buffer, 1, imagesize, f) != imagesize)
	 {
	  free(buffer);
	  return NULL;
	 }
	 fclose(f);
	 return buffer;
}
Texture& Texture::GetInstance()
{
	static Texture instance;
	return instance;
}