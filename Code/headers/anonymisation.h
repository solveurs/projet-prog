#pragma once
#include "includes.h"
#include "structures.h"
#include "utils.h"
#include "trajet.h"

int anonymisationPendantEditionC(trajet * parTr, const cercle parC);
int anonymisationPendantEditionR(trajet * parTr, const rectangle parR);
int anonymisationPendantEditionT(trajet * parTr, const int parIdTrace);
int anonymisationApresEdition(trajet * parTr);

bdd_trace * saveTrajetAnonymise(const trajet parTr, const char * chemin, const int visibilite);

//extern int inAnonymisation;
