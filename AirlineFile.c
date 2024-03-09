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
		printf("Error! file didn't open\n");
		return 0;
	}
	if (writeStringToBFile(fp, pComp->name, "Error! company name wasn't written to file") != 1)
	{
		fclose(fp);
		return 0;
	}
	if (writeIntToBFile(fp, pComp->planeCount, "Error! plane count wasn't written to file") != 1)
	{
		fclose(fp);
		return 0;
	}
	if (fwrite(pComp->planeArr, sizeof(Plane), pComp->planeCount, fp) != pComp->planeCount)
	{
		printf("Error! planes array wasn't written to file\n");
		fclose(fp);
		return 0;
	}
	if (writeIntToBFile(fp, pComp->flightCount, "Error! flight count wasn't written to file") != 1)
	{
		fclose(fp);
		return 0;
	}
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (writeFlightToBFile(fp, pComp->flightArr[i]) != 1)
		{
			fclose(fp);
			return 0;
		}
	}
	return 1;
}

int readFlightArrFromBFile(FILE* fp, Airline* pComp, AirportManager* pManager)
{
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (readFlightFromBFile(fp, pComp->flightArr[i], pManager, pComp->planeArr, pComp->planeCount) != 1)
			return 0;
	}
	return 1;
}

int createPlaneArr(Airline* pComp)
{
	pComp->planeArr = (Plane*)malloc(pComp->planeCount * sizeof(Plane));
	if (!pComp->planeArr)
	{
		printf("Memory alocation error!\n");
		return 0;
	}
	return 1;
}

int createFlightArr(Airline* pComp)
{
	if (pComp->flightCount == 0)
	{
		pComp->flightArr = NULL;
	}
	else {
		pComp->flightArr = (Flight**)malloc(pComp->flightCount * sizeof(Flight*));
		if (!pComp->flightArr)
		{
			printf("Memory alocation error!\n");
			return 0;
		}
	}

	for (int i = 0; i < pComp->flightCount; i++)
	{
		pComp->flightArr[i] = (Flight*)calloc(1, sizeof(Flight));
		if (!pComp->flightArr[i])
		{
			printf("Memory alocation error!\n");
			return 0;
		}
	}
	return 1;
}

int initAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName)
{
	FILE* fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error! file didn't open\n");
		return 0;
	}
	pComp->flightArr = NULL;
	pComp->type = eNotSorted;
	int len;
	if (readIntFromBFile(fp, &len, "Error! the company name length wasn't read from the file") != 1)
		return 0;
	pComp->name = (char*)malloc(len * sizeof(char));
	if (fread(pComp->name, sizeof(char), len, fp) != len)
	{
		printf("Error! company name wasn't read from file\n");
		free(pComp->name);
		fclose(fp);
		return 0;
	}
	if (readIntFromBFile(fp, &pComp->planeCount, "Error! plane count wasn't read from file") != 1)
	{
		free(pComp->name);
		fclose(fp);
		return 0;
	}
	if (createPlaneArr(pComp) != 1)
	{
		free(pComp->name);
		fclose(fp);
		return 0;
	}
	if (fread(pComp->planeArr, sizeof(Plane), pComp->planeCount, fp) != pComp->planeCount)
	{
		printf("Error! planes array wasn't read from file\n");
		free(pComp->name);
		free(pComp->planeArr);
		fclose(fp);
		return 0;
	}
	if (readIntFromBFile(fp, &pComp->flightCount, "Error! flight count wasn't read from file") != 1)
	{
		free(pComp->name);
		free(pComp->planeArr);
		fclose(fp);
		return 0;
	}
	if (createFlightArr(pComp) != 1)
	{
		free(pComp->name);
		free(pComp->planeArr);
		fclose(fp);
		return 0;
	}
	if (readFlightArrFromBFile(fp, pComp, pManager) != 1)
	{
		free(pComp->name);
		free(pComp->planeArr);
		free(pComp->flightArr);
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}
