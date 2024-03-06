#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AirportManager.h"
#include "General.h"

int	initManager(AirportManager* pManager)
{
	LIST list;
	if (!L_init(&list)) {
		return 0;
	}
	pManager->airports = list;
	return 1;
}

int	addAirport(AirportManager* pManager)
{
	Airport* pPort = (Airport*)malloc(sizeof(Airport));
	if (!pPort)
		return 0;

	//LIST lst = pManager->airports;
	//NODE* pNode = &lst.head;

	if(!initAirport(pPort, pManager))
	{
		freeAirport(pPort);
		free(pPort);
		return 0;
	}

	if (!addAirportToCorrecPlace(pManager, pPort))
	{
		freeAirport(pPort);
		free(pPort);
		return 0;
	}
	Airport* p = (Airport*) pManager->airports.head.next->key;
	printf("%s\n", p->code);
	printf("%s\n", p->name);
	printf("%s\n", p->country);

	return 1;
}

int addAirportToCorrecPlace(AirportManager* pManager, Airport* pPort)
{
	NODE* pNode = &pManager->airports.head;

	if(pNode->next != NULL)
	{
		while(pNode->next != NULL)
		{
			Airport* p = (Airport*) pNode->next->key;
			if(strcmp(p->code, pPort->code) > 0)
			{
				break;
			}
			pNode = pNode->next;
		}
	}

	if (!L_insert(pNode, pPort))
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
	if (pManager->airports.head.next == NULL)
	{
		return NULL;
	}
	else {
		NODE* p = L_find(&(pManager->airports.head), code, isNotAirportCode);
		if (!p)
		{
			return NULL;
		}
		else {
			return p->key;
		}
	}
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
	while(p->next != NULL)
	{
		count++;
		p = p->next;
	}
	return count;
}