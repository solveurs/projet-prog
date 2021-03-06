#pragma once
#include "includes.h"
#include "structures.h"
#include "conversion.h"

int isInCercle(const cercle parC, const point parP);
int isInRectangle(const rectangle parR, const point parP);
int dis2points(const point parP1, const point parP2, const double parDisMax);
double distanceTrajet(const trajet parTr);
double vitesseMoyenneTrajet(const trajet parTr);
long tempsTrajet(const trajet parTr);
char* tempsTrajetHeure(const trajet parTr);
adresse * initAdresse(void);
void affichePoint(point parP);
rectangle initRectangle(point origine, double hauteur, double largeur);
point initPoint(double x, double y);
void quicksortLat(point * parTab, int len);
void quicksortLon(point * parTab, int len);
