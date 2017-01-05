/**
 * @file      uiMain.c
 * @brief     Fichier main de la GUI de gestion des traces.
 * @author    Thanh.L, Guillaume.F
 *
 * C'est le fichier main du front.
 * On y declare et definit la structure globale utilisée dans toute la partie Front.
 * ====================
 *       TODO
 * ====================
 * + Gerer la liberation de la memoire
 * ====================
 *        MaJ
 * ====================
 * Creation du fichier
 *
*/

#include "../headers/front.h"

extern void activate(GtkApplication *app, gpointer user_data);

/*
int main (int argc, char **argv)
{
    GtkApplication *app;
    int status;

    initGlobFront();

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    //libereGlob();
    return status;
}
*/
void initGlobFront(void)
{
	int i;
	for(i=0; i<NOMBRE_MAX_TRAJETS; i++)
	{ //globFront est une structures ou une variable ??? -FRJ
		globFront.trajet[i] = (trajet *) malloc(sizeof(trajet));
		globFront.zoneDessinCher[i] = (GtkWidget *) malloc(sizeof(GtkWidget));
		globFront.zoneDessinBourges[i] = (GtkWidget *) malloc(sizeof(GtkWidget));
		globFront.zoneDessinInsa[i] = (GtkWidget *) malloc(sizeof(GtkWidget));
	}
	globFront.idTrajet = 0;

	/* Problemes au niveau de tes arguments ? J'ai des erreurs a la compilation*/
 	//globFront.carte_Cher = initCarte("../../Data/cartes/carte_Cher.png", 1013, 1920, 47.988083, 1.726227, 46.194092, 3.115997);
 	//globFront.carte_Bourges = initCarte("../../Data/cartes/carte_Bourges.png", 1850, 1079, 47.113540, 2.313738, 47.050476, 2.472610);
 	//globFront.carte_Insa = initCarte("../../Data/cartes/carte_Insa.png", 1850, 1080, 47.088723, 2.392981, 47.072957, 2.432764);
}

void libereGlob(void)
{
	/* Quelques erreurs, je dois encore reverifier les mallocs
	int i;
	for(i=0; i<NOMBRE_MAX_TRAJETS; i++)
	{
		free(globFront.trajet[i]);
		free(globFront.zoneDessinCher[i]);
		free(globFront.zoneDessinBourges[i]);
		free(globFront.zoneDessinInsa[i]);
	}
	*/
}
