#pragma once
#include "includes.h"
#include "structures.h"
#include "config.h"
#include "trace.h"
#include "trajet.h"
#include "utils.h"
#include "conversion.h"

pt_interet * createPointInteret(void);
pt_interet * initPointInteret(int parImpor, time_t parDbt, time_t parFin, point parPt, adresse parAddr);
liste_pt_interet * initListePointInteret(void);
void appendListePointInteret(liste_pt_interet * parListe);
void ajoutPointInteret(liste_pt_interet * parListe, pt_interet * parPtInteret);
liste_pt_interet * calculPointInteretSpatial(trajet * parTr);
liste_pt_interet * calculPointInteretTemp(trajet * parTr);
pt_interet * fusionPtInteret(pt_interet * parPtInt1, pt_interet * parPtInt2);
int savePointInteret(const liste_pt_interet parArrPtInteret);
void affichePtInteret(pt_interet * parPtIntrt);
void afficheArrPtInteret(liste_pt_interet * parArrPtIntrt);
