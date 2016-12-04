#pragma once

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void ajoutWidget(GtkWidget* emplacement, GtkWidget* widget);
void ajoutGrille(GtkWidget* grille, GtkWidget* widget, gint colonne, gint ligne, gint dimX, gint dimY);
void activate(GtkApplication *app, gpointer user_data);
void UICarte(GtkWidget* widget, gpointer user_data);
void UIAnim(GtkWidget* widget, gpointer user_data);
void UITraces(GtkWidget* widget, gpointer user_data);
void UIAnom(GtkWidget* widget, gpointer user_data);
void UISurprise(GtkWidget* widget, gpointer user_data);
