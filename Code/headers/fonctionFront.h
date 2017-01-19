#pragma once
#include "includes.h"
#include "structures.h"
#include "anonymisation.h"
#include "parserBddGeoloc.h"
#include "pointInteret.h"

trajet * IimportTrajet(const char * nom);
liste_pt_interet* IgetPtInteret(trajet * parTr);
int IlectureTrace(int parCmd, trajet * parTr);
void IModeAnonymisation();
void IfinModeAnonymisation();
void IsaveAnonymisation(const trajet parTr, const char * chemin);
void IanonymisationC(trajet * parTr, const cercle parCercleAno);
void IanonymisationP(trajet * parTr, const int parIdTraceAno);
void IanonymisationR(trajet * parTr, const rectangle parRectAno);
liste_c_anonym * IsuggestAnonymisation();
