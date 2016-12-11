/**
 @file trace.c

 @brief fonctions relatives à la gestion des traces
 */
#include "../headers/trace.h"



/**
 création de trace

 @return un pointeur sur trace
 */
trace * createTrace(void)
{
	trace * varT = (trace*)malloc(sizeof(trace));
	return varT;
}

/**
 initialise une trace

 @param parDate  la date
 @param parCoord la coordonnée
 @param parPrec  la trace précédente
 @param parSuiv  la trace suivante

 @return un pointeur sur le nouvelle trace
 */
trace * initTrace(long parDate, point parCoord, trace * parPrec, trace * parSuiv)
{
	trace * varT = createTrace();
	varT->date			= parDate;
	varT->coord			= parCoord;
	varT->prec			= parPrec;
	varT->suiv			= parSuiv;
	varT->visibilite	= 1;
	return varT;
}


/**
 affiche le contenu de la trace

 @param parT la trace
 */
void afficheTrace(trace * parT)
{
	printf("--------------------------------\n");
	printf("date :       %s\n",timestampToString(parT->date));
	printf("Coordonées : %lf, %lf\n",parT->coord.x, parT->coord.y);
	printf("--------------------------------\n");
}
