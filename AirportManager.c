#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AirportManager.h"
#include "General.h"

int	initManagerFile(AirportManager* pManager)
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

int saveManagerToFile(const AirportManager* pManager, const char* fileName)
{
	FILE* file = fopen(fileName, "w");
	if (!file)
	{
		printf("Error open file for writing\n");
		return 0;
	}

	NODE* p = &(pManager->airports.head);
	fprintf(file, "%d\n", getAirportAmount(pManager));
	while(p->next != NULL)
	{
		p = p->next;
		Airport* port = (Airport*)p->key;
		fprintf(file, "%s\n%s\n%s\n", port->name, port->country, port->code);
	}

	fclose(file);
	return 1;
}

int initManager(AirportManager* pManager, const char* fileName)
{
	FILE* file = fopen(fileName, "r");
	if (!file)
	{
		printf("Error open file for reading\n");
		initManagerFile(pManager);
		return 0;
	}

	if (!initManagerFile(pManager))
	{
		fclose(file);
		return 0;
	}

	int count;
	fscanf(file, "%d", &count);
	fgetc(file);
	char temp[MAX_STR_LEN];
	for (int i = 0; i < count; i++)
	{
		Airport* port = (Airport*)malloc(sizeof(Airport));
		if (!port)
		{
			fclose(file);
			freeManager(pManager);
			return 0;
		}

		port->name = malloc(strlen(temp) * sizeof(char));
		port->country = malloc(strlen(temp) * sizeof(char));
		
		//fgets(temp, MAX_STR_LEN, file);
		//int nameLen = strlen(temp);
		//strcpy(port->name, temp);
		//port->name[nameLen] = '\0';

		//fgets(temp, MAX_STR_LEN, file);
		//int countryLen = strlen(temp);
		//strcpy(port->country, temp);
		//port->country[countryLen] = '\0';

		if(!port->name || !port->country)
		{
			fclose(file);
			return 0;
		}

		fscanf(file, "%[^\n]", port->name);
		fgetc(file);
		fscanf(file, "%[^\n]", port->country);
		fgetc(file);
		fscanf(file, "%s", port->code);
		fgetc(file);

		if (!addAirportToCorrecPlace(pManager, port))
		{
			fclose(file);
			return 0;
		}
	}

	fclose(file);
	return 1;
}