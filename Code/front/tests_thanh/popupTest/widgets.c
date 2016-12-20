/**
 * \file      widgets.c
 * \brief     Fichier de test pour les PopUp
 * \author    Thanh.L
 * \version   0.2
 *
 * Dans ce fichier, on trouve les 4 fonctions principales
 * qui vont servir a gerer les PopUp lies aux diverses
 * sections des UI ainsi que leur fonction.
 * Les seules UI faites correctement sont UITraces et UIAnim
 * parce que les autres (UICartes et UIAnom) sont redondantes
 * (boutons de choix, scrolls, listing...)
 *
 * ===== TODO =====
 * - Creation d'un signal de "vie" des fenetres flottantes
 *    (pour eviter d'en ouvrir plusieurs fois et rendre possible
 *     la fermeture puis la reouverture)
 * - Faire des fonctions de test pour interagir avec la fenetre main
 * - Modulariser tout ca, la ca commence serieusement a faire mal aux yeux
 * - Enlever ce fichu warning Gtk de parente des PopUp
 * - Trouver un moyen de les minimiser en meme temps que la fenetre main
 * - Trouver un moyen de les minimiser tout court...
*/

#include "widgets.h"

// ===== Struct =====
struct{
  int carte;
  int animation;
  int traces;
  int anonymat;
  int surprise;
} status;

// ===== Global =====
GtkWidget* fenetre;


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

  // Signaux
  g_signal_connect(boutonCarte, "clicked", G_CALLBACK(UICarte), app);
  g_signal_connect(boutonAnimation, "clicked", G_CALLBACK(UIAnim), app);
  //g_signal_connect(boutonTraces, "clicked", G_CALLBACK(UITraces), app);
  g_signal_connect(boutonAnonym, "clicked", G_CALLBACK(UIAnom), app);
  //g_signal_connect(bSurp, "clicked", G_CALLBACK(UISurprise), app);

  // Packaging des widgets
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

  // Affichage
  gtk_widget_show_all(fenetre);
}


// ===== Fonctions =====

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
  else
    status.carte = 0;
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

    // Box layout de la fenetre
    GtkWidget* boxAnim;
    GtkWidget *frameAnimAction, *frameAnimOption;

    boxAnim = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    frameAnimAction = gtk_frame_new("Animation des traces");
    frameAnimOption = gtk_frame_new("Options avancées");

    // Contenues des box
      // Animation
    GtkWidget* boxFrameAnim;
    boxFrameAnim = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);

    GtkWidget *bReculeRapide, *bReculeStep, *bStop;
    GtkWidget *bAvanceRapide, *bAvanceStep, *bLecture;
    GtkWidget *bBRR, *bBRS, *bBS, *bBAR, *bBAS, *bBL;

    bBRR = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    bBRS = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    bBS = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    bBAR = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    bBAS = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    bBL = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    bReculeRapide = gtk_button_new_with_label("<<");
    bReculeStep = gtk_button_new_with_label("<");
    bStop = gtk_button_new_with_label("■");
    bLecture = gtk_button_new_with_label("►");
    bAvanceStep = gtk_button_new_with_label(">");
    bAvanceRapide = gtk_button_new_with_label(">>");

    ajoutWidget(bBRR, bReculeRapide);
    ajoutWidget(bBRS, bReculeStep);
    ajoutWidget(bBS, bStop);
    ajoutWidget(bBAR, bAvanceRapide);
    ajoutWidget(bBAS, bAvanceStep);
    ajoutWidget(bBL, bLecture);

    gtk_box_pack_end(boxFrameAnim, bBAR, FALSE, FALSE, 3);
    gtk_box_pack_end(boxFrameAnim, bBAS, FALSE, FALSE, 3);
    gtk_box_pack_end(boxFrameAnim, bBL, FALSE, FALSE, 3);
    gtk_box_pack_end(boxFrameAnim, bBS, FALSE, FALSE, 3);
    gtk_box_pack_end(boxFrameAnim, bBRS, FALSE, FALSE, 3);
    gtk_box_pack_end(boxFrameAnim, bBRR, FALSE, FALSE, 3);

    ajoutWidget(frameAnimAction, boxFrameAnim);

    // Packaging
    gtk_box_pack_end(boxAnim, frameAnimOption, TRUE, TRUE, 10);
    gtk_box_pack_end(boxAnim, frameAnimAction, TRUE, TRUE, 10);  
    ajoutWidget(popupAnim, boxAnim);  

    // Affichage
    gtk_widget_show_all(popupAnim);
  }
  else
    status.animation = 0;
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
  else
    status.anonymat = 0;
}

void ajoutWidget(GtkWidget* emplacement, GtkWidget* widget)
{
  gtk_container_add (GTK_CONTAINER(emplacement), widget);
}

void ajoutGrille(GtkWidget* grille, GtkWidget* widget, gint colonne, gint ligne, gint dimX, gint dimY)
{
  gtk_grid_attach(GTK_GRID(grille), widget, colonne, ligne, dimX, dimY);
}
