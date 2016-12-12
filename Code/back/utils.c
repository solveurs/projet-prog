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
