#pragma once
#include "includes.h"
#include "structures.h"

trace * createTrace(void);
void initTrace(trace * parT, long parDate, point parCoord, trace * parPrec, trace * parSuiv);
trajet * initTrajet(void);
void ajoutTrace(trajet * parTr, trace * parT);
void supprimerTraceN(trajet * parTr, trace * parT, int parPos);
void afficheTrace(trace * parT);
void afficheTrajet(trajet * parTr);
