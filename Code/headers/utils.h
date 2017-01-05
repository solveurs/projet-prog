#pragma once
#include "includes.h"
#include "structures.h"
#include "conversion.h"

int isInCercle(const cercle parC, const point parP);
int isInRectangle(const rectangle parR, const point parP);
int dis2points(const point parP1, const point parP2, const double parDisMax);
adresse * initAdresse(void);
void affichePoint(point parP);
rectangle initRectangle(point origine, double hauteur, double largeur);
point initPoint(double x, double y);
