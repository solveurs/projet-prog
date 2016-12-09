#pragma once
#include "includes.h"
#include "structures.h"
#include "trace.h"

void afficheTrajet(trajet * parTr);
void ajoutTrace(trajet * parTr, trace * parT);
void supprimerTraceN(trajet * parTr, trace * parT, int parPos);
trajet * initTrajet(void);
