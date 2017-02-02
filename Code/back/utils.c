/**
 @file utils.c
 
 @brief fonctions utiles pour le back
 */
#include "../headers/utils.h"


/**
 fonction qui nous dit si un point est dans un cercle ou pas

 @param parC le cercle
 @param parP le point

 @return >0 --> dans le cercle <0 sinon
 */
int isInCercle(const cercle parC, const point parP)
{
	/* NB : Inversion longitude et latitude corrigee */
	long double diff = (pow((parP.x - parC.centre.y),2) + pow((parP.y - parC.centre.x),2));
	long double rayon = pow(parC.rayon,2);
	if(diff < rayon) 
	{
		return 1;
	}
	else
	{
		return -1;
	}
}


/**
 fonction qui nous dit si un point est dans un rectangle ou pas

 @param parR le rectangle
 @param parP le point

 @return >0 --> dans le rectangle <0 sinon
 */
int isInRectangle(const rectangle parR, const point parP)
{
	//condition pas sûre
	if ((parP.x < parR.origine.x) || (parP.y < parR.origine.y) || (parP.x > parR.origine.x + parR.largeur) || (parP.y > parR.origine.y + parR.hauteur))
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int dis2points(const point parP1, const point parP2, const double parDisMax)
{
	return (GPStoKm(parP1, parP2) < parDisMax)?1:0;
}

double distanceTrajet(const trajet parTr)
{
	double dis = 0.0;
	trace * it = parTr.premier;
	
	while (it->suiv != NULL)
	{
		dis += GPStoKm(it->coord, it->suiv->coord);
		it = it->suiv;
	}
	return dis;
}

double vitesseMoyenneTrajet(const trajet parTr)
{
	double varVitesse = 0.0;	
	varVitesse = distanceTrajet(parTr)/tempsTrajet(parTr);
	varVitesse *= (double)(10000);
	return varVitesse;
}

long tempsTrajet(const trajet parTr)
{
	return (parTr.dernier->date - parTr.premier->date);
}

char* tempsTrajetHeure(const trajet parTr)
{
	char * buf;
	buf = (char*)calloc(80,sizeof(char));
	strftime(buf, 80, "%H:%M:%S", timestampToReadable(tempsTrajet(parTr)));
	return buf;
}

adresse * initAdresse(void)
{
	adresse * varAddr = malloc(sizeof(adresse));
	varAddr->code_postal	=	18000;
	varAddr->coord.x		=	0;
	varAddr->coord.y		=	0;
	strcpy(varAddr->nom_rue, "");
	varAddr->numero			=	0;
	return varAddr;
}

void affichePoint(point parP)
{
	printf("x = %lf : y = %lf\n",parP.x,parP.y);
}

rectangle initRectangle(point origine, double hauteur, double largeur)
{
	rectangle resR;
	resR.origine = origine;
	resR.hauteur = hauteur;
	resR.largeur = largeur;
	return resR;
}

point initPoint(double x, double y)
{
	point resP;
	resP.x = x;
	resP.y = y;
	return resP;
}

void quicksortLat(point * parTab, int len)
{
	
	if (len < 2) return;
	
	double pivot = parTab[len/2].x;
	int i, j;
	for (i=0, j = len - 1; ;i++, j--)
	{
		while (parTab[i].x < pivot)
		{
			i++;
		}
		while (parTab[j].x >pivot)
		{
			j--;
		}
		if (i >= j) break;
		
		point tmp = parTab[i];
		parTab[i] = parTab[j];
		parTab[j] = tmp;
	}
	//affichePoint(parTab[i]);
	quicksortLat(parTab, i);
	quicksortLat(&parTab[i], len -i);
}

void quicksortLon(point * parTab, int len)
{
	
	if (len < 2) return;
	
	double pivot = parTab[len/2].y;
	int i, j;
	for (i=0, j = len - 1; ;i++, j--)
	{
		while (parTab[i].y < pivot)
		{
			i++;
		}
		while (parTab[j].y >pivot)
		{
			j--;
		}
		if (i >= j) break;
		
		point tmp = parTab[i];
		parTab[i] = parTab[j];
		parTab[j] = tmp;
	}
	
	quicksortLon(parTab, i);
	quicksortLon(&parTab[i], len -i);
}
