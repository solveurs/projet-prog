#pragma once

#include "includes.h"
#include "structures.h"
#include "uiTraces.h"

/* ====== CONSTANTES ====== */
#define TAILLE_TRACE           5.0
#define TAILLE_X_CHER       1013.0
#define TAILLE_Y_CHER       1920.0
#define TAILLE_X_BOURGES    1850.0
#define TAILLE_Y_BOURGES    1079.0
#define TAILLE_X_INSA       1850.0
#define TAILLE_Y_INSA       1080.0

/* ===== Fonctions ===== */
void faire_tracesCher(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void faire_tracesBourges(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void faire_tracesInsa(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void faire_tracer(cairo_t *cr, int carte, trajet *cible);

void faire_aggregation(cairo_t *cr, cercle *cercle);

double echelle(double valeur, int carte, int abscisse);

void majCartes(int idCarte);
void cacheCartes(int idCarte);
void afficheCartes(int idCarte);
