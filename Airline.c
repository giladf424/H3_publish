#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Airline.h"
#include "Airport.h"
#include "General.h"

void	initAirline(Airline* pComp)
{
	//printf("-----------  Init Airline\n");
	pComp->name = getStrExactName("Enter Airline name");
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	pComp->planeArr = NULL;
	pComp->planeCount = 0;
	pComp->type = eNotSorted;
}

int	addFlight(Airline* pComp,const AirportManager* pManager)
{
	if (getAirportAmount(pManager) < 2)
	{
		printf("There are not enough airport to set a flight\n");
		return 0;
	}
	if(pComp->planeCount == 0)
	{
		printf("There is no plane in company\n");
		return 0;
	}

	Flight* pFlight = (Flight*)calloc(1, sizeof(Flight));
	if (!pFlight)
		return 0;
	
	Plane* thePlane = FindAPlane(pComp);
	printAirports(pManager);
	initFlight(pFlight, thePlane,pManager);

	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	if (!pComp->flightArr)
	{
		free(pFlight);
		return 0;
	}
	pComp->flightArr[pComp->flightCount] = pFlight;
	pComp->flightCount++;
	pComp->type = eNotSorted;
	return 1;
}

int		addPlane(Airline* pComp)
{
	pComp->planeArr = (Plane*)realloc(pComp->planeArr, (pComp->planeCount + 1) * sizeof(Plane));
	if (!pComp->planeArr)
		return 0;
	initPlane(&pComp->planeArr[pComp->planeCount], pComp->planeArr, pComp->planeCount);
	pComp->planeCount++;
	return 1;
}

Plane* FindAPlane(Airline* pComp)
{
	printf("Choose a plane from list, type its serial Number\n");
	printPlanesArr(pComp->planeArr,pComp->planeCount);
	int sn;
	Plane* temp = NULL;
	do {
		scanf("%d", &sn);
		temp = findPlaneBySN(pComp->planeArr,pComp->planeCount, sn);
		if (!temp)
			printf("No plane with that serial number! Try again!\n");
	} while (temp == NULL);
	 
	return temp;
}


void printCompany(const Airline* pComp)
{
	printf("Airline %s\n", pComp->name);
	printf("\n -------- Has %d planes\n", pComp->planeCount);
	printPlanesArr(pComp->planeArr, pComp->planeCount);
	printf("\n\n -------- Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
}

void	printFlightArr(Flight** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Flight*), printFlight);
}

void	printPlanesArr(Plane* arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Plane), printPlane);
}

void	doPrintFlightsWithPlaneType(const Airline* pComp)
{
	ePlaneType type = getPlaneType();
	int count = 0;
	printf("Flights with plane type %s:\n", GetPlaneTypeStr(type));
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isPlaneTypeInFlight(pComp->flightArr[i], type))
		{
			printFlight(&pComp->flightArr[i]);
			count++;
		}
	}
	if(count == 0)
		printf("Sorry - could not find a flight with plane type %s:\n", GetPlaneTypeStr(type));
	printf("\n");
}

void	freeFlightArr(Flight** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Flight*), freeFlightPtr);
}

void	freePlanes(Plane* arr, int size)
{
	for (int i = 0; i < size; i++)
		freePlane(&arr[i]);
}

void	freeCompany(Airline* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->planeArr);
	free(pComp->name);
}

void sortFlight(Airline* pComp)
{
	int type = getSortType();
	if (type == 1)
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsBySrcCode);
	else if(type == 2)
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsByDstCode);
	else
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsByDate);
	pComp->type = type;
}

int getSortType()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 1; i < eNofSortTypes; i++)
			printf("%d for %s\n", i, SortTypeStr[i]);
		scanf("%d", &option);
	} while (option < 1 || option > eNofPlaneTypes);
	return option;
}

void findFlight(const Airline* pComp)
{
	Date date;
	Flight f;
	Flight* pF;
	Flight** foundflight = NULL;
	char code[MAX_STR_LEN];

	switch (pComp->type)
	{
	case eNotSorted:
		printf("The flights array isn't sorted , sort it and try again.\n");
		return;
		break;
	case eSrcCode:
		getAirportCode(code);
		strcpy(f.sourceCode,code);
		pF = &f;
		foundflight = (Flight**)bsearch(&pF, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsBySrcCode);
		break;
	case eDstCode:
		getAirportCode(code);
		strcpy(f.destCode, code);
		pF = &f;
		foundflight = (Flight**)bsearch(&pF, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsByDstCode);
		break;
	case eDate:
		getCorrectDate(&date);
		f.date = date;
		pF = &f;
		foundflight = (Flight**)bsearch(&pF, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareFlightsByDate);
		break;
	}
	if (!foundflight)
		printf("The flight you were looking for does not exist\n");
	else
		printFlight(foundflight);
}
