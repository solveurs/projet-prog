#pragma once

#include <gtk/gtk.h>

void ajoutWidget(GtkWidget* emplacement, GtkWidget* widget);
void ajoutGrille(GtkWidget* grille, GtkWidget* widget, gint colonne, gint ligne, gint dimX, gint dimY);
void activate(GtkApplication *app, gpointer user_data);
