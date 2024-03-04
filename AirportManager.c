#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AirportManager.h"
#include "General.h"

int	initManager(AirportManager* pManager)
{
	LIST list = { NULL, NULL };
	if (!L_init(&list)) {
		return 0;
	}
	pManager->airports = list;
	return 1;
}

int	addAirport(AirportManager* pManager)
{
	Airport* pPort = (Airport*)calloc(1, sizeof(Airport));
	if (!pPort)
		return 0;

	if(!initAirport(pPort, pManager))
	{
		freeAirport(pPort);
		free(pPort);
		return 0;
	}


	if (!L_insert(&pManager->airports.head, pPort))
	{
		freeAirport(pPort);
		free(pPort);
		return 0;
	}

	return 1;
}

int  initAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	return initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
	NODE* p = &(pManager->airports.head);
	return L_find(p, code, isAirportCode);
}

int checkUniqeCode(const char* code, const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}

void	printAirports(const AirportManager* pManager)
{
	printf("there are %d airports\n", getAirportAmount(pManager));
	L_print(&pManager->airports, printAirport);
}

void	freeManager(AirportManager* pManager)
{
	freeAirportArr(pManager);
}

void	freeAirportArr(AirportManager* pManager)
{
	L_free(&pManager->airports, freeAirport);
}

int getAirportAmount(const AirportManager* pManager)
{
	int count = 0;
	NODE* p = &(pManager->airports.head);
	while(p != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}