/**
 * \file      activate.c
 * \brief
 * \author    Thanh.L, Guillaume.F
 *
 * Fichier regroupant les fonctions relatives a la GUI de la fenetre principale.
 * On y retrouve la fonction de creation de la fenetre principale et les fonctions de gestion de la carte.
 * Les fonctions appelees depuis les UI flottantes ayant un impact sur la fenetre principale sont definies ici.
 *
 */

#include "../headers/front.h"
/*#include "../headers/activate.h"
 #include "../headers/structures.h"*/

/*
extern int uiTraces(GtkWidget* widget, gpointer user_data);
extern int uiAnimation(GtkWidget* widget, gpointer user_data);
extern int uiAnonymite(GtkWidget* widget, gpointer user_data);
extern void faire_tracesCher(GtkWidget *widget, cairo_t *cr, gpointer user_data);
extern void faire_tracesBourges(GtkWidget *widget, cairo_t *cr, gpointer user_data);
extern void faire_tracesInsa(GtkWidget *widget, cairo_t *cr, gpointer user_data);
*/

static uiMain* ui;

void activate(GtkApplication *app, gpointer user_data)
{
	// ============== Initialisation widgets =============
	// ====== Validation malloc
	ui = (uiMain *)malloc(sizeof(uiMain));
	if(ui == NULL)
	{
		printf("Erreur malloc uiMain");
		exit(EXIT_FAILURE);
	}
	
	// ====== Fenetre
	ui->widget = gtk_application_window_new(app);
	gtk_window_set_title (GTK_WINDOW(ui->widget), "Geoloc v0.2");
	gtk_window_set_icon_from_file(GTK_WINDOW(ui->widget),"../Data/icones/logo_solveur-200.png",NULL);
	gtk_window_set_default_size (GTK_WINDOW(ui->widget), UI_MAIN_TAILLE_X, UI_MAIN_TAILLE_Y);
	gtk_window_maximize(GTK_WINDOW(ui->widget));
	
	// ===--- Layout : Box principale
	ui->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_MAIN_ESPACEMENT);
	
	// ===--- Layout : Box des menus
	ui->boxMenu = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
	// --- Widgets : Barre de menu + items
	ui->menuBarre = gtk_menu_bar_new();
	ui->ssMenu1 = gtk_menu_new();
	ui->ssMenu2 = gtk_menu_new();
	ui->ssMenu3 = gtk_menu_new();
	ui->ssMenu4 = gtk_menu_new();
	
	ui->ssMenuItem1 = gtk_menu_item_new_with_label("Fichier");
	ui->ssMenuItem2 = gtk_menu_item_new_with_label("Edition");
	ui->ssMenuItem3 = gtk_menu_item_new_with_label("Affichage");
	ui->ssMenuItem4 = gtk_menu_item_new_with_label("Aide");
	ui->ssMenuItem5 = gtk_menu_item_new_with_label("A faire Fichier");
	ui->ssMenuItem6 = gtk_menu_item_new_with_label("A faire Edition");
	ui->ssMenuItem7 = gtk_menu_item_new_with_label("A faire Affichage");
	ui->ssMenuItem8 = gtk_menu_item_new_with_label("A faire Aide & credit");
	
	// On définit les noms des sous-menus en tant qu'item
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(ui->ssMenuItem1), ui->ssMenu1);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(ui->ssMenuItem2), ui->ssMenu2);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(ui->ssMenuItem3), ui->ssMenu3);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(ui->ssMenuItem4), ui->ssMenu4);
	
	// On connecte les sous-menus avec les choix
	gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu1), ui->ssMenuItem5);
	gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu2), ui->ssMenuItem6);
	gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu3), ui->ssMenuItem7);
	gtk_menu_shell_append(GTK_MENU_SHELL(ui->ssMenu4), ui->ssMenuItem8);
	
	// On ajoute les items a la barre de menu
	gtk_menu_shell_append(GTK_MENU_SHELL(ui->menuBarre), ui->ssMenuItem1);
	gtk_menu_shell_append(GTK_MENU_SHELL(ui->menuBarre), ui->ssMenuItem2);
	gtk_menu_shell_append(GTK_MENU_SHELL(ui->menuBarre), ui->ssMenuItem3);
	gtk_menu_shell_append(GTK_MENU_SHELL(ui->menuBarre), ui->ssMenuItem4);
	
	// ===--- Layout : Frame de l'en-tete + Box de l'en-tete (boutons + choix carte)
	ui->frameEntete = gtk_frame_new("");
	ui->boxEntete = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
	// ===--- Layout : Box des boutons d'UI
	ui->boxUI = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
	// --- Widgets : Boutons des UI
	ui->boutonBoxTraces = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	ui->boutonBoxAnim = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	ui->boutonBoxAnon = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	ui->boutonTraces = gtk_button_new_with_label("Traces");
	ui->boutonAnimation = gtk_button_new_with_label("Animation");
	ui->boutonAnonymat = gtk_button_new_with_label("Anonymisation");
	
	// ===--- Layout : Frame du choix de la carte
	ui->frameCarte = gtk_frame_new("Carte");
	//--- Widgets : Elements du choix de la carte
	ui->boxCarte = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
	ui->frameEchelle = gtk_frame_new("");
	ui->labelEchelle = gtk_label_new("xEchelle");
	
	ui->selectCarte = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(ui->selectCarte), "0", "Cher");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(ui->selectCarte), "1", "Bourges");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(ui->selectCarte), "2", "Insa Bourges");
	gtk_combo_box_set_active(GTK_COMBO_BOX(ui->selectCarte), -1);
	
	
	// ===--- Layout : Zone de la carte
	ui->scrollCarteCher = gtk_scrolled_window_new(NULL, NULL);
	ui->scrollCarteBourges = gtk_scrolled_window_new(NULL, NULL);
	ui->scrollCarteInsa = gtk_scrolled_window_new(NULL, NULL);
	
	varGlobFront.overlayCarteCher = gtk_overlay_new();
	varGlobFront.overlayCarteBourges = gtk_overlay_new();
	varGlobFront.overlayCarteInsa = gtk_overlay_new();
	
	ui->imgCarteCher = gtk_image_new_from_file("../Data/cartes/carte_Cher.png");
	ui->imgCarteBourges = gtk_image_new_from_file("../Data/cartes/carte_Bourges.png");
	ui->imgCarteInsa = gtk_image_new_from_file("../Data/cartes/carte_Insa.png");

	gtk_widget_set_events(varGlobFront.overlayCarteCher, GDK_ENTER_NOTIFY_MASK);
    gtk_widget_set_events(varGlobFront.overlayCarteCher, GDK_POINTER_MOTION_MASK);
	
	/* J'ai modifié l'architecture du code du a quelques problemes avec Cairo
	 * Je mets ton travail en commentaire et j'etudierai les fonctions proposees
	 // ===--- Layout : zone de la carte
  ui->scrollCarte = gtk_scrolled_window_new(NULL, NULL);
  ui->bufferCarte = gdk_pixbuf_new_from_file_at_scale("../../Data/cartes/carte_Cher.png",1920-20,-1, TRUE, NULL);  //Permet de calibrer la taille la carte en passant un buffer
  // A relier aux cartes
  //                gdk_pixbuf_new_from_file_at_scale(cheminCarte, largeur-tailleBarreScroll, HauteurPasEnContrainte, GarderProportionnalités, MessageError)
	 
  ui->imgCarte    = gtk_image_new_from_pixbuf (ui->bufferCarte);
  */
	// ===================== Signaux =====================
	g_signal_connect(ui->boutonTraces, "clicked", G_CALLBACK(uiTraces), ui->widget);
	g_signal_connect(ui->boutonAnimation, "clicked", G_CALLBACK(uiAnimation), ui->widget);
	g_signal_connect(ui->boutonAnonymat, "clicked", G_CALLBACK(uiAnonymite), ui->widget);
	g_signal_connect(ui->selectCarte, "changed", G_CALLBACK(changeCarte), ui);

	// On instance les fenetres auxiliaires pour les creer puis on les cache
	g_signal_emit_by_name(ui->boutonAnonymat, "clicked", ui->widget);
	g_signal_emit_by_name(ui->boutonAnimation,  "clicked", ui->widget);
	
	// ==================== Packaging ====================
	// Fenetre principale <- Box principale
	gtk_container_add(GTK_CONTAINER(ui->widget), ui->boxPrincipale);
	// Box principale <- Box menu + Frame en-tete (UI + choix carte) + scrolls image carte
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->boxMenu, FALSE, FALSE, UI_MAIN_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->frameEntete, FALSE, FALSE, UI_MAIN_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->scrollCarteCher, TRUE, TRUE, UI_MAIN_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->scrollCarteBourges, TRUE, TRUE, UI_MAIN_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->scrollCarteInsa, TRUE, TRUE, UI_MAIN_ESPACEMENT);
	
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
	
	// Scrolls image <- Overlays carte
	gtk_container_add(GTK_CONTAINER(ui->scrollCarteCher), varGlobFront.overlayCarteCher);
	gtk_container_add(GTK_CONTAINER(ui->scrollCarteBourges), varGlobFront.overlayCarteBourges);
	gtk_container_add(GTK_CONTAINER(ui->scrollCarteInsa), varGlobFront.overlayCarteInsa);
	// Overlays carte <- Image de la carte
	gtk_container_add(GTK_CONTAINER(varGlobFront.overlayCarteCher), ui->imgCarteCher);
	gtk_container_add(GTK_CONTAINER(varGlobFront.overlayCarteBourges), ui->imgCarteBourges);
	gtk_container_add(GTK_CONTAINER(varGlobFront.overlayCarteInsa), ui->imgCarteInsa);
	
	/* On interdit aux cartes de s'auto-centrer si elles ont en la possibilite */
	gtk_widget_set_halign(ui->imgCarteCher, GTK_ALIGN_START);
	gtk_widget_set_halign(ui->imgCarteBourges, GTK_ALIGN_START);
	gtk_widget_set_halign(ui->imgCarteInsa, GTK_ALIGN_START);
	
	gtk_widget_set_valign(ui->imgCarteCher, GTK_ALIGN_START);
	gtk_widget_set_valign(ui->imgCarteBourges, GTK_ALIGN_START);
	gtk_widget_set_valign(ui->imgCarteInsa, GTK_ALIGN_START);
	// ==================== Affichage ====================
	gtk_widget_show_all(ui->widget);
	gtk_widget_hide(ui->scrollCarteCher);
	gtk_widget_hide(ui->scrollCarteBourges);
	gtk_widget_hide(ui->scrollCarteInsa);
}

void ajoutOverlays(tracesItem* ptrItem)
{
	GtkWidget* zoneDessinCher = gtk_drawing_area_new();
	GtkWidget* zoneDessinBourges = gtk_drawing_area_new();
	GtkWidget* zoneDessinInsa = gtk_drawing_area_new();
	
	varGlobFront.zoneDessinCher[varGlobFront.idTrajet] = zoneDessinCher;
	varGlobFront.zoneDessinBourges[varGlobFront.idTrajet] = zoneDessinBourges;
	varGlobFront.zoneDessinInsa[varGlobFront.idTrajet] = zoneDessinInsa;
	
	gtk_overlay_add_overlay(GTK_OVERLAY(varGlobFront.overlayCarteCher), zoneDessinCher);
	gtk_overlay_add_overlay(GTK_OVERLAY(varGlobFront.overlayCarteBourges), zoneDessinBourges);
	gtk_overlay_add_overlay(GTK_OVERLAY(varGlobFront.overlayCarteInsa), zoneDessinInsa);
	
	g_signal_connect(G_OBJECT(zoneDessinCher), "draw", G_CALLBACK(faire_tracesCher), ptrItem);
	g_signal_connect(G_OBJECT(zoneDessinBourges), "draw", G_CALLBACK(faire_tracesBourges), ptrItem);
	g_signal_connect(G_OBJECT(zoneDessinInsa), "draw", G_CALLBACK(faire_tracesInsa), ptrItem);
	
	gtk_widget_show(zoneDessinCher);
	gtk_widget_show(zoneDessinBourges);
	gtk_widget_show(zoneDessinInsa);
}

void changeCarte(GtkWidget *widget, gpointer user_data)
{
	uiMain* fenetre = (uiMain *)user_data;
	int idCarte = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
	
	if(idCarte==0)
	{
		gtk_widget_hide(fenetre->scrollCarteBourges);
		gtk_widget_hide(fenetre->scrollCarteInsa);
		gtk_widget_show(fenetre->scrollCarteCher);
	}
	else if(idCarte==1)
	{
		gtk_widget_hide(fenetre->scrollCarteCher);
		gtk_widget_hide(fenetre->scrollCarteInsa);
		gtk_widget_show(fenetre->scrollCarteBourges);
	}
	else
	{
		gtk_widget_hide(fenetre->scrollCarteBourges);
		gtk_widget_hide(fenetre->scrollCarteCher);
		gtk_widget_show(fenetre->scrollCarteInsa);
	}
	
}

void bougeCarte(GtkWidget *widget, gpointer user_data)
{
	// TODO
}

int overlayTempAjout(GtkWidget* zoneCercle, GtkWidget* eventBox, int id)
{
	int idCarte = gtk_combo_box_get_active(GTK_COMBO_BOX(ui->selectCarte));
	int i;
	if(idCarte==-1)
	{
		GtkWidget *dialog, *label, *content_area;
	    GtkDialogFlags flags;

	    // Create the widgets
	    flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
	    dialog = gtk_dialog_new_with_buttons("Message", GTK_WINDOW(ui->widget), flags,
	                                        "OK", GTK_RESPONSE_NONE, NULL);

	    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	    label = gtk_label_new("   Erreur ! \n   Aucune carte n'est sélectionnée !   ");

	    // Ensure that the dialog box is destroyed when the user responds
	    g_signal_connect_swapped (dialog, "response",
	                              G_CALLBACK (gtk_widget_destroy), dialog);
	    gtk_container_add (GTK_CONTAINER (content_area), label);
	    gtk_widget_show_all(dialog);
	    return 0;
	}
	else if(idCarte==0)
	{
		gtk_widget_realize(eventBox);
		g_signal_connect(G_OBJECT(zoneCercle), "draw", G_CALLBACK(traceCercle), NULL);
		g_signal_connect(G_OBJECT(eventBox), "motion-notify-event", G_CALLBACK(deplacementSouris), NULL);
		g_signal_connect(eventBox, "button-press-event", G_CALLBACK(clickCercle), NULL);

		gtk_container_add(GTK_CONTAINER(eventBox), zoneCercle);
		gtk_overlay_add_overlay(GTK_OVERLAY(varGlobFront.overlayCarteCher), eventBox);
		gtk_widget_add_events(eventBox, GDK_POINTER_MOTION_MASK);
		gtk_widget_set_events(eventBox, GDK_POINTER_MOTION_MASK);
		gtk_widget_show_all(eventBox);
	    for(i=0; i<NOMBRE_MAX_TRAJETS; i++)
	    {
	      if(i!=id && varGlobFront.trajetId[i]!=-1)
	      {
	        gtk_widget_hide(varGlobFront.zoneDessinCher[i]);
	      }
	    }
	}
	else if(idCarte==1)
	{
		g_signal_connect(G_OBJECT(zoneCercle), "draw", G_CALLBACK(traceCercle), NULL);
		g_signal_connect(G_OBJECT(eventBox), "motion-notify-event", G_CALLBACK(deplacementSouris), NULL);
		g_signal_connect(eventBox, "button-press-event", G_CALLBACK(clickCercle), NULL);

		gtk_container_add(GTK_CONTAINER(eventBox), zoneCercle);
		gtk_overlay_add_overlay(GTK_OVERLAY(varGlobFront.overlayCarteBourges), eventBox);
		gtk_widget_add_events(eventBox, GDK_POINTER_MOTION_MASK);
		gtk_widget_set_events(eventBox, GDK_POINTER_MOTION_MASK);
		gtk_widget_show_all(eventBox);
		for(i=0; i<NOMBRE_MAX_TRAJETS; i++)
	    {
	      if(i!=id && varGlobFront.trajetId[i]!=-1)
	      {
	        gtk_widget_hide(varGlobFront.zoneDessinBourges[i]);
	      }
	    }
	}
	else
	{
		g_signal_connect(G_OBJECT(zoneCercle), "draw", G_CALLBACK(traceCercle), NULL);
		g_signal_connect(G_OBJECT(eventBox), "motion-notify-event", G_CALLBACK(deplacementSouris), NULL);
		g_signal_connect(eventBox, "button-press-event", G_CALLBACK(clickCercle), NULL);

		gtk_container_add(GTK_CONTAINER(eventBox), zoneCercle);
		gtk_overlay_add_overlay(GTK_OVERLAY(varGlobFront.overlayCarteInsa), eventBox);
		gtk_widget_add_events(eventBox, GDK_POINTER_MOTION_MASK);
		gtk_widget_set_events(eventBox, GDK_POINTER_MOTION_MASK);
		gtk_widget_show_all(eventBox);
		for(i=0; i<NOMBRE_MAX_TRAJETS; i++)
	    {
	      if(i!=id && varGlobFront.trajetId[i]!=-1)
	      {
	        gtk_widget_hide(varGlobFront.zoneDessinInsa[i]);
	      }
	    }
	}
	return 1;
}

void overlayTempSuppr(GtkWidget* eventBox, int id)
{
	int idCarte = gtk_combo_box_get_active(GTK_COMBO_BOX(ui->selectCarte));
	int i;
	if(idCarte==0) // Cher
	{
		gtk_container_remove(GTK_CONTAINER(varGlobFront.overlayCarteCher), eventBox);
		for(i=0; i<NOMBRE_MAX_TRAJETS; i++)
	    {
	      if(i!=id && varGlobFront.trajetId[i]!=-1)
	      {
	        gtk_widget_show(varGlobFront.zoneDessinCher[i]);
	      }
	    }
	}
	else if(idCarte==1) // Bourges
	{
		gtk_container_remove(GTK_CONTAINER(varGlobFront.overlayCarteBourges), eventBox);
		for(i=0; i<NOMBRE_MAX_TRAJETS; i++)
	    {
	      if(i!=id && varGlobFront.trajetId[i]!=-1)
	      {
	        gtk_widget_show(varGlobFront.zoneDessinInsa[i]);
	      }
	    }
	}
	else // Insa
	{
		gtk_container_remove(GTK_CONTAINER(varGlobFront.overlayCarteInsa), eventBox);
		for(i=0; i<NOMBRE_MAX_TRAJETS; i++)
	    {
	      if(i!=id && varGlobFront.trajetId[i]!=-1)
	      {
	        gtk_widget_show(varGlobFront.zoneDessinInsa[i]);
	      }
	    }
	}
}

void bloqueCarte()
{
	gtk_widget_set_sensitive(ui->boutonTraces, FALSE);
	gtk_widget_set_sensitive(ui->boutonAnimation, FALSE);
	gtk_widget_set_sensitive(ui->selectCarte, FALSE);
}

void debloqueCarte()
{
	gtk_widget_set_sensitive(ui->boutonTraces, TRUE);
	gtk_widget_set_sensitive(ui->boutonAnimation, TRUE);
	gtk_widget_set_sensitive(ui->selectCarte, TRUE);
}
