#pragma once

#include "includes.h"
#include "structures.h"
#include "uiTraces.h"

/* ====== CONSTANTES ====== */
#define MODE_ANIMATION         0
#define MODE_NORMAL            1

#define TAILLE_TRACE_CHER      5.0
#define TAILLE_TRACE_BOURGES   5.0
#define TAILLE_TRACE_INSA      5.0

#define TAILLE_X_CHER       1850.0
#define TAILLE_Y_CHER       3506.0
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
void faire_tracer(cairo_t *cr, int carte, tracesItem* item);
void faire_aggregation(cairo_t *cr, point centre, double r);

double echelle(double valeur, int carte, int abscisse);
double conversionGPS(double coord, int carte, int longitude);
double rayonGPS(double rayonAConver, int carte);

void majCartes(int idCarte);
void cacheCartes(int idCarte);
void afficheCartes(int idCarte);
void switchMode(int type);
void setLimite(int max);
void setVitesse(int vit);
void incrLimite(int add, int taille);
void decrLimite(int sub);
void resetOnce();
