#pragma once
#include "includes.h"


/**
 @brief modelisation d'un point
 */
struct coord_double
{
	double x;
	double y;
};
typedef struct coord_double point;

/**
 @brief modelisation d'un pixel
 */
struct coord_int
{
	int x;
	int y;
};
typedef struct coord_int pixel;

/**
 @brief modelisation d'un rectangle
 */
struct rectangle
{
	point     origine; /**<coin haut-gauche*/
	double    largeur;
	double    hauteur;
};
typedef struct rectangle rectangle;

/**
 @brief modelisation d'un cercle
 */
struct cercle
{
	point     centre;
	double    rayon;
};
typedef struct cercle cercle;

/**
 @brief modelisation d'une adresse
 */
struct adresse
{
	int       numero;
	char      nom_rue[128];
	int       code_postal;
	//char[128] nom_ville;
	point     coord;
};
typedef struct adresse adresse;


/**
 @brief modélisation d'une trace
 */
struct trace
{
	int				id;/**<Id dans le trajet*/
	time_t			date;/**<Date de relevé de la trace*/
	point			coord;/**<coordonnée de la trace*/
	int				visibilite;/**<visibilité, 0 --> invisible, 1 --> visible*/
	struct trace *	prec;/**<pointeur sur la trace précédente*/
	struct trace *	suiv;/**<pointeur sur la trace suivante*/
};
typedef struct trace trace;

/**
 @brief modelisation d'un trajet
 */
struct trajet
{
	int		taille;/**<nombre de trace dans le trajet*/
	int		visibilite;/**<visibilité, 0 --> invisible, 1 --> visible*/
	trace *	premier;/**<pointeur sur la premiere trace*/
	trace * dernier;/**<pointeur sur la derniere trace*/
};
typedef struct trajet trajet;

/**
 @brief modelisation de la base de donnée de trace
 */
struct bdd_trace
{
	char     chemin[128];
	//int       taille;
	trajet * trajet;
	//trace *   tab_trace; //pas sûr
	int      visibilite; //0=public >0 = depend user
};
typedef struct bdd_trace bdd_trace;

/**
 @brief modelisation d'un point d'interet
 */
struct pt_interet
{
	int			id;
	int			importance;/**<importance sur le point d'interet*/
	time_t		debut;/**<date de debut du point d'interet*/
	time_t		fin;/**<date de fin du point d'interet*/
	point		position;/**<coord du point d'interet*/
	adresse		adresse;/**<adresse du point d'interet*/
};
typedef struct pt_interet pt_interet;

/**
 @brief modelisation d'une liste de point d'interet
 */
struct liste_pt_interet
{
	int				id;
	int				taille;
	int				occupee;
	pt_interet**	t;
};
typedef struct liste_pt_interet liste_pt_interet;

struct cercle_anonym
{
	int				id;
	cercle			c;
};
typedef struct cercle_anonym cercle_anonym;

struct liste_c_anonym
{
	int				id;
	int				taille;
	int				occupee;
	cercle_anonym**	t;
};
typedef struct liste_c_anonym liste_c_anonym;

/**
 @brief modelisation d'une carte
 */
struct carte
{
	char		chemin_image_carte[128];
	char		chemin_donnees_carte[128];
	rectangle	zone_pixel; //point est un double,double et pixel int,int
	rectangle	zone_latlong;
	double		ratio;
	
};
typedef struct carte carte;

/**
 @brief modelisation d'un utilisateur
 */
struct utilisateur
{
	char      identifiant[128];
	char      mdp[128];
	char      chemin_dossier[128];
};
typedef struct utilisateur utilisateur;

