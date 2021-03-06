/**
 @file parserBddGeoloc.c
 
 @brief Ouverture et traintement du fichier de trace geoloc
 */
#include "../headers/parserBddGeoloc.h"



/**
 ouverture d'un fichier de log geoloc

 @param nom chemin vers le fichier

 @return un descripteur de fichier ouvert
 */
FILE * openGeoloc(const char * nom)
{
	FILE * fd = NULL;
	if((fd = fopen(nom,"r")) == NULL)
	{
		perror("Erreur d'ouverture de la bdd geoloc\n");
	}
	return fd;
}

/**
 ouverture d'une bdd geoloc

 @param parFd le descripteur sur le fichier de log geoloc

 @return un pointeur du bdd_trace
 */
bdd_trace * readGeoloc(FILE * parFd)
{
	bdd_trace * varBddTrace = (bdd_trace*)malloc(sizeof(bdd_trace));
	long date;
	double lat,lon;
	varBddTrace->trajet = initTrajet();
	strcpy(varBddTrace->chemin," ");
	varBddTrace->visibilite = 0;
	
	while (fscanf(parFd,"date:%ld,lat:%lf,long:%lf;\n",&date,&lat,&lon) > 0)
	{
		point p;
		p.x = lat;
		p.y = lon;
		trace * varT = initTrace(0,date,p,NULL,NULL);
		ajoutTrace(varBddTrace->trajet, varT);
		//printf("%d \n", varBddTrace->trajet->taille);
	}
	return varBddTrace;
}
