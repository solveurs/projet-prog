/**
 @file fonctionFront.c
 
 @brief interface entre le Back et le Front, je met I devant mes fonctions pour dire que c'est des interfaces
 */
#include "../headers/fonctionFront.h"

/*
+fonction importation trace (open file...) --> trajet (affiche la trace)
  
+anonymisation des traces (
	-manuel(zone[cercle]) -->supprime les traces dans le cercle
	-
 
+Lecture trace
	-pause avec une step
	-bouton de recule et avancer
	-->A voir si on ajoute une variable de visibilité (1 visible et 0 invisible)
	-fonction de jump
	-fonction accessuer taille max de la trace

+fonction de detection point d'interet
 
+Fonction de suggestion de point d'anonymisation

*/

trajet * IimportTrajet(const char * nom);

liste_pt_interet* IgetPtInteret(trajet * parTr);

trajet * IlectureTrace(int parCmd, trajet * parTr);

trajet * IanonymisationC(const trajet parTr, const cercle parCercleAno);

trajet * IanonymisationP(const trajet parTr, const int parIdTraceAno);

trajet * IanonymisationR(const trajet parTr, const rectangle parRectAno);

liste_c_anonym * IsuggestAnonymisation();
