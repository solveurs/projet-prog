/**
 @file pointInteret.c
 @brief fonctions relatives à la création, au calcul et sotckage de point d'interet
 */
#include "../headers/pointInteret.h"


/**
 Creer un nouveau point d'interet

 @return un pointeur sur pt_interet
 */
pt_interet * createPointInteret(void)
{
	pt_interet* varPtInteret = malloc(sizeof(pt_interet));
	varPtInteret->id					=	0;
	varPtInteret->debut					=	0;
	varPtInteret->fin					=	0;
	varPtInteret->importance			=	0;
	varPtInteret->position.x			=	0;
	varPtInteret->position.y			=	0;
	varPtInteret->adresse				=	*(initAdresse());
//	varPtInteret->adresse.code_postal	=	18000;
//	varPtInteret->adresse.coord.x		=	0;
//	varPtInteret->adresse.coord.y		=	0;
//	strcpy(varPtInteret->adresse.nom_rue, "");
//	varPtInteret->adresse.numero		=	0;
	return varPtInteret;
}

/**
 initialise un point d'interet

 @param parImpor l'importance
 @param parDbt   la date de debut
 @param parFin   la date de fin
 @param parPt    la coordonnée
 @param parAddr  l'adresse

 @return un pointeur sur pt_interet
 */
pt_interet * initPointInteret(int parImpor, time_t parDbt, time_t parFin, point parPt, adresse parAddr)
{
	static int varPtId = 0;
	pt_interet* varPtInteret = createPointInteret();
	varPtInteret->id					=	varPtId;
	varPtInteret->debut					=	parDbt;
	varPtInteret->fin					=	parFin;
	varPtInteret->importance			=	parImpor;
	varPtInteret->position				=	parPt;
	varPtInteret->adresse				=	parAddr;
	varPtId++;
	return varPtInteret;
}


/**
 initialise une liste de point d'interet

 @return un tableau dynamique de pointeur de point d'interet
 */
liste_pt_interet * initListePointInteret(void)
{
	//static int varArrId = 0;
	liste_pt_interet * varListe = malloc(sizeof(liste_pt_interet));
	varListe->id		= 1;
	varListe->taille	= TAILLE_TAB_DYN;
	varListe->occupee	= 0;
	varListe->t			=calloc(varListe->taille, sizeof(pt_interet*));
	//varArrId++;
	return varListe;
}


/**
 Ajoute une case dynamiquement au tableau

 @param parListe la liste de point d'interet
 */
void appendListePointInteret(liste_pt_interet * parListe)
{
	void* ptr_realloc = realloc(parListe->t, ++parListe->taille);
	if (ptr_realloc != NULL)
	{
		parListe->t = ptr_realloc;
		++parListe->taille;
	}
}


/**
 Ajoute un point d'interet à la liste

 @param parListe     le tableau
 @param parPtInteret le point d'interet
 */
void ajoutPointInteret(liste_pt_interet * parListe, pt_interet * parPtInteret)
{
	if (parListe->taille==parListe->occupee)
	{
		appendListePointInteret(parListe);
	}
	parListe->t[parListe->occupee] = parPtInteret;
	++parListe->occupee;
}


liste_pt_interet * calculPointInteret(trajet * parTr)
{
	liste_pt_interet * varListe = initListePointInteret();
	cercle varC;
	varC.centre.x = 0;
	varC.centre.y = 0;
	varC.rayon = RAYON_CERCLE_PT_INT_KM;
	int nvPtInteret = 1;
	
	
	//Premiere boucle de parcours simple du trajet (repere les points où la personne passe du temps directement
	trace * it;
	it = parTr->premier;
	while (it->suiv != NULL)
	{
		pt_interet * varNvPtInt;
		varC.centre = it->coord;
		//(isInCercle(varC, it->suiv->coord)) > 0
		if (dis2points(varC.centre, it->suiv->coord, RAYON_CERCLE_PT_INT_KM) > 0) //si le pt suivant est dans le cercle
		{
			if (nvPtInteret > 0) //si il est un noueau point d'interet
			{
				nvPtInteret = 0;
				varNvPtInt = initPointInteret(1, it->date, it->date, it->coord, *(initAdresse()));
			}
			else
			{
				varNvPtInt->importance++;
				varNvPtInt->fin = it->date;
				point nvPos = varNvPtInt->position;
				nvPos.x += it->coord.x;
				nvPos.y += it->coord.y;
				varNvPtInt->position = nvPos;
			}
		}
		else
		{
			if (!(nvPtInteret > 0))
			{
				varNvPtInt->importance++;
				varNvPtInt->fin = it->date;
				point nvPos = varNvPtInt->position;
				nvPos.x += it->coord.x;
				nvPos.y += it->coord.y;
				nvPos.x /= varNvPtInt->importance;
				nvPos.y /= varNvPtInt->importance;
				varNvPtInt->position = nvPos;
				
				ajoutPointInteret(varListe, varNvPtInt);
				nvPtInteret = 1;
			}
		}
		it = it->suiv;
	}
	
	//Deuxieme boucle qui va reparcourir les points d'interet et les regroupés en plus gros
	return varListe;
}


/**
 fonction de sauvegarde des points d'interet dans un fichier Liste_pt_interet

 @param parArrPtInteret la liste de point d'interet à sauvgarder
 @return >0 si reussi, 0 si echec
 */
int savePointInteret(liste_pt_interet parArrPtInteret)
{
	
	return 1;
}

void affichePtInteret(pt_interet * parPtIntrt)
{
	printf("--------------------------------\n");
	printf("Id :			%d\n",parPtIntrt->id);
	printf("Importance :	%d\n",parPtIntrt->importance);
	affichePoint(parPtIntrt->position);
	printf("Heure de début :%s\n",timestampToString(parPtIntrt->debut));
	printf("Heure de fin :	%s\n",timestampToString(parPtIntrt->fin));
	printf("--------------------------------\n");
}

void afficheArrPtInteret(liste_pt_interet * parArrPtIntrt)
{
	int i;
	printf("Id liste : %d \n", parArrPtIntrt->id);
	printf("Taille occupee %d \n", parArrPtIntrt->occupee);
	for (i=0; i < parArrPtIntrt->occupee; i++)
	{
		affichePtInteret(parArrPtIntrt->t[i]);
	}
}











