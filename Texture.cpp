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


	buffer = esLoadTGA("Texture/football.tga",&tWidth,&tHeight);
	glGenTextures ( 1, ballTex);
	glBindTexture ( GL_TEXTURE_2D, ballTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	

	buffer = esLoadTGA("Texture/basketball.tga",&tWidth,&tHeight);
	glGenTextures ( 1, ballTex+1);
	glBindTexture ( GL_TEXTURE_2D, ballTex[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );


	buffer = esLoadTGA("Texture/beachball.tga",&tWidth,&tHeight);
	glGenTextures ( 1, ballTex+2);
	glBindTexture ( GL_TEXTURE_2D, ballTex[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	
	buffer = esLoadTGA("Texture/tennisball.tga",&tWidth,&tHeight);
	glGenTextures ( 1, ballTex+3);
	glBindTexture ( GL_TEXTURE_2D, ballTex[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );


	buffer = esLoadTGA("Texture/discoball.tga",&tWidth,&tHeight);
	glGenTextures ( 1, ballTex+4);
	glBindTexture ( GL_TEXTURE_2D, ballTex[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );
	
	buffer = esLoadTGA("Texture/route.tga",&tWidth,&tHeight);
	glGenTextures ( 1, cardTex);
	glBindTexture ( GL_TEXTURE_2D, cardTex[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

	buffer = esLoadTGA("Texture/woodTexture.tga",&tWidth,&tHeight);
	glGenTextures ( 1, cardTex+1);
	glBindTexture ( GL_TEXTURE_2D, cardTex[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP); 
	glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tWidth, tHeight, 0,  GL_BGR_EXT, GL_UNSIGNED_BYTE, buffer ); 
	free ( buffer );

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