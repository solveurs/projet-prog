#pragma once
#include "includes.h"
#include "structures.h"

/* ===== Constantes ===== */
#define UI_TRACE_INITIALISE     1
#define UI_TRACE_OUVERT         1
#define UI_TRACE_FERME          0
#define UI_TRACE_ESPACEMENT 	  5
#define UI_TRACE_TAILLE_X		  400
#define UI_TRACE_TAILLE_Y		  300

/* ===== Structures ===== */
typedef struct s_TracesDetailsUI
{
  GtkWidget *widget;

  GtkWidget *boxPrincipale;
  GtkWidget *frameCouleur;
  GtkWidget *boutonModifierCouleur;
  GtkWidget *frameNom;
  GtkWidget *zoneEntry;
  GtkWidget *boxBoutonsTD;
  GtkWidget *boutonAppliquer;
  GtkWidget *boutonAnnuler;
} tdUI; // td = TracesDetails

typedef struct s_TracesItem
{
  // Comme c'est un item, le widget principal est une box.
  GtkWidget         *widget;
  tdUI*             details;
  int               interet;
  int               etat;
  int               visible;
  int               id;
  liste_pt_interet* ptrInteret;
  trajet*           ptrTrajet;
  GdkRGBA*          ptrCouleur;
        
  GtkWidget         *boxG;
  GtkWidget         *boxD;
  GtkWidget         *labelNom;
        
  GtkWidget         *boutonRoute;
  GtkWidget         *boutonInteret;
  GtkWidget         *boutonOption;
  GtkWidget         *boutonVisible;
  GtkWidget         *boutonSupprimer;
        
  GtkWidget         *imgRoute;
  GtkWidget         *imgInteret;
  GtkWidget         *imgOption;
  GtkWidget         *imgVisible;
  GtkWidget         *imgSupprimer;
} tracesItem;

typedef struct s_TracesUI
{
  GtkWidget *widget;

  GtkWidget *boxPrincipale;
  GtkWidget *frameTraces;
  GtkWidget *boutonImporter;
  GtkWidget *imgImport;
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
}confirmeTUI;
/* ===== Fonctions ===== */

void importer(GtkWidget* widget, gpointer user_data);
void ajoutItemTraces(GtkWidget* boxScroll, const char* nomTrajet, trajet* ptrTrajet);

int uiTraces(GtkWidget* widget, gpointer user_data);
void switchVisibilite(GtkWidget* widget, gpointer user_data);
void traceRoute(GtkWidget* widget, gpointer user_data);
void traceInteret(GtkWidget* widget, gpointer user_data);
void optionItemTraces(GtkWidget* widget, gpointer user_data);
void supprimeItemTraces(GtkWidget* widget, gpointer user_data);

void changeCouleur(GtkWidget* widget, gpointer user_data);
void appliquerTD(GtkWidget* widget, gpointer user_data);
void annulerTD(GtkWidget* widget, gpointer user_data);

void detruireFen(GtkWidget* widget, gpointer user_data);
void confirmeSupprItem(GtkWidget* widget, gpointer user_data);
