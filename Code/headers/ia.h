#pragma once
#include "includes.h"
#include "structures.h"
#include "config.h"


#define TAUX_ENTRAINEMENT	0.1
#define MOMENTUM			0.1
#define LAMBDA				1.0
#define ERREUR				0.05
#define NB_NEUR				10
#define NB_COUCHE			3
#define NB_MESURE			5


struct connection
{
	double poids;
	double deltaPoids;
};
typedef struct connection connection;

struct neurone
{
	int			id;
	double		outputValue;
	connection	outputCo[NB_NEUR];
	int			nbOutput;
	double		gradient;
	double		ETA;
	double		ALPHA;
};
typedef struct neurone neurone;

struct reseau
{
	int			topologie[NB_COUCHE];
	neurone*	reseauNeur[NB_COUCHE][NB_NEUR];
	double		erreur;
	double		moyErreur;
	int			nbMesure;
};
typedef struct reseau reseau;

//CONNECTION
double initConnection(); //initialise la connection avec des valeurs aléatoires

//NEURONE
neurone * initNeur(int parId,int parNbOutput); //initialisation d'un neurone
void feedForwardNeur(neurone * parPrevLayer);
void calcOutputGradient(double parTargetValue);
void calcHiddenGradients(neurone * parNextLayer);
void updateInputsPoids(neurone * parPrevLayer);
double fctTransfert(double parSum);
double fctTransfertDerivee(double par);
double sumDOW(neurone * parNextLayer);

//RESEAU DE NEURONE
reseau * initReseau(int parNbInput, int parNbOutput); //initialisation d'un reseau
reseau * nouvReseau(int parNbInput, int parNbOutput);
reseau * ouvrirReseau(const char* chemin);
void feedForwardRes(double * parInputVal);
void backPropagation(double * parTargetVal);
void afficherPoidsRes(reseau parRes);
int saveRes(const char* chemin, reseau parRes);




















