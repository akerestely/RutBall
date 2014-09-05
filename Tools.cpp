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
	FILE *fo = fopen(fileName, "r");
	if (fo == NULL)
		return 0;
	int changes = 0;
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
			changes += sscanf(buffer, "%*c%*c%d", &id);
			strcpy(buffer, strstr(buffer+2, "=\""));
			changes += sscanf(buffer, "%*c%*c%lf", &longit);
			strcpy(buffer, strstr(buffer+2, "=\""));
			changes += sscanf(buffer, "%*c%*c%lf", &latit);
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
	fscanf(fo, "%*s%s", buffer);
	sprintf(tag, "%c/%s", buffer[0], buffer + 1);
	fgets(buffer, 200, fo);
	changes = 0;
	while(!strstr(buffer, tag))
	{ 

		strcpy(buffer, strstr(buffer, "=\""));
		changes += sscanf(buffer, "%*c%*c%d", &from);
		strcpy(buffer, strstr(buffer+2, "=\""));
		changes += sscanf(buffer, "%*c%*c%d", &to);
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
