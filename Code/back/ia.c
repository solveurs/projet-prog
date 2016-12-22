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

double feedForwardNeur(neurone * parPrevLayer, int parSizePrevLayer, int parPosLayer)
{
	double varSum = 0.0;
	int i;
	for (i = 0; i < parSizePrevLayer; i++)
	{
		varSum += (parPrevLayer[i].outputValue * parPrevLayer[i].outputCo[parPosLayer].poids);
	}
	return fctTransfert(varSum);
}

double calcOutputGradient(double parTargetValue, neurone parNeur)
{
	double delta = parTargetValue - parNeur.outputValue;
	return delta * fctTransfertDerivee(parNeur.outputValue);
}

double calcHiddenGradients(neurone * parNextLayer, reseau parRes, neurone * parNeur)
{
	double varDow = sumDOW(parNextLayer, parRes, parNeur);
	return varDow * fctTransfertDerivee(parNeur->outputValue);
}

void updateInputsPoids(neurone * parPrevLayer, reseau parRes, int parPosLayerNeur)
{
	int i;
	for (i = 0; i < parRes.topologie[NB_COUCHE - 1] ; i++)
	{
		double ancDeltaPoids = parPrevLayer[i].outputCo[parPosLayerNeur].deltaPoids;
		double nvDeltaPoids = (parPrevLayer[i].ETA * parPrevLayer[i].outputValue * parPrevLayer[i].gradient) + (parPrevLayer[i].ETA * ancDeltaPoids);
		parPrevLayer[i].outputCo[parPosLayerNeur].deltaPoids = nvDeltaPoids;
		parPrevLayer[i].outputCo[parPosLayerNeur].poids += nvDeltaPoids;
	}
}

double fctTransfert(double par)
{
	return tanh(LAMBDA * par);
}

double fctTransfertDerivee(double par)
{
	return 1.0 - pow(fctTransfert(par), 2);
}

double sumDOW(neurone * parNextLayer, reseau parRes, neurone * parNeur)
{
	double sum = 0.0;
	int i;
	for (i = 0; i < parRes.topologie[NB_COUCHE - 1]; i++)
	{
		sum += (parNeur->outputCo[i].poids * parNextLayer[i].gradient);
	}
	return sum;
}









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

void feedForwardRes(reseau * parRes, double * parInputVal, int parNbInput)
{
	int i;
	for (i = 0; i < parNbInput; i++)
	{
		parRes->reseauNeur[0][i]->outputValue = parInputVal[i];
	}
	int j, k;
	for (j = 1; j < NB_COUCHE; j++)
	{
		for (k = 0; k < parRes->topologie[j]; k++)
		{
			parRes->reseauNeur[j][k]->outputValue = feedForwardNeur(*parRes->reseauNeur[j - 1], parRes->topologie[j - 1], k);
		}
	}
}

void backPropagation(double * parTargetVal, reseau * parRes)
{
	parRes->erreur = 0.0;
	int i;
	for (i = 0; i < parRes->topologie[NB_COUCHE - 1]; i++)
	{
		double delta  = (double)(parTargetVal[i] - parRes->reseauNeur[3][i]->outputValue);
		parRes->erreur += pow(delta, 2);
	}
	
	parRes->erreur /= (double)(parRes->topologie[NB_COUCHE - 1]);
	parRes->erreur = sqrt(parRes->erreur);
	
	parRes->moyErreur = (parRes->moyErreur * parRes->nbMesure + parRes->erreur)/ parRes->nbMesure;
	
	//Calcul du gradient de sortie
	int j;
	for (j = 0; j < parRes->topologie[NB_COUCHE - 1]; j++)
	{
		parRes->reseauNeur[NB_COUCHE - 1][j]->gradient = calcOutputGradient(parTargetVal[NB_COUCHE - 1], *parRes->reseauNeur[NB_COUCHE - 1][j]);
	}
	
	//Calcul du gradient des couches intermédiaires
	int k;
	for (k = NB_COUCHE - 2; k > 0 ; k--)
	{
		int m;
		for (m = 0; m < parRes->topologie[k]; m++)
		{
			parRes->reseauNeur[k][m]->gradient = calcHiddenGradients(*parRes->reseauNeur[k + 1], *parRes, parRes->reseauNeur[k][m]);
		}
	}
	
	//On update tout les poids
	int l;
	for (l = NB_COUCHE - 1; l > 0; l--)
	{
		int n;
		for (n = 0; n < (NB_COUCHE - 1); n++)
		{
			updateInputsPoids(*parRes->reseauNeur[l - 1], *parRes, n);
		}
	}
	
}

void afficherPoidsRes(reseau parRes)
{
	int i,j,k;
	for (i = 0; i < NB_COUCHE; i++)
	{
		for (j = 0; j < parRes.topologie[i]; j++)
		{
			printf("[%d] Neurone[%d][%d] : ",parRes.reseauNeur[i][j]->id, i, j);
			for (k = 0; k < parRes.reseauNeur[i][j]->nbOutput; k++)
			{
				printf("=[%lf]=>[%d][%d]",parRes.reseauNeur[i][j]->outputCo[k].poids, i + 1, k);
			}
		}
	}
}

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





















