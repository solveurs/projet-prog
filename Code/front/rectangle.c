#include "../headers/rectangle.h"

rectangle initRectangle(point origine, double hauteur, double largeur)
{
  rectangle resR;
  resR.origine = origine;
  resR.hauteur = hauteur;
  resR.largeur = largeur;
  return resR;
}
