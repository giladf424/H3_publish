#include <stdio.h>
#include <stdlib.h>
#include "Airline.h"
#include "AirportManager.h"
#include "General.h"
#include "AirlineFile.h"
int initManagerAndAirline(AirportManager* pManager, Airline* pCompany);
typedef enum 
{ 
	eAddAirport,eAddPlane, eAddFlight, ePrintCompany, ePrintAirports,
	ePrintFlightsPlaneType,eSortFlights,eFindFlights, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Airport","Add Plane","Add Flight",
								"Print Airline", "Print all Airports",
								"Print all flights with plane type", "Sort flights", "Find flight"};

#define EXIT			-1
int menu();

int main()
{
	AirportManager	manager;
	Airline			company;
	
	if (!initManagerAndAirline(&manager, &company))
		exit(1);

	int option;
	int stop = 0;

	
	do
	{
		option = menu();
		switch (option)
		{
		case eAddPlane:
			if (!addPlane(&company))
				printf("Error adding plane\n");
			break;

		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			printAirports(&manager);
			break;

		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintFlightsPlaneType:
			doPrintFlightsWithPlaneType(&company);
			break;

		case eSortFlights:
			sortFlight(&company);
			break;

		case eFindFlights:
			findFlight(&company);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	saveManagerToFile(&manager, "authority_airport.txt");
	saveAirlineToFile(&company, "airline.bin");

	freeManager(&manager);
	freeCompany(&company);
	
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for(int i = 0 ; i < eNofOptions ; i++)
		printf("%d - %s\n",i,str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

int initManagerAndAirline(AirportManager* pManager, Airline* pCompany)
{
	int res = initManager(pManager, "authority_airport.txt");
	if (res == 0)
	{
		printf("Error init airport manager\n");
		return 0;
	}
	else if (res == 1)
	{
		res = initAirlineFromFile(pCompany, pManager, "airline.bin");
		if (res == 0)
			initAirline(pCompany);
		return 1;
	}
	else
		initAirline(pCompany);
	return 1;
}