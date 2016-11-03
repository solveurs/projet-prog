#pragma once
#include "includes.h"

struct point
{
     double x;
     double y;
};
typedef struct point point;

struct adresse
{
     int       numero;
     char[128] nom_rue;
     int       code_postal;
     //char[128] nom_ville;
     point     coord;
};
typedef struct adresse adresse;

struct trace
{
     double         date;
     point          coord;
     struct trace * prec;
     struct trace * suiv;
};
typedef trace trace;

struct bdd_trace
{
     char[128] chemin;
     int       taille;
     trace *   tab_trace; //pas sûr
     int       visibilite; //0=public >0 = depend user
}
typedef bdd_trace bdd_trace;

// struct bdd_pt_interet
// {
//      adresse * tab_adresse;
// }
typedef adresse* bdd_pt_interet;

struct carte
{
     char[128] chemin_image_carte;
     char[128] chemin_donnees_carte;
     rectangle zone_pixel; //point est un double,double et pixel int,int
     rectangle zone_latlong;
}
typedef struct carte carte;

struct utilisateur
{
     char[128]      identifiant;
     char[128]      mdp;
     char[128]      chemin_dossier;
}
typedef struct utilisateur utilisateur

struct cercle
{
     point     centre;
     double    rayon;
}
typedef cercle cercle;

struct rectangle
{
     point     origine;
     int       largeur;
     int       hauteur;
}
typedef rectangle rectangle;

struct pixel
{
     int x;
     int y;
}
typedef pixel pixel;
