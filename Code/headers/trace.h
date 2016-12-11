#pragma once
#include "includes.h"
#include "structures.h"
#include "conversion.h"
#include "trajet.h"

trace * createTrace(void);
trace * initTrace(long parDate, point parCoord, trace * parPrec, trace * parSuiv);
void afficheTrace(trace * parT);

