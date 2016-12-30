/**
 * \file      uiAnonymite.c
 * \brief     Fichier main de la GUI de l'anonymat.
 * \author    Thanh.L
 * \version   0.1a
 *
 * Le fichier contient toutes les fonctions liees au PopUp de gestion de l'anonymat.
 * ====================
 *       TODO
 * ====================
 * Faire les fonctions relatives aux boutons.
 *
 * ====================
 *        MaJ
 * ====================
 * Creation du fichier.
 * Ceci n'est que le squelette graphique, les fonctions ne sont pas encore ecrites.
 *
*/

#include "../headers/uiAnonymite.h"

int uiAnonymite(GtkWidget* widget, gpointer user_data)
{
  static int etat = UI_ANON_FERME;
  static uiAnon* fenetreAnon;

  if(!etat)
  {
    // ============== Initialisation widgets =============
    // ====== Validation d'ouverture
    etat = UI_ANON_OUVERT;
  
    // ====== Fenetre
    fenetreAnon = (uiAnon *)malloc(sizeof(uiAnon));
  
    if(fenetreAnon == NULL)
    {
      printf("Erreur malloc anonUI");
      exit(EXIT_FAILURE);
    }
  
    fenetreAnon->widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(fenetreAnon->widget), "Gestion de l'anonymat");
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(fenetreAnon->widget), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(fenetreAnon->widget), GTK_WINDOW(user_data));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(fenetreAnon->widget), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(fenetreAnon->widget), UI_ANON_TAILLE_X, UI_ANON_TAILLE_Y);
  
    fenetreAnon->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_ANON_ESPACEMENT);
  
	  fenetreAnon->boutonBoxCercle = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	  fenetreAnon->boutonCercle = gtk_button_new_with_label("Tracer un cercle d'anonymat");

	  fenetreAnon->frameCible = gtk_frame_new("Trace ciblée");
    fenetreAnon->menuDeroulant = gtk_combo_box_text_new();

	  fenetreAnon->frameScroll = gtk_frame_new("Liste des zones anonymisées");
	  fenetreAnon->zoneScroll = gtk_scrolled_window_new(NULL, NULL);
	  fenetreAnon->boxItem = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_ANON_ESPACEMENT);
  
    // ===================== Signaux =====================
    g_signal_connect(fenetreAnon->widget, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
    //g_signal_connect(fenetreAnon->boutonCercle, "clicked", G_CALLBACK(traceCercle), ???);
    g_signal_connect(fenetreAnon->boutonCercle, "clicked", G_CALLBACK(ajoutItemAnon), fenetreAnon);
  
    // ==================== Packaging ====================
    // Fenetre principale <- Box principale
    gtk_container_add(GTK_CONTAINER(fenetreAnon->widget), fenetreAnon->boxPrincipale);
    // Box principale <- Bouton cercle + Frame cible + Frame scroll
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxPrincipale), fenetreAnon->boutonBoxCercle, FALSE, FALSE, UI_ANON_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxPrincipale), fenetreAnon->frameCible, FALSE, FALSE, UI_ANON_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxPrincipale), fenetreAnon->frameScroll, TRUE, TRUE, UI_ANON_ESPACEMENT);

      // Bouton box <- Bouton cercle
    gtk_container_add(GTK_CONTAINER(fenetreAnon->boutonBoxCercle), fenetreAnon->boutonCercle);

      // Frame cible <- Menu deroulant
    gtk_container_add(GTK_CONTAINER(fenetreAnon->frameCible), fenetreAnon->menuDeroulant);

      // Frame scroll <- zone scroll
    gtk_container_add(GTK_CONTAINER(fenetreAnon->frameScroll), fenetreAnon->zoneScroll);
      // Zone scroll <- Box des items
    gtk_container_add(GTK_CONTAINER(fenetreAnon->zoneScroll), fenetreAnon->boxItem);

    // ==================== Affichage ====================
    gtk_widget_show_all(fenetreAnon->widget);

    return EXIT_SUCCESS;
  }
  else
  {
  	gtk_window_present(GTK_WINDOW(fenetreAnon->widget));
  }
}

void ajoutItemAnon(GtkWidget* widget, gpointer user_data)
{
  static int incr = 0;
  uiAnon* fenetre = (uiAnon *)user_data;
  GtkWidget* boxItem = (GtkWidget *)(fenetre->boxItem);

  // ============== Initialisation widgets =============
  // ====== Validatation malloc
  anonItem* item = (anonItem *) malloc(sizeof(anonItem));
  if(item == NULL)
  {
  	printf("Erreur malloc anonItem");
  	exit(EXIT_FAILURE);
  }

  item->details = (adUI *) malloc(sizeof(adUI));
  if(item->details == NULL)
  {
  	printf("Erreur malloc adUI");
  	exit(EXIT_FAILURE);
  }

  item->widget = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANON_ESPACEMENT);

  //int       couleur;
  item->etat = UI_ANON_FERME; 
  item->id = incr;
  /* Warning a corriger */
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(fenetre->menuDeroulant), NULL, "Mon cercle");

  item->boxG = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANON_ESPACEMENT);
  item->labelNom = gtk_label_new("Mon cercle");

  item->boxD = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANON_ESPACEMENT);
  item->boutonVisible = gtk_button_new_with_label("Visible");
  item->boutonOption = gtk_button_new_with_label("Option");
  item->boutonSupprimer = gtk_button_new_with_label("Supprimer");

  // ===================== Signaux =====================
  g_signal_connect(item->boutonOption, "clicked", G_CALLBACK(optionItemAnon), item);

  // ==================== Packaging ====================
  // Box item <- Boxes gauche et droite
  gtk_box_pack_start(GTK_BOX(item->widget), item->boxG, TRUE, FALSE, UI_ANON_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(item->widget), item->boxD, TRUE, FALSE, UI_ANON_ESPACEMENT);

    // Box gauche <- label nom
  gtk_box_pack_start(GTK_BOX(item->boxG), item->labelNom, TRUE, FALSE, UI_ANON_ESPACEMENT);

    // Box droite <- Boutons
  gtk_box_pack_start(GTK_BOX(item->boxD), item->boutonVisible, TRUE, FALSE, UI_ANON_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(item->boxD), item->boutonOption, TRUE, FALSE, UI_ANON_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(item->boxD), item->boutonSupprimer, TRUE, FALSE, UI_ANON_ESPACEMENT);

  // ==================== Affichage ====================
  gtk_widget_show_all(item->widget);
  gtk_box_pack_start(GTK_BOX(boxItem), item->widget, FALSE, TRUE, UI_ANON_ESPACEMENT);

  incr++;
}

void optionItemAnon(GtkWidget* widget, gpointer user_data)
{
  anonItem* item = (anonItem *)user_data;
  adUI* popupAD = item->details;

  if(!item->etat)
  {
    // ============== Initialisation widgets =============
    item->etat = UI_ANON_OUVERT;
	popupAD->widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(popupAD->widget), "Mon cercle");
    gtk_window_set_keep_above(GTK_WINDOW(popupAD->widget), TRUE);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popupAD->widget), TRUE);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(popupAD->widget), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(popupAD->widget), UI_ANON_TAILLE_X, UI_ANON_TAILLE_Y);

    popupAD->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_ANON_ESPACEMENT);

    popupAD->frameNom = gtk_frame_new("Nom");
    popupAD->boxFrame = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANON_ESPACEMENT);
    popupAD->entryZone = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(popupAD->entryZone), gtk_label_get_text(GTK_LABEL(item->labelNom)));
    popupAD->boutonAppliquer = gtk_button_new_with_label("Appliquer");
    
    popupAD->boutonModifier = gtk_button_new_with_label("Modifier le cercle d'anonymat");
	// ===================== Signaux =====================
	g_signal_connect(popupAD->widget, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);

	// ==================== Packaging ====================
	// Fenetre principale <- Box principale
	gtk_container_add(GTK_CONTAINER(popupAD->widget), popupAD->boxPrincipale);

	// Box principale <- Frame nom + bouton modifier
	gtk_box_pack_start(GTK_BOX(popupAD->boxPrincipale), popupAD->frameNom, TRUE, FALSE, UI_ANON_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(popupAD->boxPrincipale), popupAD->boutonModifier, TRUE, FALSE, UI_ANON_ESPACEMENT);

	  // Frame nom <- Box frame
	gtk_container_add(GTK_CONTAINER(popupAD->frameNom), popupAD->boxFrame);
	  // Box frame <- Entry + Bouton appliquer
	gtk_box_pack_start(GTK_BOX(popupAD->boxFrame), popupAD->entryZone, TRUE, FALSE, UI_ANON_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(popupAD->boxFrame), popupAD->boutonAppliquer, TRUE, FALSE, UI_ANON_ESPACEMENT);
	
	// ==================== Affichage ====================
	gtk_widget_show_all(popupAD->widget);
  }
  else
  {
  	gtk_window_present(GTK_WINDOW(popupAD->widget));
  }
}