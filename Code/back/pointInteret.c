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
	varListe->id		        = 1;
	varListe->taille	        = TAILLE_TAB_DYN;
	varListe->occupee	        = 0;
	varListe->importance_max    = 0;
	varListe->t			        = calloc(varListe->taille, sizeof(pt_interet*));
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


liste_pt_interet * calculPointInteretSpatial(trajet * parTr)
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
		if (it->visibilite == 0)
		{
			continue;
		}
		pt_interet * varNvPtInt;
		varC.centre = it->coord;
		//(isInCercle(varC, it->suiv->coord)) > 0
		if (dis2points(varC.centre, it->suiv->coord, varC.rayon) > 0) //si le pt suivant est dans le cercle
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
	return varListe;
}

liste_pt_interet * calculPointInteretTemp(trajet * parTr)
{
	liste_pt_interet * varListe = calculPointInteretSpatial(parTr);
	cercle varC;
	int i;
	int j;
	int k = 0;
	for (i = 0; i < varListe->occupee; i++)
	{
		varC.centre.x = varListe->t[i]->position.x;
		varC.centre.y = varListe->t[i]->position.y;
		for (j = i + 1 ; j < varListe->occupee; j++)
		{
			if (dis2points(varC.centre, varListe->t[j]->position, varC.rayon))
			{
				varListe->t[i] = fusionPtInteret(varListe->t[i], varListe->t[j]);
				for (k = j; k < varListe->occupee; k++)
				{
					if (varListe->importance_max < varListe->t[k]->importance)
					{
						varListe->importance_max = varListe->t[k]->importance;
					}
					varListe->t[k] = varListe->t[k + 1];
				}
				varListe->occupee--;
				j--;
			}
		}
	}
	return varListe;
}

pt_interet * fusionPtInteret(pt_interet * parPtInt1, pt_interet * parPtInt2)
{
	int importance = parPtInt1->importance + parPtInt2->importance;
	time_t varDbt;
	time_t varFin;
	if (parPtInt1->debut < parPtInt2->debut)
	{
		varDbt = parPtInt1->debut;
	}
	else
	{
		varDbt = parPtInt2->debut;
	}
	if (parPtInt1->fin < parPtInt2->fin)
	{
		varFin = parPtInt2->fin;
	}
	else
	{
		varFin = parPtInt1->fin;
	}
	point varP;
	varP.x = ((parPtInt1->position.x * parPtInt1->importance) + (parPtInt2->position.x * parPtInt2->importance)) / importance;
	varP.y = (parPtInt1->position.y + parPtInt2->position.y) / 2;
	pt_interet * varNvPtInt = initPointInteret(importance,
											   varDbt,
											   varFin,
											   varP,
											   *(initAdresse()));
	return varNvPtInt;
}

liste_pt_interet * calculPointInteretFreq(trajet * parTr)
{
	liste_pt_interet * varListe = initListePointInteret();
	point * varTab = calloc(parTr->taille, sizeof(point));
	int i;
	trace * it = parTr->premier;
	//remplissage du tableau
	for (i = 0; i < parTr->taille; i++)
	{
		varTab[i].x = it->coord.x;
		varTab[i].y = it->coord.y;
		it = it->suiv;
	}
	/*for (i = 0; i < parTr->taille; i++)
	{
		affichePoint(varTab[i]);
	}*/
	//tri du tableau suivant x puis y
	quicksortLat(varTab, parTr->taille);
	int j = 0;
	int k;
	while (j < parTr->taille)
	{
		if (j > parTr->taille) break;
		printf("j:%d\n",j);
		i = 0;
		point * tmp;
		while (varTab[i].x == varTab[i+1].x)
		{
			//printf("%lf:%lf\n",varTab[i].x,varTab[i+1].x);
			i++;
		}
		printf("i:%d\n",i);
		tmp = calloc(i, sizeof(point));
		for (k = 0; k < i; k++)
		{
			tmp[k] = varTab[j+k];
		}

		quicksortLon(tmp, i);
		for (k = 0; k < i; k++)
		{
			varTab[j+k] = tmp[k];
		}
		j += i;
		free(tmp);
	}


	int n = 0;
	int m;
	while (n < parTr->taille)
	{
		m = 0;
		while ((varTab[m+n].x == varTab[m+n+1].x) && (varTab[m+n].y == varTab[m+n+1].y))
		{
			m++;

		}
		if (m > parTr->taille/10)
		{
			ajoutPointInteret(varListe, initPointInteret(m, 0, 1, varTab[n], *(initAdresse())));
			n += m;
		}
		else
		{
			n++;
		}

	}

	return varListe;
}

/**
 fonction de sauvegarde des points d'interet dans un fichier Liste_pt_interet

 @param parArrPtInteret la liste de point d'interet à sauvgarder
 @return >0 si reussi, 0 si echec
 */
int savePointInteret(const liste_pt_interet parArrPtInteret)
{
	FILE * fd;
	//Compilation avec gcc: ../Data/savePtInteret.frj
	if((fd = fopen("../Data/savePtInteret.frj", "w+")) == NULL)
	{
		perror("Erreur à la création du fichier de sauvegarde de pt d'interet");
		return -1;
	}
	int i;
	for (i = 0; i < parArrPtInteret.occupee; i++)
	{
		fprintf(fd, "imp %d:deb %ld:fin %ld:lat %lf:lon %lf\n", parArrPtInteret.t[i]->importance, parArrPtInteret.t[i]->debut, parArrPtInteret.t[i]->fin, parArrPtInteret.t[i]->position.x, parArrPtInteret.t[i]->position.y);
	}
	fclose(fd);

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
		printf("%d",i);
		affichePtInteret(parArrPtIntrt->t[i]);
	}
}
