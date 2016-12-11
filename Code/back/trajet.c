/**
 @file trajet.c
 
 @brief fonctions relatives à la gestion des trajets
 */
#include "../headers/trajet.h"



/**
 initialisation d'un trajet

 @return un pointeur sur le nouveau trajet
 */
trajet * initTrajet(void)
{
	trajet * varTr = (trajet*)malloc(sizeof(trajet));
	varTr->taille	=	0;
	varTr->visiblite=	1;
	varTr->premier	=	NULL;
	varTr->dernier	=	NULL;
	return varTr;
}

/**
 ajouter une trace à un trajet

 @param parTr le trajet
 @param parT  la trace à ajouter
 */
void ajoutTrace(trajet * parTr, trace * parT)
{
	if (parTr->premier == NULL)
	{
		parTr->premier = parT;
		parTr->dernier = parT;
		parT->prec = NULL;
		parT->suiv = NULL;
	}
	else
	{
		parT->suiv = NULL;
		parT->prec = parTr->dernier;
		parTr->dernier->suiv = parT;
		parTr->dernier = parTr->dernier->suiv;
	}
	parTr->taille++;
}

/**
 supprimer la trace à la position N du trajet

 @param parTr  le trajet
 @param parPos la position de la trace à supprimer
 */
void supprimerTraceN(trajet * parTr, int parPos)
{
	trace* it;
	if (parPos==1)
	{
		it = parTr->premier;
		it->suiv->prec = NULL;
		parTr->premier = parTr->premier->suiv;
	}
	else if (parPos > parTr->taille)
	{
		it = parTr->dernier;
		it->prec->suiv = NULL;
		parTr->dernier = parTr->dernier->prec;
	}
	else
	{
		it = parTr->premier;
		int i;
		for (i = 0; i < parPos; i++)
			it = it->suiv;
		it->prec->suiv = it->suiv;
		it->suiv->prec = it->prec;
	}
	free(it);
}

/**
 afficher un trajet complet

 @param parTr le trajet à afficher
 */
void afficheTrajet(trajet * parTr)
{
	trace* it;
	int i = 0;
	it = parTr->premier;
	while (it->suiv != NULL)
	{
		i++;
		printf("#%d\n",i);
		afficheTrace(it);
		it = it->suiv;
	}
}


/**
 suppression d'un trajet

 @param parTr le trajet
 */
void supprimerTrajet(trajet * parTr)
{
	while (parTr->premier != NULL)
	{
		supprimerTraceN(parTr, 1);
	}
	free(parTr);
}





