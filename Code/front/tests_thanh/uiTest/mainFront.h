#pragma once

#include "includes.h"
#include "uiTraces.h"
#include "activate.h"

void ajoutWidget(GtkWidget* emplacement, GtkWidget* widget)
{
  gtk_container_add(GTK_CONTAINER(emplacement), widget);
}

void ajoutGrille(GtkWidget* grille, GtkWidget* widget, gint colonne, gint ligne, gint dimX, gint dimY)
{
  gtk_grid_attach(GTK_GRID(grille), widget, colonne, ligne, dimX, dimY);
}