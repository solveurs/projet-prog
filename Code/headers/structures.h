#pragma once
#include "includes.h"

struct point
{
	double x;
	double y;
};
typedef struct point point;

//Origine : coin haut-gauche
struct rectangle
{
	point     origine;
	double    largeur;
	double    hauteur;
};
typedef struct rectangle rectangle;

struct cercle
{
	point     centre;
	double    rayon;
};
typedef struct cercle cercle;


struct pixel
{
	int x;
	int y;
};

struct adresse
{
	int       numero;
	char      nom_rue[128];
	int       code_postal;
	//char[128] nom_ville;
	point     coord;
};
typedef struct adresse adresse;

struct trace
{
	time_t			date;
	point			coord;
	int				visibilite;
	struct trace *	prec;
	struct trace *	suiv;
};
typedef struct trace trace;

struct trajet
{
	int		taille;
	int		visiblite;
	trace *	premier;
	trace * dernier;
};
typedef struct trajet trajet;

struct bdd_trace
{
	char     chemin[128];
	//int       taille;
	trajet * trajet;
	//trace *   tab_trace; //pas sûr
	int      visibilite; //0=public >0 = depend user
};
typedef struct bdd_trace bdd_trace;

 struct pt_interet
 {
	 int		importance;
	 time_t		debut;
	 time_t		fin;
	 point		position;
	 adresse *	tab_adresse;
 };

struct carte
{
	char		chemin_image_carte[128];
	char		chemin_donnees_carte[128];
	rectangle	zone_pixel; //point est un double,double et pixel int,int
	rectangle	zone_latlong;
	double		ratio;
	
};
typedef struct carte carte;

struct utilisateur
{
	char      identifiant[128];
	char      mdp[128];
	char      chemin_dossier[128];
};
typedef struct utilisateur utilisateur;

typedef struct pixel pixel;
