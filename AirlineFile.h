#pragma once
#ifndef __AirlineFile__
#define __AirlineFile__
#include "Airline.h"

int saveAirlineToFile(const Airline* pComp, const char* fileName);
int readFlightArrFromBFile(FILE* fp, Airline* pComp, AirportManager* pManager);
int createPlaneArr(Airline* pComp);
int createFlightArr(Airline* pComp);
int initAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName);

#endif // !__AirlineFile__
