#include "../headers/carte.h"

carte initCarte(char* chemin_image_carte, char* chemin_donnees_carte, rectangle zone_pixel, rectangle zone_latlong)
{
  carte res;
  point hautGauchePixel     = initPoint(0, 0);
  point hautGaucheReel      = initPoint(latitudeHautGauche, longitudeHautGauche);
  rectangle zone_pixel      = initRectangle(hautGauchePixel, hauteur, largeur);
  rectangle zone_latlong    = initRectangle(hautGaucheReel, latitudeBasDroite, longitudeBasDroite);
  res.chemin_image_carte    = chemin_image_carte;
  res.chemin_donnees_carte  = chemin_donnees_carte;
  res.zone_pixel            = zone_pixel;
  res.zone_latlong          = zone_latlong;
  return res;
}
carte carte_Cher = initCarte("../../Data/cartes/carte_Cher.png", 1037, 1920, 47.928306, 1.757813, 46.132267, 3.181915);
carte carte_Bourges = initCarte("../../Data/cartes/carte_Bourges.png", 1877, 1080, 47.111495, 2.309103, 47.048429, 2.470207);
carte carte_Insa = initCarte("../../Data/cartes/carte_Insa.png", 1877, 1080, 47.084895, 2.400116, 47.077012, 2.420254);
