#pragma once
#include "includes.h"
#include "structures.h"
#include "config.h"

void lambert93ToGPS(double * x, double * y);
point * kmToGPS(const point parD, double parLat);
struct tm * timestampToReadable(const long parDate);
char * timestampToString(const long parDate);
