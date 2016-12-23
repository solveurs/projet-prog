#pragma once
#include "includes.h"

/* ===== Constantes ===== */
#define UI_ANIM_ESPACEMENT   5
#define UI_ANIM_OUVERT      1
#define UI_ANIM_FERME       0
#define UI_ANIM_TAILLEX      500
#define UI_ANIM_TAILLEY      150

/* ===== Structures ===== */

typedef struct s_date
{
  int jour;
  int mois;
  int annee;
}dateAnim;

typedef struct s_AnimUI
{
  GtkWidget   *widget;
  char        buffer[11];
  dateAnim    *dateDeb;
  dateAnim    *dateFin;

  GtkWidget   *boxPrincipale;

  GtkWidget   *frameDate;
  GtkWidget   *boxFrame;
    // Calendriers
  GtkWidget   *boxPH;
      // Gauche == Debut
  GtkWidget   *gridPHG;
  GtkWidget   *labelPHG;
  GtkWidget   *entryZoneDeb;
  GtkWidget   *boutonCalG;
      // Droite == Fin
  GtkWidget   *gridPHD;
  GtkWidget   *labelPHD;
  GtkWidget   *entryZoneFin;
  GtkWidget   *boutonCalD;
    // Vitesse
  GtkWidget   *boxPB;
  GtkWidget   *label;
  GtkWidget   *vitesse;

  GtkWidget   *boxBoutons;
  GtkWidget   *boutonArriere;
  GtkWidget   *boutonStop;
  GtkWidget   *boutonPlay;
  GtkWidget   *boutonAvance;

  GtkWidget   *select;

  GtkWidget   *boxAffichage;
  GtkWidget   *caseG;
  GtkWidget   *caseD;
} animUI;

typedef struct s_Calendrier
{
  GtkWidget *widget;

  GtkWidget *boxPrincipale;

  GtkWidget *calendrier;

  GtkWidget *boxBoutons;
  GtkWidget *boutonAnnuler;
  GtkWidget *boutonConfirmer;
}calUI;


/* ===== Fonctions ===== */
int uiAnimation(GtkWidget* widget, gpointer user_data);
void setCalendrier(GtkWidget* widget, gpointer user_data);
void annulerCal(GtkWidget* widget, gpointer user_data);
void confirmerCal(GtkWidget* widget, gpointer user_data);