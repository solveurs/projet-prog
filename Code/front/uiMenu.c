
#include "../headers/front.h"


void initialisation_menu(uiMain* ui){

  // ===--- Layout : Box des menus
  ui->boxMenu = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
  // --- Widgets : Barre de menu + items
  ui->menuBarre = gtk_menu_bar_new();
  ui->ssMenu1 = gtk_menu_new();
  ui->ssMenu2 = gtk_menu_new();
  ui->ssMenu3 = gtk_menu_new();


  ui->ssMenuItem1    = gtk_menu_item_new_with_label("Affichage");
  ui->ssMenuItem1_1  = gtk_menu_item_new_with_label("Ouvrir l'interface");
  ui->ssMenuItem1_2  = gtk_menu_item_new_with_label("Importer une trace");

  ui->ssMenuItem2    = gtk_menu_item_new_with_label("Animation");
  ui->ssMenuItem2_1  = gtk_menu_item_new_with_label("Ouvrir l'interface");
  ui->ssMenuItem2_2  = gtk_menu_item_new_with_label("Lancer l'animation"); // "Mettre en pause l'animation");
  ui->ssMenuItem2_3  = gtk_menu_item_new_with_label("Arreter l'animation");

  ui->ssMenuItem3    = gtk_menu_item_new_with_label("Anonymisation");
  ui->ssMenuItem3_1  = gtk_menu_item_new_with_label("Ouvrir l'interface");
  ui->ssMenuItem3_2  = gtk_menu_item_new_with_label("Tracer un cercle d'anonymat");

  ui->ssMenuItem4    = gtk_menu_item_new_with_label("Aide");

  // On définit les noms des sous-menus en tant qu'item
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(ui->ssMenuItem1), ui->ssMenu1);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(ui->ssMenuItem2), ui->ssMenu2);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(ui->ssMenuItem3), ui->ssMenu3);

  // On connecte les sous-menus avec les choix
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu1), ui->ssMenuItem1_1);
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu1), ui->ssMenuItem1_2);

  gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu2), ui->ssMenuItem2_1);
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu2), ui->ssMenuItem2_2);
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu2), ui->ssMenuItem2_3);

  gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu3), ui->ssMenuItem3_1);
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu3), ui->ssMenuItem3_2);

  // On ajoute les items a la barre de menu
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->menuBarre), ui->ssMenuItem1);
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->menuBarre), ui->ssMenuItem2);
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->menuBarre), ui->ssMenuItem3);
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->menuBarre), ui->ssMenuItem4);

  // ===================== Signaux =====================
  g_signal_connect(ui->ssMenuItem1_1, "activate", G_CALLBACK(auxTraces), NULL);
  g_signal_connect(ui->ssMenuItem1_2, "activate", G_CALLBACK(auxImporter), NULL);
  g_signal_connect(ui->ssMenuItem2_1, "activate", G_CALLBACK(auxAnim), NULL);
  g_signal_connect(ui->ssMenuItem3_1, "activate", G_CALLBACK(auxAnon), NULL);
  g_signal_connect(ui->ssMenuItem4, "active", G_CALLBACK(auxAide), NULL);
}

void auxTraces(GtkWidget* widget, gpointer user_data)
{
	affUITraces();
}

void auxImporter(GtkWidget* widget, gpointer user_data)
{
	appelImporter();
}

void auxAnim(GtkWidget* widget, gpointer user_data)
{
	affUIAnim();
}

void auxAnon(GtkWidget* widget, gpointer user_data)
{
	affUIAnon();
}

void auxAide(GtkWidget* widget, gpointer user_data)
{
  //char* message = "Une documentation se trouve dans : %s\n"
}