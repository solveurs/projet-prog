#include "../headers/pointInteret.h"

pt_interet * createPointInteret(void)
{
	pt_interet* varPtInteret = malloc(sizeof(pt_interet));
	varPtInteret->debut					=	0;
	varPtInteret->fin					=	0;
	varPtInteret->importance			=	0;
	varPtInteret->position.x			=	0;
	varPtInteret->position.y			=	0;
	varPtInteret->adresse.code_postal	=	18000;
	varPtInteret->adresse.coord.x		=	0;
	varPtInteret->adresse.coord.y		=	0;
	strcpy(varPtInteret->adresse.nom_rue, "");
	varPtInteret->adresse.numero		=	0;
	return varPtInteret;
}
pt_interet * initPointInteret(int parImpor, time_t parDbt, time_t parFin, point parPt, adresse parAddr)
{
	pt_interet* varPtInteret = createPointInteret();
	varPtInteret->debut					=	parDbt;
	varPtInteret->fin					=	parFin;
	varPtInteret->importance			=	parImpor;
	varPtInteret->position				=	parPt;
	varPtInteret->adresse				=	parAddr;
	return varPtInteret;
}
liste_pt_interet * initListePointInteret(void)
{
	liste_pt_interet * varListe = malloc(sizeof(liste_pt_interet));
	varListe->taille	= TAILLE_TAB_DYN;
	varListe->occupee	= 0;
	varListe->t			=calloc(varListe->taille, sizeof(pt_interet*));
	return varListe;
}

void appendListePointInteret(liste_pt_interet * parListe)
{
	void* ptr_realloc = realloc(parListe->t, ++parListe->taille);
	if (ptr_realloc != NULL)
	{
		parListe->t = ptr_realloc;
		++parListe->taille;
	}
}

void ajoutPointInteret(liste_pt_interet * parListe, pt_interet * parPtInteret)
{
	if (parListe->taille==parListe->occupee)
	{
		appendListePointInteret(parListe);
	}
	parListe->t[parListe->occupee] = parPtInteret;
	++parListe->occupee;
}
//liste_pt_interet calculPointInteret(trajet * parTr)
//{
//	return NULL;
//}
