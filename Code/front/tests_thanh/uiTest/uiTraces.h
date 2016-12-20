#pragma once
#include "includes.h"

/* ===== Constantes ===== */
#define UI_TRACE_INITIALISE   1
#define UI_TRACE_OUVERT       1
#define UI_TRACE_FERME        0
#define UI_TRACE_ESPACEMENT 	5
#define UI_TRACE_TAILLEX		  300
#define UI_TRACE_TAILLEY		  150

/* ===== Structures ===== */
typedef struct s_TracesDetailsUI
{
  GtkWidget *widget;

  GtkWidget *boxTD;
  GtkWidget *frameCouleur;
  GtkWidget *boutonModifierCouleur;
  GtkWidget *frameNom;
  GtkWidget *zoneEntry;
  GtkWidget *boxBoutonsTD;
  GtkWidget *boutonBoxAppliquer;
  GtkWidget *boutonBoxAnnuler;
  GtkWidget *boutonAppliquer;
  GtkWidget *boutonAnnuler;
} tdUI; // td = TracesDetails

typedef struct s_TracesItem
{
  // Comme c'est un item, le widget principal est une box.
  GtkWidget *widgetBox;
  tdUI      *details;
  int       etat;

  GtkWidget *boxG;
  GtkWidget *boxD;
  GtkWidget *labelNom;
  GtkWidget *boutonRoute;
  GtkWidget *boutonOption;
  GtkWidget *boutonVisible;
  GtkWidget *boutonSupprimer;

  //trace     *ptrTrace; //Je l'ajouterai a la fusion avec le back.
  int        couleur; 
} tracesItem;

typedef struct s_TracesUI
{
  GtkWidget *widget;

  GtkWidget *boxTraces;
  GtkWidget *frameTraces;
  GtkWidget *boutonBoxImporter;
  GtkWidget *boutonImporter;
  GtkWidget *zoneScroll;
  GtkWidget *zoneScrollBox;
} tracesUI;

typedef struct s_confirmationTracesUI
{
  GtkWidget *widget;

  GtkWidget *boxPrincipale;
  GtkWidget *labelTxt;
  GtkWidget *boxBoutons;
  GtkWidget *boutonAnnuler;
  GtkWidget *boutonConfirmer;
  GtkWidget *boxAnnuler;
  GtkWidget *boxConfirmer;
}confirmeTUI;
/* ===== Fonctions ===== */

char* importer(GtkWidget* widget, gpointer user_data);
int uiTraces(GtkWidget* widget, gpointer user_data);

void afficheTraces(GtkWidget* widget, gpointer user_data);
void ajoutItemTraces(GtkWidget* widget, gpointer user_data);
void appliquerTD(GtkWidget* widget, gpointer user_data);
void annulerTD(GtkWidget* widget, gpointer user_data);
void detruireFen(GtkWidget* widget, gpointer user_data);
void confirmeSupprItem(GtkWidget* widget, gpointer user_data);
void supprimeItemTraces(GtkWidget* widget, gpointer user_data);
void traceRoute(GtkWidget* widget, gpointer user_data);
void optionItemTraces(GtkWidget* widget, gpointer user_data);

