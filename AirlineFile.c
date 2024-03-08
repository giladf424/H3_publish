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
	if (writeStringToBFile(fp, pComp->name, "Error! company name wasn't written to file\n") != 1)
	{
		fclose(fp);
		return 0;
	}
	if (writeIntToBFile(fp, pComp->planeCount, "Error! plane count wasn't written to file\n") != 1)
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
	if (writeIntToBFile(fp, pComp->flightCount, "Error! flight count wasn't written to file\n") != 1)
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
