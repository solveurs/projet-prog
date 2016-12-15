#pragma once
#include "includes.h"
#include "structures.h"

trajet * IimportTrajet(const char * nom);
liste_pt_interet* IgetPtInteret(trajet * parTr);
trajet * IlectureTrace(int parCmd, trajet * parTr);
trajet * IanonymisationC(const trajet parTr, const cercle parCercleAno);
trajet * IanonymisationP(const trajet parTr, const int parIdTraceAno);
trajet * IanonymisationR(const trajet parTr, const rectangle parRectAno);
liste_c_anonym * IsuggestAnonymisation();
