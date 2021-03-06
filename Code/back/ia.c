/**
 @file ia.c
 
 @brief Fichier de suggestion de cercle d'anonymisation avec une IA basée sur un réseau neuronal
 */

#include "../headers/ia.h"

/*
 L'IA (que Flavien implementeras) permetteras à parir de cercle déjà tracé par l'utilisateur de lui proposer des zones à anonymiser.
 Elle fonctionneras sur le principe de réseau neuronal sur des données déjà entré
 
 Manque encore plus de donnée pour améliorer l'IA
*/


/*
 COMMENT L'IA FONCTIONNE ?
 L'IA est basée sur un reseau neuronal simple (cours très bon à lire : http://web.stanford.edu/class/cs221/ )
 Elle prend en entrée 10(=NB_NEUR) informations, 5 positions (x,y) de trace
 Elle sort en sortie 3 informations, la positions x, y et le rayon du cercle
 La structure du réseau est evolutif suivant ce que l'on met dans la topologie du réseau (/!\ NB_NEUR-->max neurone par couche et NB_COUCHE-->max couche avec E/S comprises) : 
 X1\
 Y1-11-\
 X2\    \
 Y2-12--16==>c.centre.x
 X3-13--17==>c.centre.y
 Y3/
 X4-14--18==>c.rayon
 Y4/	/
 X5-15-/
 Y5/
 
 Le taux d'entrainement est de TAUX_ENTRAINEMENT 0.1
 Le taux de moment est de MOMENTUM 0.1
 La fonction de transfert est thanh() de parametre LAMBDA
 
 */



/**
 chargement de donné d'entrainement de l'IA

 @param chemin vers les données d'entrainement

 @return un tableau de donnée d'entrainement
 */
TrainData loadTrain(const char* chemin)
{
	FILE * fd = NULL;
	if((fd = fopen(chemin, "r")) == NULL)
	{
		perror("Erreur à l'ouverture des données d'entrainement");
	}
	
	TrainData varData;
	varData.t = (Data*)calloc(TAILLE_TAB_DYN, sizeof(Data));
	varData.size = TAILLE_TAB_DYN;
	//On lit tout les données du fichier
	//on en selectionne 25% que l'on renvoie
	return varData;
}


/**
 Entrainemetn du reseau neuronal

 @param parRes	un pointeur sur le reseau à entrainer
 @param parTraindata les données d'entrainement
 */
void TrainReseau(reseau * parRes, TrainData parTraindata)
{
	int i = 0;
	int j;
	int k = 0;
	double varInputData[NB_NEUR];
	while (i < parTraindata.size && i < 100 && parRes->erreur > ERREUR)
	{
		for (j = 0; j < parRes->topologie[0]; j++)
		{
			if (j%2 ==0)
			{
				varInputData[j] = parTraindata.t[k].coord.x;
				k++;
			}
			else
			{
				varInputData[j] = parTraindata.t[k].coord.y;
				k++;
			}
			
		}
		feedForwardRes(parRes, varInputData, parRes->topologie[0]);
		cercle_anonym varTargetVal;
		//FINIR FONCTION DE LECTURE DES VALEURS TARGET
		varTargetVal.c.centre.x = 0.0;
		varTargetVal.c.centre.y = 0.0;
		varTargetVal.c.rayon = 1.0;
		
		backPropagation(varTargetVal, parRes);
		
		printf("Moyenne d'erreur %lf", parRes->moyErreur);

	}
}


/**
 Fonction de suggestion de cercle d'anonymisation

 @param parRes le reseau neuronal ENTRAINE
 @param parTr  le trajet sur lequel on doit predire un cercle d'anonymisation

 @return le cercle d'anonymisation suggerer
 */
cercle_anonym SuggestCAnonymisation(reseau * parRes, trajet * parTr)
{
	cercle_anonym varCAno;
	varCAno.id = -1; //Assigner une valeur si l'utilisateur le valide
	//Selection de 10 valeur aleatoire dans la trace
	int i;
	int j;
	trace * it = parTr->premier;
	double tab[NB_NEUR];
	//on choisie des positions aléatoire
	for (i = 0; i < NB_NEUR/2; i+=2)
	{
		tab[i] = rand()%(parTr->taille) + 1;
	}
	for (i = 0; i < NB_NEUR; i+=2)
	{
		for (j = 0; j < tab[i]; j++)
		{
			it = it->suiv;
		}
		tab[i] = it->coord.x;
		tab[i+1] = it->coord.y;
	}
	
	feedForwardRes(parRes, tab, NB_NEUR);
	varCAno.c.centre.x = parRes->reseauNeur[NB_COUCHE][0]->outputValue;
	varCAno.c.centre.y = parRes->reseauNeur[NB_COUCHE][1]->outputValue;
	varCAno.c.rayon = parRes->reseauNeur[NB_COUCHE][2]->outputValue;
	
	return varCAno;
}



/*============CONNECTION============*/
/**
 initialisation de la valeur de poids aléatoire d'une connection

 @return une valeur aléatoire entre 0 et 1
 */
double initConnection()
{
	return (double)rand()/(double)RAND_MAX;
}









/*============NEURONE============*/

/**
 initialisation d'un neurone

 @param parId       l'id du neurone
 @param parNbOutput le nombre de sortie qu'il a

 @return un pointeur sur neurone
 */
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


/**
 calcul de la sortie du neurone avec les couches inférieur

 @param parPrevLayer     un tableau sur neurone qui modélise une couche
 @param parSizePrevLayer le nombre de neurone dans la couche inferieur
 @param parPosLayer      la position du neurone dans sa couche

 @return la valeur de sortie du neurone
 */
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


/**
 calcul du gradient de sorite d'un neurone

 @param parTargetValue la valeur de sortie attendue
 @param parNeur        le neurone selectionne

 @return la valeur du gradient de sortie
 */
double calcOutputGradient(double parTargetValue, neurone parNeur)
{
	double delta = parTargetValue - parNeur.outputValue;
	return delta * fctTransfertDerivee(parNeur.outputValue);
}


/**
 calcul du gradient des couches cachées

 @param parNextLayer un pointeur sur la couche supérieur
 @param parRes       le réseau complet
 @param parNeur      un pointeur sur le neurone en cours

 @return la valeur du gradient
 */
double calcHiddenGradients(neurone * parNextLayer, reseau parRes, neurone * parNeur)
{
	double varDow = sumDOW(parNextLayer, parRes, parNeur);
	return varDow * fctTransfertDerivee(parNeur->outputValue);
}


/**
 Update de tout les poids des connections du réseau

 @param parPrevLayer    la couche inférieur
 @param parRes          le reseau
 @param parPosLayerNeur la position de la couche
 */
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


/**
 fonction de transfert du neurone pour introduire de la continuité

 @param par la valeur de sortie intermédiaire

 @return la valeur de sorite du neurone
 */
double fctTransfert(double par)
{
	return tanh(LAMBDA * par);
}


/**
 dérivé de la fonction de transfert

 @param par valeur du gradient intermédiaire

 @return le gradient
 */
double fctTransfertDerivee(double par)
{
	return 1.0 - pow(fctTransfert(par), 2);
}


/**
 Sum DataOutputWeight, pour calculer les gradients

 @param parNextLayer la couche suivante
 @param parRes       le reseau
 @param parNeur      le neurone

 @return le gradient intermédiaire
 */
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









/*============RESEAU NEURONAL============*/

/**
 initialisation du reseau de neurone

 @param parNbInput  le nombre d'entrée dans le réseau
 @param parNbOutput le nombre de sortie du réseau

 @return un pointeur sur réseau
 */
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


/**
 création d'un nouveau réseau aléatoire

 @param parNbInput  le nombre d'entrée dans le réseau
 @param parNbOutput le nombre de sortie du réseau

 @return un pointeur sur réseau
 */
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


/**
 Ouverture d'un réseau depuis le fichier

 @param chemin vers le fichier du reseau sauvegarde

 @return un pointeur sur réseau, NULL si le fichier à une erreur
 */
reseau * ouvrirReseau(const char* chemin)
{
	reseau * varRes;
	FILE * fd = NULL;
	if ((fd = fopen(chemin, "r")) == NULL)
	{
		perror("Erreur à l'ouverture du fichier de config de l'ia");
		return NULL;
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
				return NULL;
			}
		}
	}
	return varRes;
}


/**
 Calcul de la sortie du réseau

 @param parRes      le pointeur dur réseau
 @param parInputVal un tableau de valeur d'entrée
 @param parNbInput  le nombre d'entrée = nb de neurone de la première couche
 */
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


/**
 la bcak propagation sur les couches inférieurs

 @param parTarget	le cercle d'anonymisation attendu
 @param parRes       le réseau
 */
void backPropagation(cercle_anonym parTarget, reseau * parRes)
{
	parRes->erreur = 0.0;
	int i;
	double parTargetVal[3];
	parTargetVal[0] = parTarget.c.centre.x;
	parTargetVal[1] = parTarget.c.centre.y;
	parTargetVal[2] = parTarget.c.rayon;
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


/**
 Affichage de tout les poids

 @param parRes le réseau
 */
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


/**
 Sauvegarde du réseau neuronal

 @param chemin vers le fichier de sauvegarde
 @param parRes le reseau

 @return >0 si le réseau est bien sauvegardé
 */
int saveRes(const char* chemin, reseau parRes)
{
	FILE * fd = NULL;
	if ((fd = fopen(chemin, "w")) == NULL)
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





















