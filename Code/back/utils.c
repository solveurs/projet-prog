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
	if (pow((parP.x - parC.centre.x),2) + pow((parP.x - parC.centre.y),2) < parC.rayon) {
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
