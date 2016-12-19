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
carte carte_Cher = initCarte("../../Data/cartes/carte_Cher.png", 1013, 1920, 47.988083, 1.726227, 46.194092, 3.115997);
carte carte_Bourges = initCarte("../../Data/cartes/carte_Bourges.png", 1850, 1079, 47.113540, 2.313738, 47.050476, 2.472610);
carte carte_Insa = initCarte("../../Data/cartes/carte_Insa.png", 1850, 1080, 47.088723, 2.392981, 47.072957, 2.432764);
