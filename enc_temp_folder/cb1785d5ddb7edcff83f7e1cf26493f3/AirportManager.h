#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "List.h"

typedef struct
{
	LIST	airports;
}AirportManager;

int		initManager(AirportManager* pManager);

int		addAirport(AirportManager* pManager);

int		initAirport(Airport* pPort, AirportManager* pManager);

Airport* findAirportByCode(const AirportManager* pManager, const char* code);

int		checkUniqeCode(const char* code, const AirportManager* pManager);

void	printAirports(const AirportManager* pManager);

void	freeManager(AirportManager* pManager);

void	freeAirportArr(AirportManager* pManager);

int getAirportAmount(const AirportManager* pManager);
#endif