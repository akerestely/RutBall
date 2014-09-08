#include "Tools.h"

Tools::Tools(void)
{
}
int Tools::ReadNodesFromXML(char *fileName, std::map<int,Node>& nodes)
{
	char *buffer = new char[200];
	char *tag = new char[100];
	int id; 
	double longit, latit;
	FILE *fo;
	fopen_s(&fo,fileName, "r");
	if (fo == NULL)
		return 0;
	int changes = 0;
	try
	{
		fgets(buffer, 200, fo);
		fscanf_s(fo, "%*s%*[^=]%*c%*c%[^\">]s", buffer);
		fscanf_s(fo, "%*s%s", buffer);
		fgets(buffer, 200, fo);
		fgets(buffer, 200, fo);
		while(!strstr(buffer, tag))
		{		
			strcpy_s(buffer, sizeof(strstr(buffer, "=\"")), strstr(buffer, "=\""));
			changes += sscanf_s(buffer, "%*c%*c%d", &id);
			strcpy_s(buffer, sizeof(strstr(buffer + 2, "=\"")), strstr(buffer+2, "=\""));
			changes += sscanf_s(buffer, "%*c%*c%lf", &longit);
			strcpy_s(buffer, sizeof(strstr(buffer + 2, "=\"")), strstr(buffer + 2, "=\""));
			changes += sscanf_s(buffer, "%*c%*c%lf", &latit);
			if (changes != 3)
				return 0;
			changes = 0;
			//nodes.push_back(Node(id, Point(latit, 0, longit)));
			nodes[id]=Node(id,Point(latit,0,longit));
			fgets(buffer, 200, fo);
		}
	}
	catch(...)
	{
		return 0;
	}

	int from, to;
	fscanf_s(fo, "%*s%s", buffer);
	sprintf_s(tag, sizeof(tag),"%c/%s", buffer[0], buffer + 1);
	fgets(buffer, 200, fo);
	changes = 0;
	while(!strstr(buffer, tag))
	{ 
		strcpy_s(buffer, sizeof(strstr(buffer, "=\"")), strstr(buffer, "=\""));
		changes += sscanf_s(buffer, "%*c%*c%d", &from);
		strcpy_s(buffer, sizeof(strstr(buffer + 2, "=\"")), strstr(buffer + 2, "=\""));
		changes += sscanf_s(buffer, "%*c%*c%d", &to);
		if (changes != 2)
			return 0;
		changes = 0;
		nodes[from].getDestinations().push_back(to);
		nodes[to].getDestinations().push_back(from);
		fgets(buffer, 200, fo);
	}
	delete []buffer;
	delete []tag;
	fclose(fo);
	return 1;
}

Tools::~Tools(void)
{
}


typedef struct
{
        unsigned char IdSize,
                MapType,
                ImageType;
        unsigned short PaletteStart,
                PaletteSize;
        unsigned char PaletteEntryDepth;
        unsigned short X,
                Y,
                Width,
                Height;
        unsigned char ColorDepth,
                Descriptor;

} TGA_HEADER;

char*  Tools::esLoadTGA ( char *fileName, int *width, int *height )
{
   char *buffer = NULL;
   FILE *f;
   unsigned char tgaheader[12];
   unsigned char attributes[6];
   unsigned int imagesize;
   fopen_s(&f,fileName, "rb");
   if(f == NULL) return NULL;
   if(fread(&tgaheader, sizeof(tgaheader), 1, f) == 0)
   {
       fclose(f);
       return NULL;
   }

   if(fread(attributes, sizeof(attributes), 1, f) == 0)
   {
       fclose(f);
       return 0;
   }

   *width = attributes[1] * 256 + attributes[0];
   *height = attributes[3] * 256 + attributes[2];
   imagesize = attributes[4] / 8 * *width * *height;
   buffer =(char*) malloc(imagesize);
   if (buffer == NULL)
   {
       fclose(f);
       return 0;
   }

   if(fread(buffer, 1, imagesize, f) != imagesize)
   {
       free(buffer);
       return NULL;
   }
   fclose(f);
   return buffer;
}
