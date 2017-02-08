#include "headers/main.h"
//gcc main.c back/anonymisation.c back/conversion.c back/fonctionFront.c back/parserBddGeoloc.c back/pointInteret.c back/trace.c back/trajet.c back/utils.c back/ia.c -o main -Wall && ./main
struct globFront varGlobFront;

#define DEBUG 1

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
	//void (*fnDebug)(void);

	//fnDebug = debugBack;
	debugBack();
	//debugFront(argc,argv);

#endif
	//printf("toujours\n");
	fin = clock();
	printf("Temps d'execution : %.2f ms \n",(double)(fin - debut) / (CLOCKS_PER_SEC/1000));
	return 0;
}

void debugBack(void)
{
	//double x=655712, y=6664882;	//position INSA
	//lambert93ToGPS(&x,&y);
	//printf("long : %lf , lat: %lf\n",x, y);

	//La lecture d'un fichier de 450 traces + création du trajet + affichage = <8ms

	FILE * fd = openGeoloc("../Data/geoloc-logs.txt");
	bdd_trace * fd_trace = readGeoloc(fd);
	trajet * _trajet = fd_trace->trajet;
	afficheTrajet(_trajet);
	//liste_pt_interet * _listePtInteret = calculPointInteretTemp(_trajet);
	liste_pt_interet * _listePtInteret = calculPointInteretTemp(_trajet);
	afficheArrPtInteret(_listePtInteret);
	savePointInteret(*_listePtInteret);
	printf("Distance du trajet : %f", distanceTrajet(*_trajet));

	//	point p = { .x = 0.1, .y = 0.1};
	//	point * varP = kmToGPS(p, 51);
	//	printf("dlat : %lf, dlon : %lf",varP->x,varP->y);
	printf("\n\n\n TEST ADDR TEST ADDR \n\n\n");
	//Initialisation
	
	FILE * fd2 = pretreat_bddaddr("../Data/ADRESSE.csv","../Data/ADRESSE2.csv");
	printf("\n Apres pretreatBddAddr\n");
	bdd_addr * base_addr = readAddr(fd2);
	FILE * fd3 = openBddAddr("../Data/bdd_adresse.csv");
	write_infixe_bddAddr(base_addr, fd3);
	fclose(fd2);
	fclose(fd3);
	
	//Si déjà initialisée
	/*
	FILE * fd2 = openGeoloc("../Data/bdd_adresse.txt");
	bdd_addr * base_addr = readAddr2(fd2);
	fclose(fd2);
	FILE * fd3 = openBddAddr("../Data/bdd_adresse.txt");
	write_infixe_bddAddr(base_addr, fd3);
	fclose(fd3);
	*/
	printf("\n\n\n TEST ADDR TEST ADDR FINI \n\n\n");
}

void debugFront(int argc, char* argv[])
{
	GtkApplication *app;

	initGlobFront();

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
	g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	//libereGlob();
}

void initGlobFront(void)
{
	int i;
	for(i=0; i<NOMBRE_MAX_TRAJETS; i++)
	{ //varGlobFront est une structures ou une variable ??? -FRJ
		varGlobFront.zoneDessinCher[i] = (GtkWidget *) malloc(sizeof(GtkWidget));
		varGlobFront.zoneDessinBourges[i] = (GtkWidget *) malloc(sizeof(GtkWidget));
		varGlobFront.zoneDessinInsa[i] = (GtkWidget *) malloc(sizeof(GtkWidget));
	}
	varGlobFront.idTrajet = 0;

	/* Problemes au niveau de tes arguments ? J'ai des erreurs a la compilation*/
	//varGlobFront.carte_Cher = initCarte("../../Data/cartes/carte_Cher.png", 1013, 1920, 47.988083, 1.726227, 46.194092, 3.115997);
	//varGlobFront.carte_Bourges = initCarte("../../Data/cartes/carte_Bourges.png", 1850, 1079, 47.113540, 2.313738, 47.050476, 2.472610);
	//varGlobFront.carte_Insa = initCarte("../../Data/cartes/carte_Insa.png", 1850, 1080, 47.088723, 2.392981, 47.072957, 2.432764);
}

void libereGlob(void)
{
	/* Quelques erreurs, je dois encore reverifier les mallocs
	 int i;
	 for(i=0; i<NOMBRE_MAX_TRAJETS; i++)
	 {
		free(varGlobFront.trajet[i]);
		free(varGlobFront.zoneDessinCher[i]);
		free(varGlobFront.zoneDessinBourges[i]);
		free(varGlobFront.zoneDessinInsa[i]);
	 }
	 */
}
