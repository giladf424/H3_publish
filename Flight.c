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
	const Flight* f1 = (const Flight*)v1;
	const Flight* f2 = (const Flight*)v2;
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
	const Flight* f1 = (const Flight*)v1;
	const Flight* f2 = (const Flight*)v2;
	return strcmp((const char*)f1->sourceCode, (const char*)f2->sourceCode);
}

int compareFlightsByDstCode(const void* v1, const void* v2)
{
	const Flight* f1 = (const Flight*)v1;
	const Flight* f2 = (const Flight*)v2;
	return strcmp(f1->destCode, f2->destCode);
}


void	printFlight(const Flight* pFlight)
{
	printf("Flight From %s To %s\t",pFlight->sourceCode, pFlight->destCode);
	printDate(&pFlight->date);
	printf("\t");
	printPlane(&pFlight->flightPlane);
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
