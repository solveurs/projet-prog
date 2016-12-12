#include "headers/main.h"
//gcc main.c -D BACK -D FRONT -o test&& ./test

void debugBack(void);

void debugBack(void)
{
	//double x=655712, y=6664882;	//position INSA
	//lambert93ToGPS(&x,&y);
	//printf("long : %lf , lat: %lf\n",x, y);
	
	//La lecture d'un fichier de 450 traces + création du trajet + affichage = <8ms
//	FILE * fd = openGeoloc("/Users/frj/Documents/Code/Projet_prog_3a/Data/geoloc-logs.txt");
//	bdd_trace * fd_trace = readGeoloc(fd);
//	trajet * _trajet = fd_trace->trajet;
//	afficheTrajet(_trajet);
	point p = { .x = 0.1, .y = 0.1};
	point * varP = kmToGPS(p, 51);
	printf("dlat : %lf, dlon : %lf",varP->x,varP->y);
}

int main(int argc, char* argv[])
{
	clock_t debut, fin;
	debut = clock();
#ifdef FRONT
	printf("front\n");
	
#elif BACK
	printf("back\n");
		
#elif DEBUG
	printf("DEBUG\n");
	void (*fnDebug)(void);
	
	fnDebug = debugBack;
	fnDebug();
	
#endif
	//printf("toujours\n");
	fin = clock();
	//printf("Temps d'excution : %.2f ms \n",(double)(fin - debut) / (CLOCKS_PER_SEC/1000));
	return 0;
}
