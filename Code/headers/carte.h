#pragma once
#include "includes.h"
#include "structures.h"
#include "point.h"
#include "rectangle.h"

carte initCarte(char chemin_image_carte[128], char chemin_donnees_carte[128], int hauteur, int largeur, double latitudeHautGauche, double longitudeHautGauche, double latitudeBasDroite, double longitudeBasDroite);
