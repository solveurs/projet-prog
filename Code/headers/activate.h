#pragma once
#include "includes.h"

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
  GtkWidget     *frameEchelle;
  GtkWidget		*labelEchelle;
  GtkWidget		*selectCarte;

  GtkWidget 	*scrollCarte;
  GtkWidget 	*imgCarte;
}uiMain;

/* ===== Fonctions ===== */
void activate(GtkApplication *app, gpointer user_data);