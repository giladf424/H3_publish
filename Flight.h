#ifndef __FLIGHT__
#define __FLIGHT__

#include "AirportManager.h"
#include "Date.h"
#include "Plane.h"


typedef struct
{
	char	sourceCode[IATA_LENGTH + 1];
	char	destCode[IATA_LENGTH + 1];
	Plane	flightPlane;
	Date	date;
}Flight;

void	initFlight(Flight* pFlight, Plane* thePlane,const AirportManager* pManager);
int		isFlightFromSourceAirport(const Flight* pFlight, const char* code);
int		isFlightToDestAirport(const Flight* pFlight, const char* code);
void	printFlight(const void* pFlight);
Airport*	setAiportToFlight(const AirportManager* pManager, const char* msg);
int		isPlaneTypeInFlight(const Flight* pFlight, ePlaneType type);
int		compareFlightsByDate(const void* v1, const void* v2);
int		compareFlightsBySrcCode(const void* v1, const void* v2);
int		compareFlightsByDstCode(const void* v1, const void* v2);
void	freeFlightPtr(void** pFlight);
int		writeFlightToBFile(FILE* fp, Flight* f);
int		writeFlightArrToBFile(FILE* fp, Flight** arr, int count);

#endif
