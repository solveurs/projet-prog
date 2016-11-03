#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

//Pour la compilation et l'execution
//gcc `pkg-config --cflags gtk+-3.0` -o tmpMemo tmpMemo.c `pkg-config --libs gtk+-3.0` && ./tmpMemo

//Oui je suis un flemmard, et je le revendique !
void ajoutWidget(GtkWidget* emplacement, GtkWidget* widget)
{
  gtk_container_add (GTK_CONTAINER(emplacement), widget);
}

void ajoutGrille(GtkWidget* grille, GtkWidget* widget, gint colonne, gint ligne, gint dimX, gint dimY)
{
  gtk_grid_attach(GTK_GRID(grille), widget, colonne, ligne, dimX, dimY);
}


void activate (GtkApplication* app, gpointer user_data)
{
  //Creation de la fenetre
  GtkWidget* fenetre;

  fenetre = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (fenetre), "Mes tests loufoques");
  gtk_window_set_default_size (GTK_WINDOW (fenetre), 600, 600);

  //Creation de la grille
  GtkWidget* grille;
  grille = gtk_grid_new();
  ajoutWidget(fenetre, grille);

  //Label
  GtkWidget* monLabel;
  monLabel = gtk_label_new("Mon label");
  ajoutGrille(grille, monLabel, 0, 0, 1, 1);

  
  //Bouton + ButtonBox
  GtkWidget *monBouton, *buttonBox;
  buttonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  monBouton = gtk_button_new_with_label("Mon bouton");
  ajoutWidget(buttonBox, monBouton);
  ajoutGrille(grille, buttonBox, 1, 0, 1, 1);

  //Bouton menu
  GtkWidget* menuBouton;
  menuBouton = gtk_menu_button_new();
  // A faire: le menu 
  ajoutGrille(grille, menuBouton, 2, 0, 1, 1);

  //Le spin button
  GtkWidget* monSpin;
  // A faire: definir un adjustment (au lieu de NULL)
  monSpin = gtk_spin_button_new(NULL, 1, 0);
  ajoutGrille(grille, monSpin, 3, 0, 1, 1);


  //Boutton couleur
  GtkWidget *colorButton;
  colorButton = gtk_color_button_new();
  ajoutGrille(grille, colorButton, 4, 0, 1, 1);
  // A faire: voir cette histoire de dconf

  //Zone d'input ?
  GtkEntryBuffer* monBuffer;
  monBuffer = gtk_entry_buffer_new("NANIIII ?!", -1);
  GtkWidget* entryZone;
  entryZone = gtk_entry_new_with_buffer(monBuffer);
  ajoutGrille(grille, entryZone, 5, 0, 1, 1);

  //Label cadre
  GtkWidget* monCadre;
  monCadre = gtk_frame_new("Youhou un cadre");
  ajoutGrille(grille, monCadre, 6, 0, 1, 1);

  //Zone de scroll
  GtkWidget *monScroll, *labelScroll;
  // A faire: definir un adjustment
  labelScroll = gtk_label_new("The Elder Scrolls");
  monScroll = gtk_scrolled_window_new(NULL, NULL);

  ajoutWidget(monScroll, labelScroll);
  ajoutGrille(grille, monScroll, 0, 1, 1, 1);

  //Menu bar + Menu + Menu Item
  GtkWidget *maBox, *menuBar, *ssMenu1, *ssMenu2;
  GtkWidget *ssMenuItem1, *ssMenuItem2, *ssMenuItem3, *ssMenuItem4, *ssMenuItem5;

  maBox = gtk_box_new(FALSE, 5);
  menuBar = gtk_menu_bar_new();
  ssMenu1 = gtk_menu_new();
  ssMenu2 = gtk_menu_new();

  ssMenuItem1 = gtk_menu_item_new_with_label("Fichier");
  ssMenuItem2 = gtk_menu_item_new_with_label("Aide");
  ssMenuItem3 = gtk_menu_item_new_with_label("Test1");
  ssMenuItem4 = gtk_menu_item_new_with_label("Test2");
  ssMenuItem5 = gtk_menu_item_new_with_label("Test3");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(ssMenuItem1), ssMenu1);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(ssMenuItem2), ssMenu2);

  gtk_menu_shell_append(GTK_MENU_SHELL(ssMenu1), ssMenuItem3);
  gtk_menu_shell_append(GTK_MENU_SHELL(ssMenu2), ssMenuItem4);
  gtk_menu_shell_append(GTK_MENU_SHELL(ssMenu2), ssMenuItem5);

  gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), ssMenuItem1);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), ssMenuItem2);

  gtk_box_pack_start(GTK_BOX(maBox), menuBar, FALSE, FALSE, 0);
  ajoutGrille(grille, maBox, 0, 2, 1, 1);

/*
  //Selection de fichier
  //Non fonctionnelle ?

  GtkWidget *boutonChoix;

  boutonChoix = gtk_file_chooser_button_new(("Choisir un fichier"),GTK_FILE_CHOOSER_ACTION_OPEN);
  gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER (boutonChoix),".");
  ajoutGrille(grille, boutonChoix, 1, 1, 1, 1);

  //Image

  GtkWidget* image;
  image = gtk_image_new_from_file("votre_image");
  ajoutGrille(grille, image, 0, 3, 1, 1);
*/
  
  //Affichage recursif des widgets
  gtk_widget_show_all (fenetre);

}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;
  app = gtk_application_new ("geoloc.gtk.exemple", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
