#pragma once
#include "includes.h"
#include "structures.h"

trace * createTrace(void);
void initTrace(trace * parT, long parDate, point parCoord, trace * parPrec, trace * parSuiv);
trajet * initTrajet(void);
void ajoutTrace(trajet * parTr, trace * parT);
void afficheTrace(trace * parT);
void afficheTrajet(trajet * parTr);
