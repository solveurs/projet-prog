#include "headers/main.h"
//gcc main.c -D BACK -D FRONT -o test&& ./test

void debugBack(void);

void debugBack(void)
{
	//double x=655712, y=6664882;	//position INSA
	//lambert93ToGPS(&x,&y);
	//printf("long : %lf , lat: %lf\n",x, y);
	
	//printf("Date de %d : %s \n",1477070408,timestampToString(1477070408));
	FILE * fd = openGeoloc("/Users/frj/Documents/Code/Projet_prog_3a/Data/geoloc-logs.txt");
	bdd_trace * fd_trace = readGeoloc(fd);
	trajet * _trajet = fd_trace->trajet;
	//afficheTrace(_trajet->premier);
	afficheTrajet(_trajet);
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
	printf("Temps d'excution : %.2f ms \n",(double)(fin - debut) / (CLOCKS_PER_SEC/1000));
	return 0;
}
