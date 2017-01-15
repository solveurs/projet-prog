/**
 * \file      uiAnimation.c
 * \brief     Fichier main de la GUI de gestion des traces.
 * \author    Thanh.L
 * \version   0.1a
 *
 * Le fichier contient toutes les fonctions liees au PopUp de gestion de l'animation.
 * ====================
 *       TODO
 * ====================
 * Faire les fonctions relatives aux calendriers.
 * + les fonctions relatives a l'affichage
 * Doxygen
 *
 * ====================
 *        MaJ
 * ====================
 * Creation du fichier
 *
*/

#include "../headers/front.h"
//#include "../headers/uiAnimation.h"

/**
 * \fn      int uiAnimation(GtkWidget* widget, gpointer user_data)
 * \brief   Affiche une GUI pour la gestion des animations.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  1 en cas de succès.
 *          0 sinon.
*/
int uiAnimation(GtkWidget* widget, gpointer user_data)
{
  // Variable static pour eviter de reconstruire la fenetre
  static int etat = UI_ANIM_FERME;

  // Declaration static pour eviter un SegFault
  static animUI* fenetreAnim;

  //gtk_init(&argc, &argv);
  if(!etat)
  {
    // ============== Initialisation widgets ==============
    // ====== Validation d'ouverture
    etat = UI_ANIM_OUVERT;

    // ====== Fenetre
    fenetreAnim = (animUI *)malloc(sizeof(animUI));

    if(fenetreAnim == NULL)
      exit(EXIT_FAILURE);

    fenetreAnim->widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(fenetreAnim->widget), "Animation des traces");
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(fenetreAnim->widget), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(fenetreAnim->widget), GTK_WINDOW(user_data));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(fenetreAnim->widget), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(fenetreAnim->widget), UI_ANIM_TAILLE_X, UI_ANIM_TAILLE_Y);

    // ===--- Layout : Box principale
	fenetreAnim->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_ANIM_ESPACEMENT);

	// ===--- Layout : Frame pour les dates + la box
	fenetreAnim->frameDate = gtk_frame_new("Intervalle de visionnage");
	fenetreAnim->boxFrame = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_ANIM_ESPACEMENT);

		// === Layout : Box calendriers
	fenetreAnim->boxPH = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANIM_ESPACEMENT);

			// === Layout : Grille debut + Grille fin
	fenetreAnim->gridPHG = gtk_grid_new();
	fenetreAnim->gridPHD = gtk_grid_new();

			// --- Widgets : Calendrier de debut (gauche)
	/* Initialisation de la date */
	fenetreAnim->dateDeb = malloc(sizeof(dateAnim));
	if(fenetreAnim->dateDeb == NULL)
	{
		printf("Erreur dateDeb");
		exit(EXIT_FAILURE);
	}
	fenetreAnim->dateDeb->jour = 1;
	fenetreAnim->dateDeb->mois = 1;
	fenetreAnim->dateDeb->annee = 2000;

	/* Initialisation des widgets */
  	fenetreAnim->labelPHG = gtk_label_new("Debut                           ");

  	fenetreAnim->entryZoneDeb =	gtk_entry_new();
  	gtk_entry_set_text(GTK_ENTRY(fenetreAnim->entryZoneDeb), "01/01/2000");
  	gtk_widget_set_can_focus(fenetreAnim->entryZoneDeb, FALSE);

  	fenetreAnim->boutonCalG = gtk_button_new();
    fenetreAnim->imgCalG = gtk_image_new_from_file("../Data/icones/calendar-Time-16.png");
    gtk_button_set_image(GTK_BUTTON(fenetreAnim->boutonCalG), fenetreAnim->imgCalG);
			// --- Widgets : Calendrier de fin (droite)
	/* Initialisation de la date */
	fenetreAnim->dateFin = malloc(sizeof(dateAnim));
	if(fenetreAnim->dateFin == NULL)
	{
		printf("Erreur dateFin");
		exit(EXIT_FAILURE);
	}
	fenetreAnim->dateFin->jour = 1;
	fenetreAnim->dateFin->mois = 1;
	fenetreAnim->dateFin->annee = 2018;

	/* Initialisation des widgets */
  	fenetreAnim->labelPHD = gtk_label_new("Fin                             ");

  	fenetreAnim->entryZoneFin =	gtk_entry_new();
  	gtk_widget_set_can_focus(fenetreAnim->entryZoneFin, FALSE);
  	gtk_entry_set_text(GTK_ENTRY(fenetreAnim->entryZoneFin), "01/01/2018");

  	fenetreAnim->boutonCalD = gtk_button_new();
    fenetreAnim->imgCalD = gtk_image_new_from_file("../Data/icones/calendar-Time-16.png");
    gtk_button_set_image(GTK_BUTTON(fenetreAnim->boutonCalD), fenetreAnim->imgCalD);


		//=== Box : vitesse
	fenetreAnim->boxPB = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANIM_ESPACEMENT);

		//--- Widgets : label + spin vitesse
	fenetreAnim->label = gtk_label_new("Vitesse");
	fenetreAnim->vitesse = gtk_spin_button_new(NULL, 1, 0);

	// ===--- Layout : Box contenant les boutons d'animation
	fenetreAnim->boxBoutons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANIM_ESPACEMENT);

  fenetreAnim->boutonArriere = gtk_button_new();
  fenetreAnim->boutonStop = gtk_button_new();
  fenetreAnim->boutonPlayPause = gtk_button_new();
  fenetreAnim->boutonAvance = gtk_button_new();

  fenetreAnim->imgArriere = gtk_image_new_from_file("../Data/icones/skipbackward-32.png");
  fenetreAnim->imgStop = gtk_image_new_from_file("../Data/icones/stop-32.png");
  fenetreAnim->imgPlayPause = gtk_image_new_from_file("../Data/icones/play-32.png");
  fenetreAnim->imgAvance = gtk_image_new_from_file("../Data/icones/skipforward-32.png");

  gtk_button_set_image(GTK_BUTTON(fenetreAnim->boutonArriere), fenetreAnim->imgArriere);
  gtk_button_set_image(GTK_BUTTON(fenetreAnim->boutonStop), fenetreAnim->imgStop);
  gtk_button_set_image(GTK_BUTTON(fenetreAnim->boutonPlayPause), fenetreAnim->imgPlayPause);
  gtk_button_set_image(GTK_BUTTON(fenetreAnim->boutonAvance), fenetreAnim->imgAvance);

	// ===--- Widget : Barre de selection
	fenetreAnim->select = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);

	// ===--- Layout : Box pour les cases d'affichage
	fenetreAnim->boxAffichage = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

		//--- Widgets : Entry zone non utilisable
	fenetreAnim->caseG = gtk_entry_new();
	fenetreAnim->caseD = gtk_entry_new();

    // ===================== Signaux =====================
    g_signal_connect(fenetreAnim->widget, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
    g_signal_connect(fenetreAnim->boutonCalG, "clicked", G_CALLBACK(setCalendrier), fenetreAnim->entryZoneDeb);
    g_signal_connect(fenetreAnim->boutonCalD, "clicked", G_CALLBACK(setCalendrier), fenetreAnim->entryZoneFin);

    g_signal_connect(fenetreAnim->boutonArriere, "clicked", G_CALLBACK(arriere), fenetreAnim);
    g_signal_connect(fenetreAnim->boutonStop, "clicked", G_CALLBACK(stop), fenetreAnim);
    g_signal_connect(fenetreAnim->boutonPlayPause, "clicked", G_CALLBACK(playPause), fenetreAnim);
    g_signal_connect(fenetreAnim->boutonAvance, "clicked", G_CALLBACK(avance), fenetreAnim);


    // ==================== Packaging ====================
    // Fenetre principale <- Box principale
    gtk_container_add(GTK_CONTAINER(fenetreAnim->widget), fenetreAnim->boxPrincipale);

    // Box principale <- Frame date + Box boutons + Selectionneur + Box d'affichage
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPrincipale), fenetreAnim->frameDate, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPrincipale), fenetreAnim->boxBoutons, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPrincipale), fenetreAnim->select, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPrincipale), fenetreAnim->boxAffichage, TRUE, FALSE, UI_ANIM_ESPACEMENT);

		// Frame date <- Box frame
	gtk_container_add(GTK_CONTAINER(fenetreAnim->frameDate), fenetreAnim->boxFrame);
			// Box frame <- Box partie haute + Box partie basse
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxFrame), fenetreAnim->boxPH, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxFrame), fenetreAnim->boxPB, TRUE, FALSE, UI_ANIM_ESPACEMENT);
				// Box partie haute <- Box gauche + Box droite
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPH), fenetreAnim->gridPHG, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPH), fenetreAnim->gridPHD, TRUE, FALSE, UI_ANIM_ESPACEMENT);
					// Grille gauche <- Label debut + EntryZone debut + Bouton calendrier debut
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHG), fenetreAnim->labelPHG, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHG), fenetreAnim->entryZoneDeb, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHG), fenetreAnim->boutonCalG, 1, 1, 1, 1);
					// Grille droite <- Label fin + EntryZone fin + Bouton calendrier fin
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHD), fenetreAnim->labelPHD, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHD), fenetreAnim->entryZoneFin, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHD), fenetreAnim->boutonCalD, 1, 1, 1, 1);
				// Box partie basse <- Label vitesse + Spin vitesse
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPB), fenetreAnim->label, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPB), fenetreAnim->vitesse, TRUE, FALSE, UI_ANIM_ESPACEMENT);

		// Box bouton <- Boutons
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxBoutons), fenetreAnim->boutonArriere, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxBoutons), fenetreAnim->boutonStop, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxBoutons), fenetreAnim->boutonPlayPause, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxBoutons), fenetreAnim->boutonAvance, TRUE, FALSE, UI_ANIM_ESPACEMENT);

		// Box d'affichage <- Case de gauche + Case de droite
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxAffichage), fenetreAnim->caseG, TRUE, TRUE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxAffichage), fenetreAnim->caseD, TRUE, TRUE, UI_ANIM_ESPACEMENT);

    // ==================== Affichage ====================
    gtk_widget_show_all(fenetreAnim->widget);
    gtk_widget_hide(fenetreAnim->widget);
  }
  else
  {
    gtk_window_present(GTK_WINDOW(fenetreAnim->widget));
  }

  return EXIT_SUCCESS;
}

void setCalendrier(GtkWidget* widget, gpointer user_data)
{
  static int etat = UI_ANIM_FERME;
  static calUI* popupCal;

  if(!etat)
  {
  	// ============== Initialisation widgets ==============
  	// ====== Validation d'ouverture
  	popupCal = (calUI *) malloc(sizeof(calUI));
  	if(popupCal == NULL)
  	{
  	  printf("Erreur malloc calUI");
  	  exit(EXIT_FAILURE);
  	}
  	etat = UI_ANIM_OUVERT;

  	// ====== Fenetre
  	popupCal->widget = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_position(GTK_WINDOW(popupCal->widget), GTK_WIN_POS_MOUSE);
	gtk_window_set_keep_above(GTK_WINDOW(popupCal->widget), TRUE);
	gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popupCal->widget), TRUE);
	gtk_window_set_modal(GTK_WINDOW(popupCal->widget), TRUE);
	gtk_window_set_destroy_with_parent(GTK_WINDOW(popupCal->widget), TRUE);

	// ---=== Layout : Box principale
	popupCal->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_ANIM_ESPACEMENT);

	// ------ Widget : Calendrier
	popupCal->calendrier = gtk_calendar_new();

	// ---=== Layout : Box boutons
	popupCal->boxBoutons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANIM_ESPACEMENT);

		//--- Widgets : Boutons
	popupCal->boutonAnnuler = gtk_button_new_with_label("Annuler");
	popupCal->boutonConfirmer = gtk_button_new_with_label("Confirmer");

	// ===================== Signaux =====================
	GtkWidget* entryZone = (GtkWidget *) user_data;
	g_signal_connect(popupCal->boutonAnnuler, "clicked", G_CALLBACK(annulerCal), popupCal->widget);
	g_signal_connect(popupCal->boutonConfirmer, "clicked", G_CALLBACK(confirmerCal), entryZone);

	// ==================== Packaging ====================
	// Box principale <- calendrier + box boutons
	gtk_container_add(GTK_CONTAINER(popupCal->widget), popupCal->boxPrincipale);
	gtk_box_pack_start(GTK_BOX(popupCal->boxPrincipale), popupCal->calendrier, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(popupCal->boxPrincipale), popupCal->boxBoutons, TRUE, FALSE, UI_ANIM_ESPACEMENT);

	// Box boutons <- boutons
	gtk_box_pack_start(GTK_BOX(popupCal->boxPrincipale), popupCal->boxBoutons, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(popupCal->boxBoutons), popupCal->boutonAnnuler, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(popupCal->boxBoutons), popupCal->boutonConfirmer, TRUE, FALSE, UI_ANIM_ESPACEMENT);

	// ==================== Affichage ====================
	gtk_widget_show_all(popupCal->widget);
  }
  else
  {
  	popupCal->calendrier = gtk_calendar_new();
  	gtk_window_set_position(GTK_WINDOW(popupCal->widget), GTK_WIN_POS_MOUSE);
  	gtk_window_present(GTK_WINDOW(popupCal->widget));
  }
}

void annulerCal(GtkWidget* widget, gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(user_data));
}

void confirmerCal(GtkWidget* widget, gpointer user_data)
{
  animUI* fenetreAnim = (animUI *)user_data;
	// TODO
}

void arriere(GtkWidget* widget, gpointer user_data)
{
  animUI* fenetreAnim = (animUI *)user_data;
	// TODO
}

void stop(GtkWidget* widget, gpointer user_data)
{
  animUI* fenetreAnim = (animUI *)user_data;
	// TODO
}

void playPause(GtkWidget* widget, gpointer user_data)
{
  static int active = 1;
  animUI* fenetreAnim = (animUI *)user_data;
  if(active)
  {
    active = 0;
    gtk_image_set_from_file(GTK_IMAGE(fenetreAnim->imgPlayPause), "../Data/icones/pause-32.png");

    // TODO

  }
  else
  {
    active = 1;
    gtk_image_set_from_file(GTK_IMAGE(fenetreAnim->imgPlayPause), "../Data/icones/play-32.png");

    // TODO


  }
}

void avance(GtkWidget* widget, gpointer user_data)
{
  animUI* fenetreAnim = (animUI *)user_data;
	// TODO
}
