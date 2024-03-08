#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"


void	initFlight(Flight* pFlight,Plane* thePlane, const AirportManager* pManager)
{
	Airport* pPortOr = setAiportToFlight(pManager, "Enter code of origin airport:");
	strcpy(pFlight->sourceCode, pPortOr->code);
	int same;
	Airport* pPortDes;
	do {
		pPortDes = setAiportToFlight(pManager, "Enter code of destination airport:");
		same = isSameAirport(pPortOr, pPortDes);
		if (same)
			printf("Same origin and destination airport\n");
	} while (same);
	strcpy(pFlight->destCode, pPortDes->code);
	pFlight->flightPlane = *thePlane;
	getCorrectDate(&pFlight->date);
}

int		isFlightFromSourceAirport(const Flight* pFlight, const char* code)
{
	if (strcmp(pFlight->sourceCode, code) == 0)
		return 1;
		
	return 0;
}


int		isFlightToDestAirport(const Flight* pFlight, const char* code)
{
	if (strcmp(pFlight->destCode, code) == 0)
		return 1;

	return 0;


}

int		isPlaneTypeInFlight(const Flight* pFlight, ePlaneType type)
{
	return (pFlight->flightPlane.type == type);
}

int compareFlightsByDate(const void* v1, const void* v2)
{
	const Flight* f1 = *(const Flight**)v1;
	const Flight* f2 = *(const Flight**)v2;
	if (f1->date.year == f2->date.year)
	{
		if (f1->date.month == f2->date.month)
			return f1->date.day - f2->date.day;
		return f1->date.month - f2->date.month;
	}
	return f1->date.year - f2->date.year;
}

int compareFlightsBySrcCode(const void* v1, const void* v2)
{
	const Flight* f1 = *(const Flight**)v1;
	const Flight* f2 = *(const Flight**)v2;
	return strcmp(f1->sourceCode, f2->sourceCode);
}

int compareFlightsByDstCode(const void* v1, const void* v2)
{
	const Flight* f1 = *(const Flight**)v1;
	const Flight* f2 = *(const Flight**)v2;
	return strcmp(f1->destCode, f2->destCode);
}

int writeFlightToBFile(FILE* fp, Flight* f)
{
	if (!fp)
		return 0;
	int sLen = (int)strlen(f->sourceCode);
	int dLen = (int)strlen(f->destCode);
	if (fwrite(&sLen, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&f->sourceCode, sizeof(char), sLen, fp) != sLen)
		return 0;
	if (fwrite(&dLen, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&f->destCode, sizeof(char), dLen, fp) != dLen)
		return 0;
	if (fwrite(&f->flightPlane.serialNum, sizeof(int), 1, fp) != 1)
		return 0;
	if (fwrite(&f->date, sizeof(int), 3, fp) != 3)
		return 0;
	return 0;
}

int writeFlightArrToBFile(FILE* fp, Flight** arr, int count)
{
	if (!fp)
		return 0;
	if (fwrite(&count, sizeof(int), 1, fp) != 1)
		return 0;
	for (int i = 0; i < count; i++)
		writeFlightToBFile(fp, arr[i]);
	return 1;
}


void	printFlight(const void* pFlight)
{
	const Flight* pF = *(const Flight**)pFlight;
	printf("Flight From %s To %s\t",pF->sourceCode, pF->destCode);
	printDate(&pF->date);
	printf("\t");
	printPlane(&pF->flightPlane);
}

Airport* setAiportToFlight(const AirportManager* pManager, const char* msg)
{
	char code[MAX_STR_LEN];
	Airport* port;
	do
	{
		printf("%s\t", msg);
		getAirportCode(code);
		port = findAirportByCode(pManager, code);
		if (port == NULL)
			printf("No airport with this code - try again\n");
	} while (port == NULL);

	return port;
}
