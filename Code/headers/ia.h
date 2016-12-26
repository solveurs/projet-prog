#pragma once
#include "includes.h"
#include "structures.h"
#include "config.h"
#include "utils.h"

/*============CONSTANTES============*/
#define TAUX_ENTRAINEMENT	0.1
#define MOMENTUM			0.1
#define LAMBDA				1.0
#define ERREUR				0.05
#define NB_NEUR				10
#define NB_COUCHE			3
#define NB_MESURE			5


/**
 @brief modele le plus simple d'une trace
 */
struct Data
{
	time_t	date;
	point	coord;
};
typedef struct Data Data;

/**
 @brief modele le plus simple d'un trajet
 */
struct TrainData
{
	int		size;
	Data *	t;
};
typedef struct TrainData TrainData;

/**
 @brief modelisation d'une connection neuronal
 */
struct connection
{
	double poids;
	double deltaPoids;
};
typedef struct connection connection;

/**
 @brief modelisation d'un neurone
 */
struct neurone
{
	int			id;/**<l'id du reseau*/
	double		outputValue;/**<la valeur de sortie*/
	connection	outputCo[NB_NEUR];/**<tableau de connection de sortie*/
	int			nbOutput;/**<nombre de sortie*/
	double		gradient;/**gradient du neurone*/
	double		ETA;/**<Taux d'apprentissage*/
	double		ALPHA;/**<Le moment*/
};
typedef struct neurone neurone;

/**
 @brief modelisation d'un reseau de neurone
 */
struct reseau
{
	int			topologie[NB_COUCHE];/**<la topologie du reseau*/
	neurone*	reseauNeur[NB_COUCHE][NB_NEUR];/**<le tableau de pointeur sur neurone*/
	double		erreur;/**<l'erreur actuelle du réseau*/
	double		moyErreur;/**<l'erreur moyenne du réseau*/
	int			nbMesure;/**<le nombre de mesure pour le calcul de l'erreur*/
};
typedef struct reseau reseau;

/*============ENTRAINEMENT ET RESULTAT============*/
TrainData loadTrain(const char* chemin);
void TrainReseau(reseau * parRes, TrainData parTraindata);
pt_interet SuggestPtInteret(reseau * parRes, trajet * parTr);


/*============CONNECTION============*/
double initConnection(); //initialise la connection avec des valeurs aléatoires

/*============NEURONE============*/
neurone * initNeur(int parId,int parNbOutput); //initialisation d'un neurone
double feedForwardNeur(neurone * parPrevLayer, int parSizePrevLayer, int parPosLayer);
double calcOutputGradient(double parTargetValue, neurone parNeur);
double calcHiddenGradients(neurone * parNextLayer, reseau parRes, neurone * parNeur);
void updateInputsPoids(neurone * parPrevLayer, reseau parRes, int parPosLayerNeur);
double fctTransfert(double par);
double fctTransfertDerivee(double par);
double sumDOW(neurone * parNextLayer, reseau parRes, neurone * parNeur);

/*============RESEAU NEURONAL============*/
reseau * initReseau(int parNbInput, int parNbOutput); //initialisation d'un reseau
reseau * nouvReseau(int parNbInput, int parNbOutput);
reseau * ouvrirReseau(const char* chemin);
void feedForwardRes(reseau * parRes, double * parInputVal, int parNbInput);
void backPropagation(cercle_anonym parTarget, reseau * parRes);
void afficherPoidsRes(reseau parRes);
int saveRes(const char* chemin, reseau parRes);




















