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
  GtkWidget 	*ssMenuItem1;
  GtkWidget 	*ssMenuItem2;
  GtkWidget 	*ssMenuItem3;
  GtkWidget 	*ssMenuItem4;

  GtkWidget 	*frameEntete;
  GtkWidget		*boxEntete;

  GtkWidget 	*boxUI;
  GtkWidget		*boutonBoxTraces;
  GtkWidget		*boutonBoxAnim;
  GtkWidget		*boutonBoxAnon;
  GtkWidget 	*boutonTraces;
  GtkWidget 	*boutonAnimation;
  GtkWidget 	*boutonAnonymat;

  GtkWidget		*boxCarte;
  GtkWidget		*frameCarte;
  GtkWidget   *frameEchelle;
  GtkWidget		*labelEchelle;
  GtkWidget		*selectCarte;

  GtkWidget 	*scrollCarteCher;
  GtkWidget   *scrollCarteBourges;
  GtkWidget   *scrollCarteInsa;
  GtkWidget 	*imgCarteCher;
  GtkWidget   *imgCarteBourges;
  GtkWidget   *imgCarteInsa;
  /* Modification de Guillaume
  GtkWidget 	*scrollCarte;
  GdkPixbuf   *bufferCarte;
  GtkWidget 	*imgCarte;
  */
}uiMain;

/* ===== Fonctions ===== */
void activate(GtkApplication *app, gpointer user_data);
void ajoutOverlays(tracesItem* ptrItem);
void changeCarte(GtkWidget *widget, gpointer user_data);
void bougeCarte(GtkWidget *widget, gpointer user_data);