#include "../headers/ia.h"

/*
 L'IA (que Flavien implementeras) permetteras à parir de cercle déjà tracé par l'utilisateur de lui proposer des zones à anonymiser.
 Elle fonctionneras sur le principe de réseau neuronal sur des données déjà entré
*/

//CONNECTION
double initConnection()
{
	return (double)rand()/(double)RAND_MAX;
}

//NEURONE
neurone * initNeur(int parId,int parNbOutput)
{
	neurone * varNeur = (neurone*)malloc(sizeof(neurone));
	varNeur->id			= parId;
	if (parNbOutput < NB_NEUR) {
		varNeur->nbOutput	= parNbOutput;
	}
	else
	{
		varNeur->nbOutput = NB_NEUR;
	}
	
	int i;
	for (i = 0; i < varNeur->nbOutput; i++)
	{
		varNeur->outputCo[i].poids = initConnection();
		varNeur->outputCo[i].deltaPoids = 0.0;
	}
	varNeur->outputValue = 0.0;
	varNeur->ETA = TAUX_ENTRAINEMENT;
	varNeur->ALPHA = MOMENTUM;
	varNeur->gradient = 0.0;
	
	return varNeur;
}

void feedForwardNeur(neurone * parPrevLayer);
void calcOutputGradient(double parTargetValue);
void calcHiddenGradients(neurone * parNextLayer);
void updateInputsPoids(neurone * parPrevLayer);
double fctTransfert(double parSum);
double fctTransfertDerivee(double par);
double sumDOW(neurone * parNextLayer);

//RESEAU DE NEURONE
reseau * initReseau(int parNbInput, int parNbOutput)
{
	reseau * varRes = (reseau*)malloc(sizeof(reseau));
	
	varRes->topologie[0] = parNbInput; //couche d'entrée
	varRes->topologie[1] = NB_NEUR;		//couches intermédiaire
	varRes->topologie[2] = parNbOutput;		//couche de sortie
	
	varRes->erreur = 0.0;
	varRes->moyErreur = 0.0;
	varRes->nbMesure = NB_MESURE;
	
	return varRes;
}

reseau * nouvReseau(int parNbInput, int parNbOutput)
{
	reseau * varRes = initReseau(parNbInput, parNbOutput);
	int i,j;
	for (i = 0; i < NB_COUCHE; i++)
	{
		for (j = 0; j < varRes->topologie[i]; j++)
		{
			varRes->reseauNeur[i][j] = initNeur(i+j, varRes->topologie[i+1]);
		}
	}
	return varRes;
}

reseau * ouvrirReseau(const char* chemin)
{
	reseau * varRes;
	FILE * fd = NULL;
	if ((fd = fopen(chemin, "r")) == NULL)
	{
		perror("Erreur à l'ouverture du fichier de config de l'ia");
	}
	int vartopo[NB_COUCHE];
	fscanf(fd, "topo:%d,%d,%d\n",&vartopo[0],&vartopo[1],&vartopo[2]); //A rendre plus evolutif
	varRes = initReseau(vartopo[0], vartopo[2]);
	int i,j;
	for (i = 0; i < NB_COUCHE; i++)
	{
		for (j = 0; j < varRes->topologie[i]; j++)
		{
			if(fscanf(fd,"id:%d,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
				   &varRes->reseauNeur[i][j]->id,
				   &varRes->reseauNeur[i][j]->outputCo[0].poids,
				   &varRes->reseauNeur[i][j]->outputCo[1].poids,
				   &varRes->reseauNeur[i][j]->outputCo[2].poids,
				   &varRes->reseauNeur[i][j]->outputCo[3].poids,
				   &varRes->reseauNeur[i][j]->outputCo[4].poids,
				   &varRes->reseauNeur[i][j]->outputCo[5].poids,
				   &varRes->reseauNeur[i][j]->outputCo[6].poids,
				   &varRes->reseauNeur[i][j]->outputCo[7].poids,
				   &varRes->reseauNeur[i][j]->outputCo[8].poids,
				   &varRes->reseauNeur[i][j]->outputCo[9].poids) < 0)
			{
				perror("Erreur à la lecture du fichier de config de l'ia");
			}
		}
	}
	return varRes;
}

void feedForwardRes(double * parInputVal);
void backPropagation(double * parTargetVal);
void afficherPoidsRes(reseau parRes);

int saveRes(const char* chemin, reseau parRes)
{
	FILE * fd = NULL;
	if ((fd = fopen(chemin, "r")) == NULL)
	{
		perror("Erreur à la création du fichier de config de l'ia");
		return -1;
	}
	int i,j,k;
	for (i = 0; i < NB_COUCHE; i++)
	{
		for (j = 0; j < parRes.topologie[i]; j++)
		{
			for (k = 0; k < parRes.reseauNeur[i][j]->nbOutput; k++)
			{
				if (fwrite(&parRes.reseauNeur[i][j]->outputCo[k], sizeof(double), 1, fd))
				{
					perror("Erreur à l'ecriture du fichier de config de l'ia");
					return -1;
				}
			}
			for (k = k; k < NB_NEUR; k++)
			{
				if (fwrite("0.0", sizeof(double), 1, fd))
				{
					perror("Erreur à l'ecriture du fichier de config de l'ia");
					return -1;
				}
			}
		}
	}
	return 1;
}





















