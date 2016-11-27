/**
 * \file      widgets.c
 * \brief     Fichier de test pour les PopUp
 * \author    Thanh.L
 * \version   0.1
 *
 * Dans ce fichier, on trouve les 4 fonctions principales
 * qui vont servir a gerer les PopUp lies aux diverses
 * sections des UI ainsi que leur fonction.
 *
*/

#include "widgets.h"


GtkWidget* fenetre;

struct{
  int carte;
  int animation;
  int traces;
  int anonymat;
  int surprise;
} status;

void activate(GtkApplication *app, gpointer user_data)
{
  fenetre = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (fenetre), "Test des fenetres flottantes");
  gtk_window_set_default_size (GTK_WINDOW (fenetre), 300, 300);

  //Creation de la grille
  GtkWidget* grille;
  grille = gtk_grid_new();
  gtk_grid_set_column_homogeneous(GTK_GRID(grille), TRUE);
  gtk_grid_set_row_homogeneous (GTK_GRID(grille), TRUE);
  ajoutWidget(fenetre, grille);

  //Bouton + ButtonBox
  GtkWidget *buttonBoxC, *buttonBoxAnim, *buttonBoxT, *buttonBoxAnom, *bBSurp;
  GtkWidget *boutonCarte, *boutonAnimation, *boutonTraces, *boutonAnonym, *bSurp;

  buttonBoxC = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  buttonBoxAnim = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  buttonBoxT = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  buttonBoxAnom = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  bBSurp = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

  boutonCarte = gtk_button_new_with_label("Gestion des cartes");
  boutonAnimation = gtk_button_new_with_label("Animation des traces");
  boutonTraces = gtk_button_new_with_label("Gestion des traces");
  boutonAnonym = gtk_button_new_with_label("Anonymisation");
  bSurp = gtk_button_new_with_label("Une surprise !");

  g_signal_connect(boutonCarte, "clicked", G_CALLBACK(UICarte), app);
  g_signal_connect(boutonAnimation, "clicked", G_CALLBACK(UIAnim), app);
  g_signal_connect(boutonTraces, "clicked", G_CALLBACK(UITraces), app);
  g_signal_connect(boutonAnonym, "clicked", G_CALLBACK(UIAnom), app);
  g_signal_connect(bSurp, "clicked", G_CALLBACK(UISurprise), app);

  ajoutWidget(buttonBoxC, boutonCarte);
  ajoutGrille(grille, buttonBoxC, 1, 0, 1, 1);

  ajoutWidget(buttonBoxAnim, boutonAnimation);
  ajoutGrille(grille, buttonBoxAnim, 1, 1, 1, 1);

  ajoutWidget(buttonBoxT, boutonTraces);
  ajoutGrille(grille, buttonBoxT, 1, 2, 1, 1);

  ajoutWidget(buttonBoxAnom, boutonAnonym);
  ajoutGrille(grille, buttonBoxAnom, 1, 3, 1, 1);

  ajoutWidget(bBSurp, bSurp);
  ajoutGrille(grille, bBSurp, 1, 4, 1, 1);

  //Packaging
  gtk_widget_show_all(fenetre);
}


//TODO
/*
Lors d'un reclick, on refocus juste
Interraction avec d'autres widgets hors de sa fenetre
*/
void UICarte(GtkWidget* widget, gpointer user_data)
{
  if(!status.carte)
  {
    //Fenetre popup
    status.carte = 1;
    GtkWidget* popupCarte;

    popupCarte = gtk_application_window_new(user_data);
    gtk_window_set_title (GTK_WINDOW (popupCarte), "Gestion des cartes");
    // On definit un parent
    gtk_widget_set_parent(popupCarte, fenetre);
    // On n'affiche pas le popup dans la barre des taches
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popupCarte), TRUE);
    // Le popup sera toujours au-dessus de la fenetre principale
    gtk_window_set_transient_for(GTK_WINDOW(popupCarte),GTK_WINDOW(fenetre));
    // Explicite
    gtk_window_set_destroy_with_parent(GTK_WINDOW(popupCarte), TRUE);

    gtk_widget_show_all(popupCarte);
  }
}

void UIAnim(GtkWidget* widget, gpointer user_data)
{
  if(!status.animation)
  {
    //Fenetre popup
    status.animation = 1;
    GtkWidget* popupAnim;

    popupAnim = gtk_application_window_new(user_data);
    gtk_window_set_title (GTK_WINDOW (popupAnim), "Gestion des animations");
    gtk_widget_set_parent(popupAnim, fenetre);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popupAnim), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(popupAnim),GTK_WINDOW(fenetre));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(popupAnim), TRUE);

    gtk_widget_show_all(popupAnim);
  }
}

void UITraces(GtkWidget* widget, gpointer user_data)
{
  if(!status.traces)
  {
    status.traces = 1;
    //Fenetre popup
    GtkWidget* popupTraces;

    popupTraces = gtk_application_window_new(user_data);
    gtk_window_set_title (GTK_WINDOW (popupTraces), "Gestion des traces");
    gtk_widget_set_parent(popupTraces, fenetre);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popupTraces), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(popupTraces), GTK_WINDOW(fenetre));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(popupTraces), TRUE);

    // Box layout de la fenetre
    GtkWidget* boxTraces;
    boxTraces = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Bouton "Importer"
    GtkWidget *boutonImporter, *bBoxImporter;
    bBoxImporter = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    boutonImporter = gtk_button_new_with_label("Mon bouton");
    ajoutWidget(bBoxImporter, boutonImporter);
    gtk_box_pack_start(boxTraces, bBoxImporter, FALSE, FALSE, 0);

    // Zone scrollable
    GtkWidget *zoneScroll, *labelScroll;
    labelScroll = gtk_label_new("A faire: definir un adjustment\nEt fonctions de gestion");
    zoneScroll = gtk_scrolled_window_new (NULL, NULL);
    ajoutWidget(zoneScroll, labelScroll);
    gtk_box_pack_end(boxTraces, zoneScroll, FALSE, FALSE, 0);

    ajoutWidget(popupTraces, boxTraces);
    gtk_widget_show_all(popupTraces);
  }
}

void UIAnom(GtkWidget* widget, gpointer user_data)
{
  if(!status.anonymat)
  {
    status.anonymat = 1;
    //Fenetre popup
    GtkWidget* popupAnom;

    popupAnom = gtk_application_window_new(user_data);
    gtk_window_set_title (GTK_WINDOW (popupAnom), "Gestion de l'anonymat");
    gtk_widget_set_parent(popupAnom, fenetre);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popupAnom), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(popupAnom), GTK_WINDOW(fenetre));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(popupAnom), TRUE);

    gtk_widget_show_all(popupAnom);
  }
}

void UISurprise(GtkWidget* widget, gpointer user_data)
{
  if(!status.surprise)
  {
    status.surprise = 1;
    //Fenetre popup
    GtkWidget* popupSurprise;
    gtk_widget_set_parent(popupSurprise, fenetre);

    popupSurprise = gtk_application_window_new(user_data);
    gtk_window_set_title (GTK_WINDOW (popupSurprise), "SURPRISE MOZAF*CKER");
    gtk_widget_set_parent(popupSurprise, fenetre);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popupSurprise), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(popupSurprise), GTK_WINDOW(fenetre));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(popupSurprise), TRUE);

    //Image
    GtkWidget* image;
    image = gtk_image_new_from_file("../surprise.jpg");
    ajoutWidget(popupSurprise, image);

    gtk_widget_show_all(popupSurprise);
  }
}

void ajoutWidget(GtkWidget* emplacement, GtkWidget* widget)
{
  gtk_container_add (GTK_CONTAINER(emplacement), widget);
}

void ajoutGrille(GtkWidget* grille, GtkWidget* widget, gint colonne, gint ligne, gint dimX, gint dimY)
{
  gtk_grid_attach(GTK_GRID(grille), widget, colonne, ligne, dimX, dimY);
}
