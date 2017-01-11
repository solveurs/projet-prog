#pragma once
#include "includes.h"
#include "structures.h"

/* ===== Constantes ===== */
#define UI_ANON_ESPACEMENT      5
#define UI_ANON_OUVERT  	      1
#define UI_ANON_FERME           0
#define UI_ANON_TAILLE_X      250
#define UI_ANON_TAILLE_Y      300

/* ===== Structures ===== */

typedef struct s_AnonDetails
{
  GtkWidget *widget;
  GtkWidget *boxPrincipale;

  GtkWidget *frameNom;
  GtkWidget *boxFrame;
  GtkWidget *entryZone;
  GtkWidget *boutonAppliquer;

  GtkWidget *boutonModifier;
}adUI;

typedef struct s_AnonymiteItem
{
  GtkWidget *widget; // Le widget est une box car c'est un item
  adUI      *details;
  int       couleur;
  int		    etat;
  int       id;
  double    rayon;
  point     coord;

  GtkWidget *boxG;
  GtkWidget *labelNom;

  GtkWidget *boxD;

  GtkWidget *boutonVisible;
  GtkWidget *boutonOption;
  GtkWidget *boutonSupprimer;
} anonItem;

typedef struct s_Anon
{
  GtkWidget *widget;
  GtkWidget *boxPrincipale;

  GtkWidget *boutonCercle;
  GtkWidget *imgCercle;

  GtkWidget *boxTracer;
  GtkWidget *labelInfo;
  GtkWidget *boxBoutons;
  GtkWidget *boutonConfirmer;
  GtkWidget *boutonAnnuler;

  GtkWidget *frameCible;
  GtkWidget *menuDeroulant;

  GtkWidget *frameScroll;
  GtkWidget *zoneScroll;
  GtkWidget *boxItem;
}uiAnon;

/* ===== Fonctions ===== */
int uiAnonymite(GtkWidget* widget, gpointer user_data);
void ajoutItemAnon(GtkWidget* widget, gpointer user_data);
void optionItemAnon(GtkWidget* widget, gpointer user_data);
void traceCercle(GtkWidget* widget, gpointer user_data);

void ajoutMenuTraces(const gchar* nom);
void supprimeMenuTraces(gint id);
void renommeMenuTraces(gint id, const gchar* nom);
