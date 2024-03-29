#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"
#include "General.h"
#include "Files.h"


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

int writeFlightToBFile(FILE* fp, const Flight* pF)
{
	if (writeCharToBFile(fp, IATA_LENGTH, pF->sourceCode, "Error! flight source code wasn't written to file\n") != 1)
		return 0;
	if (writeCharToBFile(fp, IATA_LENGTH, pF->destCode, "Error! flight destination code wasn't written to file\n") != 1)
		return 0;
	if (writeIntToBFile(fp, pF->flightPlane.serialNum, "Error! flight plane serial number wasn't written to file\n") != 1)
		return 0;
	if (writeDateToBFile(fp, &pF->date) != 1)
		return 0;
	return 1;
}

int readFlightFromBFile(FILE* fp, Flight* pF, const AirportManager* pManager, Plane* planeArr, int planeCount)
{
	int sNum;
	memset(pF, 0, sizeof(Flight));
	if (readCharFromBFile(fp, pF->sourceCode, IATA_LENGTH, "Error! flight source code wasn't read from file\n") != 1)
		return 0;
	if (findAirportByCode(pManager, pF->sourceCode) == NULL)
	{
		printf("The airport with %s source code isn't in manager\n", &pF->sourceCode);
		return 0;
	}
	if (readCharFromBFile(fp, pF->destCode, IATA_LENGTH, "Error! flight dest code wasn't read from file\n") != 1)
		return 0;
	if (findAirportByCode(pManager, pF->destCode) == NULL)
	{
		printf("The airport with %s source code isn't in manager\n", &pF->destCode);
		return 0;
	}
	if (readIntFromBFile(fp, &sNum, "Error! flight serial number wasn't read from file\n") != 1)
		return 0;
	Plane* pTmp = findPlaneBySN(planeArr, planeCount, sNum);
	if (pTmp == NULL)
	{
		printf("The plane with %d serial number isn't in the company", sNum);
		return 0;
	}
	pF->flightPlane.serialNum = pTmp->serialNum;
	pF->flightPlane.type = pTmp->type;
	if (readDateFromBFile(fp, &pF->date) != 1)
		return 0;
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

void freeFlightPtr(void** pFlight)
{
	free(*pFlight);
}