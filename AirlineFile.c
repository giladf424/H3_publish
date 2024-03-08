#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AirlineFile.h"
#include "Files.h"

int saveAirlineToFile(const Airline* pComp, const char* fileName)
{
	FILE* fp = fopen(fileName, "wb");
	if (!fp)
	{
		printf("Error! the file didn't open");
		return 0;
	}
	if (writeStringToBFile(fp, pComp->name, "Error! company name wasn't written to file") != 1)
	{
		fclose(fp);
		return 0;
	}
	return 0;
}
