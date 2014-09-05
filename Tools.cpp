#include "Tools.h"

Tools::Tools(void)
{
}
int Tools::ReadNodesFromXML(char *fileName, std::vector<Node> &nodes)
{
	char *buffer = new char[200];
	char *tag = new char[100];
    int id; 
	double longit, latit;
	FILE *fo = fopen(fileName, "r");
	if (fo == NULL)
		return 0;
	try
	{
		fgets(buffer, 200, fo);
		fscanf(fo, "%*s%*[^=]%*c%*c%[^\">]s", buffer);
		fscanf(fo, "%*s%s", buffer);
		sprintf(tag, "%c/%s", buffer[0], buffer + 1);

		fgets(buffer, 200, fo);
		fgets(buffer, 200, fo);
		while(!strstr(buffer, tag))
		{		
			strcpy(buffer, strstr(buffer, "=\""));
			sscanf(buffer, "%*c%*c%d", &id);
			strcpy(buffer, strstr(buffer+2, "=\""));
			sscanf(buffer, "%*c%*c%lf", &longit);
			strcpy(buffer, strstr(buffer+2, "=\""));
			sscanf(buffer, "%*c%*c%lf", &latit);
			
			nodes.push_back(Node(id, Point(latit, 0, longit)));
			fgets(buffer, 200, fo);
		}
	}
	catch(...)
	{
		return 0;
	}
	delete []buffer;
	delete []tag;
	fclose(fo);
	return 1;
}
char* Tools::esLoadTGA(char *fileName, double *width, double *height)
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
Tools::~Tools(void)
{
}
