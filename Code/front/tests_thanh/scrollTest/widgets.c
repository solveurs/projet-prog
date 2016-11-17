#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "widgets.h"

void ajoutWidget(GtkWidget* emplacement, GtkWidget* widget)
{
  gtk_container_add (GTK_CONTAINER(emplacement), widget);
}

void ajoutGrille(GtkWidget* grille, GtkWidget* widget, gint colonne, gint ligne, gint dimX, gint dimY)
{
  gtk_grid_attach(GTK_GRID(grille), widget, colonne, ligne, dimX, dimY);
}


void activate(GtkApplication *app, gpointer user_data)
  {
  GtkWidget* fenetre;

  fenetre = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (fenetre), "Fenetre de test");
  gtk_window_set_default_size (GTK_WINDOW (fenetre), 300, 300);

  //Creation de la grille
  //GtkWidget* grille;
  //grille = gtk_grid_new();
  //ajoutWidget(fenetre, grille);

  //Fenetre Scroll
  GtkWidget* monScroll;
  monScroll = gtk_scrolled_window_new(NULL, NULL);
  //ajoutGrille(monScroll, 0,0,0,0);
  ajoutWidget(fenetre, monScroll);

  GtkWidget* image;
  image = gtk_image_new_from_file("surprise.jpg");
  ajoutWidget(monScroll, image);


  //Packaging
  gtk_widget_show_all(fenetre);
  }

