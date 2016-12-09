#pragma once
#include "includes.h"
#include "structures.h"
#include "config.h"
#include "trace.h"
#include "trajet.h"

pt_interet * createPointInteret(void);
pt_interet * initPointInteret(int parImpor, time_t parDbt, time_t parFin, point parPt, adresse parAddr);
liste_pt_interet * initListePointInteret(void);
void appendListePointInteret(liste_pt_interet * parListe);
void ajoutPointInteret(liste_pt_interet * parListe, pt_interet * parPtInteret);
liste_pt_interet calculPointInteret(trajet * parTr);
