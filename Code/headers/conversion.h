#pragma once
#include "includes.h"
#include "structures.h"
#include "config.h"

void lambert93ToGPS(double * x, double * y);
point * kmToGPS(const point parD, double parLat);
double convertToRad(const double par);
double GPStoKm(const point parP1, const point parP2);
struct tm * timestampToReadable(const long parDate);
char * timestampToString(const long parDate);
