#pragma once

#include "includes.h"
#include "structures.h"
#include "uiTraces.h"

/* ====== CONSTANTES ====== */
#define TAILLE_TRACE           5.0

#define TAILLE_X_CHER       1013.0
#define TAILLE_Y_CHER       1920.0
#define LAT_HG_CHER      47.988083
#define LON_HG_CHER       1.726227
#define LAT_BD_CHER      46.194092
#define LON_BD_CHER	      3.115997

#define TAILLE_X_BOURGES    1850.0
#define TAILLE_Y_BOURGES    1079.0
#define LAT_HG_BOURGES   47.113540
#define LON_HG_BOURGES    2.313738
#define LAT_BD_BOURGES   47.050476
#define LON_BD_BOURGES	  2.472610

#define TAILLE_X_INSA       1850.0
#define TAILLE_Y_INSA       1080.0
#define LAT_HG_INSA      47.088723
#define LON_HG_INSA       2.392981
#define LAT_BD_INSA      47.072957
#define LON_BD_INSA	      2.432764

/* ===== Fonctions ===== */
void faire_tracesCher(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void faire_tracesBourges(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void faire_tracesInsa(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void faire_tracer(cairo_t *cr, int carte, trajet *cible, GdkRGBA* couleur);

void faire_aggregation(cairo_t *cr, cercle *cercle);

double echelle(double valeur, int carte, int abscisse);

void majCartes(int idCarte);
void cacheCartes(int idCarte);
void afficheCartes(int idCarte);
