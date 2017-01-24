#pragma once
#include "includes.h"
#include "uiTraces.h"
#include "globalFront.h"
#include "fctnCairo.h"

/* ===== Constantes ===== */
#define UI_MAIN_ESPACEMENT 	  	5
#define UI_MAIN_TAILLE_X		  800
#define UI_MAIN_TAILLE_Y		  600

/* ===== Structures ===== */
typedef struct s_uiPrincipale
{
	GtkWidget 	*widget; //c'est l'application
	GtkWidget 	*boxPrincipale;

	GtkWidget 	*boxMenu;
	GtkWidget 	*menuBarre;
	GtkWidget 	*ssMenu1;
	GtkWidget 	*ssMenu2;
	GtkWidget 	*ssMenu3;
	GtkWidget 	*ssMenu4;
	GtkWidget 	*ssMenuItem1;
	GtkWidget 	*ssMenuItem2;
	GtkWidget 	*ssMenuItem3;
	GtkWidget 	*ssMenuItem4;
	GtkWidget 	*ssMenuItem5;
	GtkWidget 	*ssMenuItem6;
	GtkWidget 	*ssMenuItem7;
	GtkWidget 	*ssMenuItem8;
	GtkWidget 	*ssMenuItem9;

	GtkWidget 	*frameEntete;
	GtkWidget	*boxEntete;

	GtkWidget 	*boxUI;
	GtkWidget	*boutonBoxTraces;
	GtkWidget	*boutonBoxAnim;
	GtkWidget	*boutonBoxAnon;
	GtkWidget 	*boutonTraces;
	GtkWidget 	*boutonAnimation;
	GtkWidget 	*boutonAnonymat;
	
	GtkWidget	*boxCarte;
	GtkWidget	*frameCarte;
	GtkWidget	*imgCarte;
	GtkWidget	*selectCarte;

	GtkWidget	*boxEventCher;
	GtkWidget	*boxEventBourges;
	GtkWidget	*boxEventInsa;
	GtkWidget	*boxScrolls;
	GtkWidget 	*scrollCarteCher;
	GtkWidget   *scrollCarteBourges;
	GtkWidget   *scrollCarteInsa;
	GtkWidget 	*imgCarteCher;
	GtkWidget   *imgCarteBourges;
	GtkWidget   *imgCarteInsa;

	GtkWidget	*boxFooter;
	GtkWidget	*labelPos;
}uiMain;

/* ===== Fonctions ===== */
void activate(GtkApplication *app, gpointer user_data);
void ajoutOverlays(tracesItem* ptrItem);
void changeCarte(GtkWidget *widget, gpointer user_data);
void bougeCarte(GtkWidget *widget, gpointer user_data);
int overlayTempAjout(GtkWidget* zoneCercle, GtkWidget* eventBox, int id);
void overlayTempSuppr(GtkWidget* eventBox, int id);
void bloqueCarte();
void debloqueCarte();
<<<<<<< HEAD
int getCarte();
void getPosSouris(GtkWidget* widget, GdkEvent *event, gpointer user_data);
=======
>>>>>>> a60ad3c2c67718922d1a94162570743ce8447f91
