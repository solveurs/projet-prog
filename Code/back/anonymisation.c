#include "../headers/anonymisation.h"

int anonymisationPendantEditionC(trajet * parTr, const cercle parC)
{
	int nb = 0;
	int na = 0;
	trace * it = parTr->premier;
	while (it->suiv != NULL)
	{
		int tmp = isInCercle(parC, it->coord);
		if(tmp>0)
		{
			it->visibilite = 0;
			nb++;
		}
		else
		{
			na++;
		}
		it = it->suiv;
	}
	printf("\n%d", na);
	return nb;
}

int anonymisationPendantEditionR(trajet * parTr, const rectangle parR)
{
	int nb = 0;
	trace * it = parTr->premier;
	while (it->suiv != NULL)
	{
		if (isInRectangle(parR, it->coord))
		{
			it->visibilite = 0;
			nb++;
		}
		it = it->suiv;
	}
	return nb;
}

int anonymisationPendantEditionT(trajet * parTr, const int parIdTrace)
{
	trace * it = parTr->premier;
	while (it->suiv != NULL)
	{
		if (it->id == parIdTrace)
		{
			it->visibilite = 0;
		}
		it = it->suiv;
	}
	return 1;
}

int anonymisationApresEdition(trajet * parTr)
{
	int nb = 0;
	int i = 1;
	trace * it = parTr->premier;
	while (it->suiv != NULL)
	{
		if (it->visibilite == 0)
		{
			supprimerTraceN(parTr, i);
			nb++;
			i--;
		}
		i++;
		it = it->suiv;
	}
	return nb;
}

bdd_trace * saveTrajetAnonymise(trajet parTr, const char * chemin, const int visibilite)
{
	bdd_trace * varBddTrace = (bdd_trace*)malloc(sizeof(bdd_trace));
	strcpy(varBddTrace->chemin, chemin);
	varBddTrace->visibilite = visibilite;
	varBddTrace->trajet = &parTr;
	saveTrajet(varBddTrace->trajet, varBddTrace->chemin);
	return varBddTrace;
}










