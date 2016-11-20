#pragma once
#include "includes.h"
#include "structures.h"

void lambert93ToGPS(double * x, double * y);
struct tm * timestampToReadable(const long parDate);
char * timestampToString(const long parDate);
