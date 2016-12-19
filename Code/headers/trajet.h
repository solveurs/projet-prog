#pragma once
#include "includes.h"
#include "structures.h"
#include "trace.h"

trajet * initTrajet(void);
void ajoutTrace(trajet * parTr, trace * parT);
void supprimerTraceN(trajet * parTr, int parPos);
void afficheTrajet(trajet * parTr);
void supprimerTrajet(trajet * parTr);
int saveTrajet(trajet * parTr, const char * chemin);
