#include "../headers/trace.h"
#include "../headers/conversion.h"

trace * createTrace(void)
{
	trace * varT = (trace*)malloc(sizeof(trace));
	return varT;
}

void initTrace(trace * parT, long parDate, point parCoord, trace * parPrec, trace * parSuiv)
{
	if (parT == NULL)
	{
		parT = createTrace();
	}
	parT->date			= parDate;
	parT->coord			= parCoord;
	parT->prec			= parPrec;
	parT->suiv			= parSuiv;
	parT->visibilite	= 1;
}

trajet * initTrajet(void)
{
	trajet * varTr = (trajet*)malloc(sizeof(trajet));
	varTr->taille	=	0;
	varTr->visiblite=	1;
	varTr->premier	=	NULL;
	varTr->dernier	=	NULL;
	return varTr;
}

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

void supprimerTraceN(trajet * parTr, trace * parT, int parPos)
{
	if (parPos==1)
	{
		parTr->premier->suiv->prec = NULL;
		parTr->premier = parTr->premier->suiv;
	}
	else if (parPos > parTr->taille)
	{
		parTr->dernier->prec->suiv = NULL;
		parTr->dernier = parTr->dernier->prec;
	}
	else
	{
		trace* it = parTr->premier;
		int i;
		for (i = 0; i < parPos; i++)
			it = it->suiv;
		it->prec->suiv = it->suiv;
		it->suiv->prec = it->prec;
		free(it);
	}
}

void afficheTrace(trace * parT)
{
	printf("-----------------------\n");
	printf("date : %s\n",timestampToString(parT->date));
	printf("Coordonées : %lf, %lf\n",parT->coord.x, parT->coord.y);
	printf("-----------------------\n");
}

void afficheTrajet(trajet * parTr)
{
	trace* it;
	it = parTr->premier;
	while (it->suiv != NULL)
	{

		afficheTrace(it);
		it = it->suiv;
	}
}






