#pragma once
#include "includes.h"
#include "structures.h"
#include "trace.h"
#include "trajet.h"

pt_interet * createPointInteret(void);
pt_interet * initPointInteret(int parImpor, time_t parDbt, time_t parFin, point parPt, adresse * parAddr);
liste_pt_interet calculPointInteret(trajet * parTr);
