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
	GtkWidget 	*ssMenuItem1_1;
	GtkWidget 	*ssMenuItem1_2;

	GtkWidget 	*ssMenuItem2;
	GtkWidget 	*ssMenuItem2_1;
	GtkWidget 	*ssMenuItem2_2;
	GtkWidget 	*ssMenuItem2_3;

	GtkWidget 	*ssMenuItem3;
	GtkWidget 	*ssMenuItem3_1;
	GtkWidget 	*ssMenuItem3_2;

	GtkWidget 	*ssMenuItem4;

	GtkWidget *frameEntete;
	GtkWidget	*boxEntete;

	GtkWidget *boxUI;
	GtkWidget	*boutonBoxTraces;
	GtkWidget	*boutonBoxAnim;
	GtkWidget	*boutonBoxAnon;
	GtkWidget *boutonTraces;
	GtkWidget *boutonAnimation;
	GtkWidget *boutonAnonymat;

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
int overlayTempAjout(GtkWidget* zoneCercle, GtkWidget* eventBox, int id);
void overlayTempSuppr(GtkWidget* eventBox, int id);
void bloqueCarte(int mode);
void debloqueCarte(int mode);
int getCarte();
void getPosSouris(GtkWidget* widget, GdkEvent *event, gpointer user_data);
void focusTrajet(int carte, int id);
void defocusTrajet(int carte, int id);

void affUITraces();
void affUIAnim();
void affUIAnon();
