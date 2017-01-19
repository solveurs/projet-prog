/**
 @file fonctionFront.c
 
 @brief interface entre le Back et le Front, je met I devant mes fonctions pour dire que c'est des interfaces
 */
#include "../headers/fonctionFront.h"

/*
+fonction importation trace (open file...) --> trajet (affiche la trace)
 
+anonymisation des traces (
	-manuel(zone[cercle]) -->plutôt que de les affacés, le temps que l'on est en mode édition on met la visiblité des points à 0. A la fin de l'édition on créé un trajet avec les points dont la visibilté est à 1.
	- Proposer de sauvegarder le trajet
 
+Lecture trace
	-pause avec une step
	-bouton de recule et avancer
	-->A voir si on ajoute une variable de visibilité (1 visible et 0 invisible)
	-fonction de jump
	-fonction accessuer taille max de la trace

+fonction de detection point d'interet
 
+Fonction de suggestion de point d'anonymisation

*/

trajet * IimportTrajet(const char * nom)
{
	bdd_trace * varBddTrace = readGeoloc(openGeoloc(nom));
	return varBddTrace->trajet;
}

liste_pt_interet* IgetPtInteret(trajet * parTr)
{
	return calculPointInteretTemp(parTr);
}

int IlectureTrace(int parCmd, trajet * parTr)
{
	switch (parCmd)
	{
		case 0: //on fait une lecture simple
			
			return 1;
			break;
		case 1: //on fait une lecture point par point
			
			break;
		case 2: //on fait une lecture inverse
			
			break;
		default:
			break;
	}
	return -1;
}

void IModeAnonymisation();

void IfinModeAnonymisation(const trajet parTr)
{
	IsaveAnonymisation(parTr, "");
}

void IsaveAnonymisation(const trajet parTr, const char * chemin)
{
	saveTrajetAnonymise(parTr, chemin, 1);
}

void IanonymisationC(trajet * parTr, const cercle parCercleAno)
{
	anonymisationPendantEditionC(parTr, parCercleAno);
}

void IanonymisationP(trajet * parTr, const int parIdTraceAno)
{
	anonymisationPendantEditionT(parTr, parIdTraceAno);
}

void IanonymisationR(trajet * parTr, const rectangle parRectAno)
{
	anonymisationPendantEditionR(parTr, parRectAno);
}

liste_c_anonym * IsuggestAnonymisation();





