#pragma once
#include "includes.h"
#include "structures.h"
#include "config.h"
#include "utils.h"


#define TAUX_ENTRAINEMENT	0.1
#define MOMENTUM			0.1
#define LAMBDA				1.0
#define ERREUR				0.05
#define NB_NEUR				10
#define NB_COUCHE			3
#define NB_MESURE			5

struct Data
{
	time_t	date;
	point	coord;
};
typedef struct Data Data;

struct TrainData
{
	int		size;
	Data *	t;
};
typedef struct TrainData TrainData;

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

//ENTRAINEMENT DU RESEAU
TrainData loadTrain(const char* chemin);
void TrainReseau(reseau * parRes, TrainData parTraindata);
pt_interet SuggestPtInteret(reseau * parRes, trajet * parTr);


//CONNECTION
double initConnection(); //initialise la connection avec des valeurs aléatoires

//NEURONE
neurone * initNeur(int parId,int parNbOutput); //initialisation d'un neurone
double feedForwardNeur(neurone * parPrevLayer, int parSizePrevLayer, int parPosLayer);
double calcOutputGradient(double parTargetValue, neurone parNeur);
double calcHiddenGradients(neurone * parNextLayer, reseau parRes, neurone * parNeur);
void updateInputsPoids(neurone * parPrevLayer, reseau parRes, int parPosLayerNeur);
double fctTransfert(double par);
double fctTransfertDerivee(double par);
double sumDOW(neurone * parNextLayer, reseau parRes, neurone * parNeur);

//RESEAU DE NEURONE
reseau * initReseau(int parNbInput, int parNbOutput); //initialisation d'un reseau
reseau * nouvReseau(int parNbInput, int parNbOutput);
reseau * ouvrirReseau(const char* chemin);
void feedForwardRes(reseau * parRes, double * parInputVal, int parNbInput);
void backPropagation(double * parTargetVal, reseau * parRes);
void afficherPoidsRes(reseau parRes);
int saveRes(const char* chemin, reseau parRes);




















