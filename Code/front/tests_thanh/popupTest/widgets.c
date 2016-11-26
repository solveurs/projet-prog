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


int compteur = 0;

//Label
GtkWidget* monLabel;

void activate(GtkApplication *app, gpointer user_data)
  {
  GtkWidget* fenetre;

  fenetre = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (fenetre), "Fenetre de test");
  gtk_window_set_default_size (GTK_WINDOW (fenetre), 300, 300);

  //Creation de la grille
  GtkWidget* grille;
  grille = gtk_grid_new();
  ajoutWidget(fenetre, grille);

  //Bouton + ButtonBox
  GtkWidget *monBouton, *buttonBox;
  buttonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  monBouton = gtk_button_new_with_label("Click moi !!");
  g_signal_connect (monBouton, "clicked", G_CALLBACK(ouverture), app);
  ajoutWidget(buttonBox, monBouton);
  ajoutGrille(grille, buttonBox, 1, 0, 1, 1);

  monLabel = gtk_label_new("0");
  ajoutGrille(grille, monLabel, 0, 0, 1, 1);

  //Packaging
  gtk_widget_show_all(fenetre);
  }

 void ouverture(GtkWidget* widget, gpointer user_data)
  {
  	//TODO
  	/*
  	Gestion du focus
  	Lors d'un reclick, on refocus juste
  	Interraction avec d'autres widgets (incremente comme exemple)
  	*/

  //Fenetre popup
  	GtkWidget* popup;

  	popup = gtk_application_window_new(user_data);
  	gtk_window_set_title (GTK_WINDOW (popup), "SURPRISE MOZAF*CKER");
  	gtk_window_set_default_size (GTK_WINDOW (popup), 500, 500);

  //Creation de la grille
  	GtkWidget* grille;
  	grille = gtk_grid_new();
  	ajoutWidget(popup, grille);

  //Bouton + ButtonBox
  	GtkWidget *monBouton, *buttonBox;
  	buttonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  	monBouton = gtk_button_new_with_label("Incremente");
  	//g_signal_connect (monBouton, "clicked", G_CALLBACK(incremente), NULL);
  	ajoutWidget(buttonBox, monBouton);
  	ajoutGrille(grille, buttonBox, 0, 0, 1, 1);

  //Image
  	GtkWidget* image;
  	image = gtk_image_new_from_file("../surprise.jpg");
  	ajoutGrille(grille, image, 0, 1, 1, 1);

  	gtk_widget_show_all(popup);
  }

/*
  void incremente(GtkWidget* widget, gpointer user_data)
  {
  	compteur++;
  	gtk_label_set_text(monLabel, &((gchar)compteur));
  }
*/