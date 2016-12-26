#include "../headers/activate.h"

extern int uiTraces(GtkWidget* widget, gpointer user_data);
extern int uiAnimation(GtkWidget* widget, gpointer user_data);
extern int uiAnonymite(GtkWidget* widget, gpointer user_data);

void activate(GtkApplication *app, gpointer user_data)
{
  // ============== Initialisation widgets =============
  // ====== Validation malloc
  uiMain* ui = (uiMain *)malloc(sizeof(uiMain));
  if(ui == NULL)
  {
  	printf("Erreur malloc uiMain");
  	exit(EXIT_FAILURE);
  }

  // ====== Fenetre
  ui->widget = gtk_application_window_new(app);
  gtk_window_set_title (GTK_WINDOW(ui->widget), "Geoloc v0.1a");
  gtk_window_set_default_size (GTK_WINDOW(ui->widget), UI_MAIN_TAILLE_X, UI_MAIN_TAILLE_Y);
  
  // ===--- Layout : Box principale
  ui->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_MAIN_ESPACEMENT);

     // ===--- Layout : Box des menus
  ui->boxMenu = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
  	    // --- Widgets : Barre de menu + items
  ui->menuBarre = gtk_menu_bar_new();
  ui->ssMenu1 = gtk_menu_new();
  ui->ssMenu2 = gtk_menu_new();

  ui->ssMenuItem1 = gtk_menu_item_new_with_label("Fichier");
  ui->ssMenuItem2 = gtk_menu_item_new_with_label("Reste a faire");
  ui->ssMenuItem3 = gtk_menu_item_new_with_label("A faire");
  ui->ssMenuItem4 = gtk_menu_item_new_with_label("A faire");

  		// On définit les noms des sous-menus en tant qu'item
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(ui->ssMenuItem1), ui->ssMenu1);
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(ui->ssMenuItem2), ui->ssMenu2);

  		// On connecte les sous-menus avec les choix
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu1), ui->ssMenuItem3);
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu2), ui->ssMenuItem4);
  
  		// On ajoute les items a la barre de menu
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->menuBarre), ui->ssMenuItem1);
  gtk_menu_shell_append(GTK_MENU_SHELL(ui->menuBarre), ui->ssMenuItem2);
   
     // ===--- Layout : Frame de l'en-tete + Box de l'en-tete (boutons + choix carte)
  ui->frameEntete = gtk_frame_new("");
  ui->boxEntete = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
     // ===--- Layout : Box des boutons d'UI  
  ui->boxUI = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
  	    // --- Widgets : Boutons des UI  
  ui->boutonBoxTraces = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  ui->boutonBoxAnim = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  ui->boutonBoxAnon = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  ui->boutonTraces = gtk_button_new_with_label("uiTraces");
  ui->boutonAnimation = gtk_button_new_with_label("uiAnimation");
  ui->boutonAnonymat = gtk_button_new_with_label("uiAnonymite");

     // ===--- Layout : Frame du choix de la carte
  ui->frameCarte = gtk_frame_new("Carte");
  		 //--- Widgets : Elements du choix de la carte
  ui->boxCarte = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
  ui->frameEchelle = gtk_frame_new(" ");
  ui->labelEchelle = gtk_label_new("xEchelle");

  ui->selectCarte = gtk_combo_box_text_new();
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(ui->selectCarte), "0", "Cher");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(ui->selectCarte), "1", "Bourges");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(ui->selectCarte), "2", "Insa Bourges");

    // ===--- Layout : zone de la carte
  ui->scrollCarte = gtk_scrolled_window_new(NULL, NULL);
  ui->imgCarte = gtk_image_new_from_file("../france.png");
  
  // ===================== Signaux =====================
  g_signal_connect(ui->boutonTraces, "clicked", G_CALLBACK(uiTraces), ui->widget);
  g_signal_connect(ui->boutonAnimation, "clicked", G_CALLBACK(uiAnimation), ui->widget);
  g_signal_connect(ui->boutonAnonymat, "clicked", G_CALLBACK(uiAnonymite), ui->widget);

  /* Signaux pour les cartes
  g_signal_connect(ui->boutonAnonymat, "clicked", G_CALLBACK(), ui->widget);
  g_signal_connect(ui->boutonAnonymat, "clicked", G_CALLBACK(), ui->widget);
  g_signal_connect(ui->boutonAnonymat, "clicked", G_CALLBACK(), ui->widget);
  */
  
  // ==================== Packaging ====================:
  // Fenetre principale <- Box principale
  gtk_container_add(GTK_CONTAINER(ui->widget), ui->boxPrincipale);
  // Box principale <- Box menu + Frame en-tete (UI + choix carte) + scroll image carte
  gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->boxMenu, FALSE, FALSE, UI_MAIN_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->frameEntete, FALSE, FALSE, UI_MAIN_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->scrollCarte, TRUE, TRUE, UI_MAIN_ESPACEMENT);

  	 // Box menu <- Barre de menu  
  gtk_box_pack_start(GTK_BOX(ui->boxMenu), ui->menuBarre, FALSE, FALSE, UI_MAIN_ESPACEMENT);

  	 // Frame entete <- Box entete
  gtk_container_add(GTK_CONTAINER(ui->frameEntete), ui->boxEntete);
  	 // Box entete <- Box UI + Frame carte
  gtk_box_pack_start(GTK_BOX(ui->boxEntete), ui->boxUI, TRUE, FALSE, UI_MAIN_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(ui->boxEntete), ui->frameCarte, TRUE, TRUE, UI_MAIN_ESPACEMENT);
  		 // Box UI <- Boutons
  gtk_container_add(GTK_CONTAINER(ui->boutonBoxTraces), ui->boutonTraces);
  gtk_container_add(GTK_CONTAINER(ui->boutonBoxAnim), ui->boutonAnimation);
  gtk_container_add(GTK_CONTAINER(ui->boutonBoxAnon), ui->boutonAnonymat);
  gtk_box_pack_start(GTK_BOX(ui->boxUI), ui->boutonBoxTraces, TRUE, FALSE, UI_MAIN_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(ui->boxUI), ui->boutonBoxAnim, TRUE, FALSE, UI_MAIN_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(ui->boxUI), ui->boutonBoxAnon, TRUE, FALSE, UI_MAIN_ESPACEMENT);

  	 // Frame carte <- Box carte
  gtk_container_add(GTK_CONTAINER(ui->frameCarte), ui->boxCarte);
  	 	 // Box carte <- Frame echelle + Label echelle + menu deroulant
  gtk_box_pack_start(GTK_BOX(ui->boxCarte), ui->frameEchelle, FALSE, FALSE, UI_MAIN_ESPACEMENT);
  gtk_container_add(GTK_CONTAINER(ui->frameEchelle), ui->labelEchelle);
  gtk_box_pack_start(GTK_BOX(ui->boxCarte), ui->selectCarte, TRUE, TRUE, UI_MAIN_ESPACEMENT);

  	 // Scroll carte <- image de la carte
  gtk_container_add(GTK_CONTAINER(ui->scrollCarte), ui->imgCarte);

  // ==================== Affichage ====================
  gtk_widget_show_all(ui->widget);
}

