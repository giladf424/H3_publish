#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "Airport.h"
#include "List.h"

typedef struct
{
	LIST	airports;
}AirportManager;

int		initManagerFile(AirportManager* pManager);

int		initManager(AirportManager* pManager, const char* fileName);

int		addAirport(AirportManager* pManager);

int		initAirport(Airport* pPort, AirportManager* pManager);

Airport* findAirportByCode(const AirportManager* pManager, const char* code);

int		checkUniqeCode(const char* code, const AirportManager* pManager);

void	printAirports(const AirportManager* pManager);

void	freeManager(AirportManager* pManager);

void	freeAirportArr(AirportManager* pManager);

int		getAirportAmount(const AirportManager* pManager);

int		addAirportToCorrecPlace(AirportManager* pManager, Airport* pPort);

int		saveManagerToFile(const AirportManager* pManager, const char* fileName);


#endif