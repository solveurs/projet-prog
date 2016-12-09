#include "../headers/parserBddGeoloc.h"

FILE * openGeoloc(const char * nom)
{
	FILE * fd;
	if((fd = fopen(nom,"r")) == NULL)
	{
		perror("Erreur d'ouverture de la bdd geoloc\n");
	}
	return fd;
}

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
		trace * varT = createTrace();
		initTrace(varT,date,p,NULL,NULL);
		ajoutTrace(varBddTrace->trajet, varT);
		//printf("%d \n", varBddTrace->trajet->taille);
	}
	return varBddTrace;
}
