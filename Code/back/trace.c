#include "../headers/trace.h"

trace * createTrace(void)
{
	trace * varT = (trace*)malloc(sizeof(trace));
	return varT;
}

void initTrace(trace * parT, double parDate, point parCoord, trace * parPrec, trace * parSuiv)
{
	if (parT == NULL)
	{
		parT = createTrace();
	}
	parT->date	= parDate;
	parT->coord = parCoord;
	parT->prec	= parPrec;
	parT->suiv	= parSuiv;
}

trajet * initTrajet(void)
{
	trajet * varTr = (trajet*)malloc(sizeof(trajet));
	varTr->taille	=	0;
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
		parT->prec = NULL
		parT->suiv = NULL;
	}
	parT->suiv = NULL;
	parT->prec = parTr->dernier;
	parTr->dernier->suiv = parT;
	parTr->dernier = parTr->dernier->suiv;
	parTr->taille++;
}
