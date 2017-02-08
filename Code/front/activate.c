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
	gtk_window_set_title (GTK_WINDOW(ui->widget), "Geoloc v0.9");
	gtk_window_set_icon_from_file(GTK_WINDOW(ui->widget),"../Data/icones/logo_solveur-200.png",NULL);
	gtk_window_set_default_size (GTK_WINDOW(ui->widget), UI_MAIN_TAILLE_X, UI_MAIN_TAILLE_Y);
	gtk_window_maximize(GTK_WINDOW(ui->widget));

	// ===--- Layout : Box principale
	ui->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_MAIN_ESPACEMENT);

	// Barre de menu
	initialisation_menu(ui);

	// ===--- Layout : Frame de l'en-tete + Box de l'en-tete (boutons + choix carte)
	ui->frameEntete = gtk_frame_new("");
	ui->boxEntete = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
	// ===--- Layout : Box des boutons d'UI
	ui->boxUI = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
	// --- Widgets : Boutons des UI
	ui->boutonBoxTraces = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	ui->boutonBoxAnim = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	ui->boutonBoxAnon = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	ui->boutonTraces = gtk_button_new_with_label("Affichage des traces");
	ui->boutonAnimation = gtk_button_new_with_label("Animation des traces");
	ui->boutonAnonymat = gtk_button_new_with_label("Anonymisation des traces");

	// ===--- Layout : Frame du choix de la carte
	ui->frameCarte = gtk_frame_new("Carte");
	//--- Widgets : Elements du choix de la carte
	ui->boxCarte = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
	ui->imgCarte = gtk_image_new_from_file("../Data/icones/map-32.png");

	ui->selectCarte = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(ui->selectCarte), "0", "Cher");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(ui->selectCarte), "1", "Bourges");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(ui->selectCarte), "2", "Insa Bourges");
	gtk_combo_box_set_active(GTK_COMBO_BOX(ui->selectCarte), 0);

	// ===--- Layout : Zone de la carte
	ui->boxEventCher = gtk_event_box_new();
	g_signal_connect(G_OBJECT(ui->boxEventCher), "motion-notify-event", G_CALLBACK(getPosSouris), NULL);
	gtk_widget_add_events(ui->boxEventCher, GDK_POINTER_MOTION_MASK);
	gtk_widget_set_events(ui->boxEventCher, GDK_POINTER_MOTION_MASK);

	ui->boxEventBourges = gtk_event_box_new();
	g_signal_connect(G_OBJECT(ui->boxEventBourges), "motion-notify-event", G_CALLBACK(getPosSouris), NULL);
	gtk_widget_add_events(ui->boxEventBourges, GDK_POINTER_MOTION_MASK);
	gtk_widget_set_events(ui->boxEventBourges, GDK_POINTER_MOTION_MASK);

	ui->boxEventInsa = gtk_event_box_new();
	g_signal_connect(G_OBJECT(ui->boxEventInsa), "motion-notify-event", G_CALLBACK(getPosSouris), NULL);
	gtk_widget_add_events(ui->boxEventInsa, GDK_POINTER_MOTION_MASK);
	gtk_widget_set_events(ui->boxEventInsa, GDK_POINTER_MOTION_MASK);

	ui->boxScrolls = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_MAIN_ESPACEMENT);
	ui->scrollCarteCher = gtk_scrolled_window_new(NULL, NULL);
	ui->scrollCarteBourges = gtk_scrolled_window_new(NULL, NULL);
	ui->scrollCarteInsa = gtk_scrolled_window_new(NULL, NULL);

	varGlobFront.overlayCarteCher = gtk_overlay_new();
	varGlobFront.overlayCarteBourges = gtk_overlay_new();
	varGlobFront.overlayCarteInsa = gtk_overlay_new();

	ui->imgCarteCher = gtk_image_new_from_file("../Data/cartes/carte_Cher.png");
	ui->imgCarteBourges = gtk_image_new_from_file("../Data/cartes/carte_Bourges.png");
	ui->imgCarteInsa = gtk_image_new_from_file("../Data/cartes/carte_Insa.png");

	// ===--- Layout : Box footer
	ui->boxFooter = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_MAIN_ESPACEMENT);
	ui->labelPos = gtk_label_new("");

	// ===================== Signaux =====================
	g_signal_connect(ui->boutonTraces, "clicked", G_CALLBACK(uiTraces), ui->widget);
	g_signal_connect(ui->boutonAnimation, "clicked", G_CALLBACK(uiAnimation), ui->widget);
	g_signal_connect(ui->boutonAnonymat, "clicked", G_CALLBACK(uiAnonymite), ui->widget);
	g_signal_connect(ui->selectCarte, "changed", G_CALLBACK(changeCarte), ui);


	// On instance les fenetres auxiliaires pour les creer puis on les cache
	g_signal_emit_by_name(ui->boutonTraces, "clicked", ui->widget);
	g_signal_emit_by_name(ui->boutonAnonymat, "clicked", ui->widget);
	g_signal_emit_by_name(ui->boutonAnimation,  "clicked", ui->widget);

	// ==================== Packaging ====================:
	// Fenetre principale <- Box principale
	gtk_container_add(GTK_CONTAINER(ui->widget), ui->boxPrincipale);
	// Box principale <- Box menu + Frame en-tete (UI + choix carte) + Scrolls + Box footer
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->boxMenu, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->frameEntete, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->scrollCarteCher, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->scrollCarteBourges, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->scrollCarteInsa, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(ui->boxPrincipale), ui->boxFooter, FALSE, FALSE, 0);

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

	// Box carte <-Image + menu deroulant
	gtk_box_pack_start(GTK_BOX(ui->boxCarte), ui->imgCarte, FALSE, FALSE, UI_MAIN_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(ui->boxCarte), ui->selectCarte, TRUE, TRUE, UI_MAIN_ESPACEMENT);

	// Scrolls <- Box event
	gtk_container_add(GTK_CONTAINER(ui->scrollCarteCher), ui->boxEventCher);
	gtk_container_add(GTK_CONTAINER(ui->scrollCarteBourges), ui->boxEventBourges);
	gtk_container_add(GTK_CONTAINER(ui->scrollCarteInsa), ui->boxEventInsa);
	// Box events <- Overlays carte
	gtk_container_add(GTK_CONTAINER(ui->boxEventCher), varGlobFront.overlayCarteCher);
	gtk_container_add(GTK_CONTAINER(ui->boxEventBourges), varGlobFront.overlayCarteBourges);
	gtk_container_add(GTK_CONTAINER(ui->boxEventInsa), varGlobFront.overlayCarteInsa);
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

	/* Box footer <- Label pos */
	gtk_box_pack_start(GTK_BOX(ui->boxFooter), ui->labelPos, FALSE, FALSE, UI_MAIN_ESPACEMENT);

	// ==================== Affichage ====================
	gtk_widget_show_all(ui->widget);
	gtk_widget_hide(ui->scrollCarteCher);
	gtk_widget_hide(ui->scrollCarteBourges);
	gtk_widget_hide(ui->scrollCarteInsa);
	changeCarte(ui->selectCarte, ui);
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
		g_signal_connect(G_OBJECT(zoneCercle), "draw", G_CALLBACK(traceCercle), NULL);
		g_signal_connect(G_OBJECT(eventBox), "motion-notify-event", G_CALLBACK(deplacementSouris), NULL);
		g_signal_connect(eventBox, "button-press-event", G_CALLBACK(clickCercle), NULL);

		gtk_container_add(GTK_CONTAINER(eventBox), zoneCercle);
		gtk_overlay_add_overlay(GTK_OVERLAY(varGlobFront.overlayCarteCher), eventBox);
		gtk_widget_add_events(eventBox, GDK_POINTER_MOTION_MASK);
		gtk_widget_set_events(eventBox, GDK_POINTER_MOTION_MASK);
		gtk_widget_show_all(eventBox);
	    for(i=0; i<varGlobFront.idTrajet; i++)
	    {
	      if(i!=id)
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
		for(i=0; i<varGlobFront.idTrajet; i++)
	    {
	      if(i!=id)
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
		for(i=0; i<varGlobFront.idTrajet; i++)
	    {
	      if(i!=id)
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
		for(i=0; i<varGlobFront.idTrajet; i++)
	    {
	      if(i!=id)
	      {
	        gtk_widget_show(varGlobFront.zoneDessinCher[i]);
	      }
	    }
	}
	else if(idCarte==1) // Bourges
	{
		gtk_container_remove(GTK_CONTAINER(varGlobFront.overlayCarteBourges), eventBox);
		for(i=0; i<varGlobFront.idTrajet; i++)
	    {
	      if(i!=id)
	      {
	        gtk_widget_show(varGlobFront.zoneDessinInsa[i]);
	      }
	    }
	}
	else // Insa
	{
		gtk_container_remove(GTK_CONTAINER(varGlobFront.overlayCarteInsa), eventBox);
		for(i=0; i<varGlobFront.idTrajet; i++)
	    {
	      if(i!=id)
	      {
	        gtk_widget_hide(varGlobFront.zoneDessinInsa[i]);
	      }
	    }
	}
}

void bloqueCarte(int mode)
{
	gtk_widget_set_sensitive(ui->boutonTraces, FALSE);
	gtk_widget_set_sensitive(ui->selectCarte, FALSE);
	if(mode) // Mode anonymite
	{
		gtk_widget_set_sensitive(ui->boutonAnimation, FALSE);
	}
	else     // Mode animation
	{
		gtk_widget_set_sensitive(ui->boutonAnonymat, FALSE);
	}
}

void debloqueCarte()
{
	gtk_widget_set_sensitive(ui->boutonTraces, TRUE);
	gtk_widget_set_sensitive(ui->boutonAnimation, TRUE);
	gtk_widget_set_sensitive(ui->selectCarte, TRUE);
	gtk_widget_set_sensitive(ui->boutonAnonymat, TRUE);
}

int getCarte()
{
	return gtk_combo_box_get_active(GTK_COMBO_BOX(ui->selectCarte));
}

void getPosSouris(GtkWidget* widget, GdkEvent *event, gpointer user_data)
{
  /* Credits StackOverflow forum */
  /* On recupere la position du curseur */
  GdkEventMotion* e = (GdkEventMotion*)event;
  char text[64];
  sprintf(text, "Longitude : %lf,\t Latitude : %lf", conversionGPS(e->x, getCarte(), 1), conversionGPS(e->y, getCarte(), 0));
  gtk_label_set_text(GTK_LABEL(ui->labelPos), text);
}

void focusTrajet(int carte, int id)
{
	int i;
	switch(carte)
	{
		case 0: //Cher
			for(i=0; i<varGlobFront.idTrajet; i++)
			{
		      	if(i!=id)
		      	{
		        	gtk_widget_hide(varGlobFront.zoneDessinCher[i]);
		      	}
			}
		case 1: //Bourges
			for(i=0; i<varGlobFront.idTrajet; i++)
			{
		      	if(i!=id)
		      	{
		        	gtk_widget_hide(varGlobFront.zoneDessinBourges[i]);
		      	}
			}
		default: //Insa
			for(i=0; i<varGlobFront.idTrajet; i++)
			{
		      	if(i!=id)
		      	{
		        	gtk_widget_hide(varGlobFront.zoneDessinInsa[i]);
		      	}
			}
	}
}

void defocusTrajet(int carte, int id)
{
	int i;
	switch(carte)
	{
		case 0: //Cher
			for(i=0; i<varGlobFront.idTrajet; i++)
			{
		      	if(i!=id)
		      	{
		        	gtk_widget_show(varGlobFront.zoneDessinCher[i]);
		      	}
			}
		case 1: //Bourges
		for(i=0; i<varGlobFront.idTrajet; i++)
			{
		      	if(i!=id)
		      	{
		        	gtk_widget_show(varGlobFront.zoneDessinBourges[i]);
		      	}
			}
		case 2: //Insa
		for(i=0; i<varGlobFront.idTrajet; i++)
			{
		      	if(i!=id)
		      	{
		        	gtk_widget_show(varGlobFront.zoneDessinInsa[i]);
		      	}
			}
	}
}


void affUITraces()
{
	g_signal_emit_by_name(ui->boutonTraces, "clicked", ui->widget);
}

void affUIAnim()
{
	g_signal_emit_by_name(ui->boutonAnonymat, "clicked", ui->widget);
}

void affUIAnon()
{
	g_signal_emit_by_name(ui->boutonAnimation,  "clicked", ui->widget);
}
