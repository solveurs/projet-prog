#pragma once
#include "includes.h"

/* ===== Constantes ===== */
#define UI_ANIM_ESPACEMENT      5
#define UI_ANIM_OUVERT          1
#define UI_ANIM_FERME           0
#define UI_ANIM_TAILLE_X      400
#define UI_ANIM_TAILLE_Y      100

/* ===== Structures ===== */

typedef struct s_AnimUI
{
  GtkWidget   *widget;
  GtkWidget   *calendrierDeb;
  GtkWidget   *calendrierFin;

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
  GtkWidget   *imgCalG;
  GtkWidget   *boxComboG;
  GtkWidget   *comboHG;
  GtkWidget   *comboMG;
  GtkWidget   *comboSG;
  // Droite == Fin
  GtkWidget   *gridPHD;
  GtkWidget   *labelPHD;
  GtkWidget   *entryZoneFin;
  GtkWidget   *boutonCalD;
  GtkWidget   *boxComboD;
  GtkWidget   *imgCalD;
  GtkWidget   *comboHD;
  GtkWidget   *comboMD;
  GtkWidget   *comboSD;

  // Vitesse
  GtkWidget   *boxPB;
  GtkWidget   *label;
  GtkWidget   *vitesse;

  GtkWidget   *frameCible;
  GtkWidget   *boxFrameCible;
  GtkWidget   *boutonMode;
  GtkWidget   *menuDeroulant;

  //Boutons d'animation
  GtkWidget   *boxBoutons;
  GtkWidget   *boutonArriere;
  GtkWidget   *boutonStop;
  GtkWidget   *boutonPlayPause;
  GtkWidget   *boutonAvance;

  //Icones des boutons d'animation
  GtkWidget   *imgArriere;
  GtkWidget   *imgStop;
  GtkWidget   *imgPlayPause;
  GtkWidget   *imgAvance;

  GtkWidget   *boxAffichage;
  GtkWidget   *labelDate;
  GtkWidget   *labelHeure;
} animUI;

typedef struct s_Calendrier
{
  GtkWidget *widget;
  int       type;

  GtkWidget *boxPrincipale;

  GtkWidget *boxBoutons;
  GtkWidget *boutonAnnuler;
  GtkWidget *boutonConfirmer;
}calUI;


/* ===== Fonctions ===== */
int uiAnimation(GtkWidget* widget, gpointer user_data);
void setCalendrierDebut(GtkWidget* widget, gpointer user_data);
void setCalendrierFin(GtkWidget* widget, gpointer user_data);
void annulerCal(GtkWidget* widget, gpointer user_data);
void confirmerCalDebut(GtkWidget* widget, gpointer user_data);
void confirmerCalFin(GtkWidget* widget, gpointer user_data);
void arriere(GtkWidget* widget, gpointer user_data);
void stop(GtkWidget* widget, gpointer user_data);
void playPause(GtkWidget* widget, gpointer user_data);
void avance(GtkWidget* widget, gpointer user_data);
int avanceAux(gpointer user_data);

void initCombo();
void changeMode(GtkWidget* widget, gpointer user_data);
void getHeure();
void ajoutMenuTracesAnim(const gchar* nom);
void supprimeMenuTracesAnim(gint id);
void renommeMenuTracesAnim(gint id, const gchar* nom);

void bloqueInterfaceAnim();
void debloqueInterfaceAnim();
int compareTps(time_t date);
