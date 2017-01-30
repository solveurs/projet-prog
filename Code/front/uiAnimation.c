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
#include <time.h>

// Declaration static pour eviter un SegFault
static animUI* fenetreAnim;

/* Variables globales au fichier */
static struct tm dateDebut;
static time_t tpsDebut;
static struct tm dateFin;
static time_t tpsFin;
static int    ANIMER;
static int    VITESSE_SPIN;

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

    /* Initialisation calendriers */
    fenetreAnim->calendrierDeb = gtk_calendar_new();
    dateDebut.tm_mday = 1;
    dateDebut.tm_mon = 0;
    dateDebut.tm_year = 100;
    dateDebut.tm_isdst = -1;
    fenetreAnim->calendrierFin = gtk_calendar_new();
    dateFin.tm_mday = 1;
    dateFin.tm_mon = 0;
    dateFin.tm_year = 150;
    dateFin.tm_isdst = -1;

    tpsDebut = mktime(&dateDebut);
    tpsFin = mktime(&dateFin);



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
  	fenetreAnim->labelPHG = gtk_label_new("Debut                           ");

  	fenetreAnim->entryZoneDeb =	gtk_entry_new();
  	gtk_entry_set_text(GTK_ENTRY(fenetreAnim->entryZoneDeb), "01/01/2000");
  	gtk_widget_set_can_focus(fenetreAnim->entryZoneDeb, FALSE);

  	fenetreAnim->boutonCalG = gtk_button_new();
    fenetreAnim->imgCalG = gtk_image_new_from_file("../Data/icones/calendar-Time-16.png");
    gtk_button_set_image(GTK_BUTTON(fenetreAnim->boutonCalG), fenetreAnim->imgCalG);

    fenetreAnim->boxComboG = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    fenetreAnim->comboHG = gtk_combo_box_text_new();
    fenetreAnim->comboMG = gtk_combo_box_text_new();
    fenetreAnim->comboSG = gtk_combo_box_text_new();
			// --- Widgets : Calendrier de fin (droite)
  	fenetreAnim->labelPHD = gtk_label_new("Fin                             ");

  	fenetreAnim->entryZoneFin =	gtk_entry_new();
  	gtk_widget_set_can_focus(fenetreAnim->entryZoneFin, FALSE);
  	gtk_entry_set_text(GTK_ENTRY(fenetreAnim->entryZoneFin), "01/01/2050");

  	fenetreAnim->boutonCalD = gtk_button_new();
    fenetreAnim->imgCalD = gtk_image_new_from_file("../Data/icones/calendar-Time-16.png");
    gtk_button_set_image(GTK_BUTTON(fenetreAnim->boutonCalD), fenetreAnim->imgCalD);

    fenetreAnim->boxComboD = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    fenetreAnim->comboHD = gtk_combo_box_text_new();
    fenetreAnim->comboMD = gtk_combo_box_text_new();
    fenetreAnim->comboSD = gtk_combo_box_text_new();

    /* Initialiastion des comboboxes */
    initCombo();

		//=== Box : vitesse
	fenetreAnim->boxPB = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANIM_ESPACEMENT);

		//--- Widgets : label + spin vitesse
	fenetreAnim->label = gtk_label_new("Vitesse (en trace)");
	fenetreAnim->vitesse = gtk_spin_button_new_with_range(1, 1000, 1);

	// ===--- Layout : Frame pour la trace ciblee
    fenetreAnim->frameCible = gtk_frame_new("Trace ciblée");
    fenetreAnim->menuDeroulant = gtk_combo_box_text_new();
    gtk_combo_box_set_active(GTK_COMBO_BOX(fenetreAnim->menuDeroulant), -1);
    fenetreAnim->boxFrameCible = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANIM_ESPACEMENT);
    fenetreAnim->boutonMode = gtk_button_new_with_label("Valider");

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

	// ===--- Layout : Box pour les cases d'affichage
	fenetreAnim->boxAffichage = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
		//--- Widgets : Label
	fenetreAnim->labelDate = gtk_label_new("Date non definie");
	fenetreAnim->labelHeure = gtk_label_new("--:--:--");

    // ===================== Signaux =====================
    g_signal_connect(fenetreAnim->widget, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
    g_signal_connect(fenetreAnim->boutonCalG, "clicked", G_CALLBACK(setCalendrierDebut), NULL);
    g_signal_connect(fenetreAnim->boutonCalD, "clicked", G_CALLBACK(setCalendrierFin), NULL);
    g_signal_connect(fenetreAnim->boutonMode, "clicked", G_CALLBACK(changeMode), NULL);

    g_signal_connect(fenetreAnim->boutonArriere, "clicked", G_CALLBACK(arriere), NULL);
    g_signal_connect(fenetreAnim->boutonStop, "clicked", G_CALLBACK(stop), NULL);
    g_signal_connect(fenetreAnim->boutonPlayPause, "clicked", G_CALLBACK(playPause), NULL);
    g_signal_connect(fenetreAnim->boutonAvance, "clicked", G_CALLBACK(avance), NULL);


    // ==================== Packaging ====================
    // Fenetre principale <- Box principale
    gtk_container_add(GTK_CONTAINER(fenetreAnim->widget), fenetreAnim->boxPrincipale);

    // Box principale <- Frame date + Frame Cible + Box boutons + Box d'affichage
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPrincipale), fenetreAnim->frameDate, FALSE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPrincipale), fenetreAnim->frameCible, FALSE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPrincipale), fenetreAnim->boxBoutons, FALSE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPrincipale), fenetreAnim->boxAffichage, FALSE, FALSE, UI_ANIM_ESPACEMENT);

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
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHG), fenetreAnim->boxComboG, 0, 2, 1, 1);
					// Grille droite <- Label fin + EntryZone fin + Bouton calendrier fin
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHD), fenetreAnim->labelPHD, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHD), fenetreAnim->entryZoneFin, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHD), fenetreAnim->boutonCalD, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(fenetreAnim->gridPHD), fenetreAnim->boxComboD, 0, 2, 1, 1);
				// Box partie basse <- Label vitesse + Spin vitesse
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPB), fenetreAnim->label, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxPB), fenetreAnim->vitesse, TRUE, TRUE, UI_ANIM_ESPACEMENT);
        
        // Box combo <- Comboboxes
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxComboG), fenetreAnim->comboHG, TRUE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxComboG), fenetreAnim->comboMG, TRUE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxComboG), fenetreAnim->comboSG, TRUE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxComboD), fenetreAnim->comboHD, TRUE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxComboD), fenetreAnim->comboMD, TRUE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxComboD), fenetreAnim->comboSD, TRUE, FALSE, 1);

	    // Frame cible <- Box cible
	gtk_container_add(GTK_CONTAINER(fenetreAnim->frameCible), fenetreAnim->boxFrameCible);
			// Box cible <- Menu deroulant + Bouton mode
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxFrameCible), fenetreAnim->menuDeroulant, TRUE, TRUE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxFrameCible), fenetreAnim->boutonMode, FALSE, FALSE, UI_ANIM_ESPACEMENT);

		// Box bouton <- Boutons
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxBoutons), fenetreAnim->boutonArriere, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxBoutons), fenetreAnim->boutonStop, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxBoutons), fenetreAnim->boutonPlayPause, TRUE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxBoutons), fenetreAnim->boutonAvance, TRUE, FALSE, UI_ANIM_ESPACEMENT);

		// Box d'affichage <- Case de gauche + Case de droite
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxAffichage), fenetreAnim->labelDate, FALSE, FALSE, UI_ANIM_ESPACEMENT);
	gtk_box_pack_start(GTK_BOX(fenetreAnim->boxAffichage), fenetreAnim->labelHeure, FALSE, FALSE, UI_ANIM_ESPACEMENT);

    // ==================== Affichage ====================
    gtk_widget_show_all(fenetreAnim->widget);
    gtk_widget_hide(fenetreAnim->widget);
    gtk_widget_hide(fenetreAnim->boxBoutons);
    gtk_widget_hide(fenetreAnim->boxAffichage);
  }
  else
  {
    gtk_window_present(GTK_WINDOW(fenetreAnim->widget));
  }

  return EXIT_SUCCESS;
}

void setCalendrierDebut(GtkWidget* widget, gpointer user_data)
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

	// ---=== Layout : Box boutons
	popupCal->boxBoutons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANIM_ESPACEMENT);

		//--- Widgets : Boutons
	popupCal->boutonAnnuler = gtk_button_new_with_label("Annuler");
	popupCal->boutonConfirmer = gtk_button_new_with_label("Confirmer");

	// ===================== Signaux =====================
	g_signal_connect(popupCal->boutonAnnuler, "clicked", G_CALLBACK(annulerCal), popupCal->widget);
	g_signal_connect(popupCal->boutonConfirmer, "clicked", G_CALLBACK(confirmerCalDebut), popupCal);

	// ==================== Packaging ====================
	// Box principale <- calendrier + box boutons
	gtk_container_add(GTK_CONTAINER(popupCal->widget), popupCal->boxPrincipale);
	gtk_box_pack_start(GTK_BOX(popupCal->boxPrincipale), fenetreAnim->calendrierDeb, TRUE, FALSE, UI_ANIM_ESPACEMENT);
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
  	gtk_window_set_position(GTK_WINDOW(popupCal->widget), GTK_WIN_POS_MOUSE);
  	gtk_window_present(GTK_WINDOW(popupCal->widget));
  }
}

void setCalendrierFin(GtkWidget* widget, gpointer user_data)
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

	// ---=== Layout : Box boutons
	popupCal->boxBoutons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANIM_ESPACEMENT);

		//--- Widgets : Boutons
	popupCal->boutonAnnuler = gtk_button_new_with_label("Annuler");
	popupCal->boutonConfirmer = gtk_button_new_with_label("Confirmer");

	// ===================== Signaux =====================
	g_signal_connect(popupCal->boutonAnnuler, "clicked", G_CALLBACK(annulerCal), popupCal->widget);
	g_signal_connect(popupCal->boutonConfirmer, "clicked", G_CALLBACK(confirmerCalFin), popupCal);

	// ==================== Packaging ====================
	// Box principale <- calendrier + box boutons
	gtk_container_add(GTK_CONTAINER(popupCal->widget), popupCal->boxPrincipale);
	gtk_box_pack_start(GTK_BOX(popupCal->boxPrincipale), fenetreAnim->calendrierFin, TRUE, FALSE, UI_ANIM_ESPACEMENT);
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
  	gtk_window_set_position(GTK_WINDOW(popupCal->widget), GTK_WIN_POS_MOUSE);
  	gtk_window_present(GTK_WINDOW(popupCal->widget));
  }
}

void annulerCal(GtkWidget* widget, gpointer user_data)
{
	gtk_widget_hide(GTK_WIDGET(user_data));
}

void confirmerCalDebut(GtkWidget* widget, gpointer user_data)
{
	gtk_calendar_get_date(GTK_CALENDAR(fenetreAnim->calendrierDeb), &(dateDebut.tm_year), &(dateDebut.tm_mon), &(dateDebut.tm_mday));

	char dateTmp[16];
	sprintf(dateTmp, "%d/%d/%d", dateDebut.tm_mday, dateDebut.tm_mon+1, dateDebut.tm_year);
	gtk_entry_set_text(GTK_ENTRY(fenetreAnim->entryZoneDeb), dateTmp);

	dateDebut.tm_year  -= 1900;
	gtk_widget_hide(GTK_WIDGET(user_data));
}

void confirmerCalFin(GtkWidget* widget, gpointer user_data)
{
  	gtk_calendar_get_date(GTK_CALENDAR(fenetreAnim->calendrierFin), &(dateFin.tm_year), &(dateFin.tm_mon), &(dateFin.tm_mday));

  	char dateTmp[16];
	sprintf(dateTmp, "%d/%d/%d", dateFin.tm_mday, dateFin.tm_mon+1, dateFin.tm_year);
	gtk_entry_set_text(GTK_ENTRY(fenetreAnim->entryZoneFin), dateTmp);

	dateFin.tm_year  -= 1900;
  	gtk_widget_hide(GTK_WIDGET(user_data));
}

void changeMode(GtkWidget* widget, gpointer user_data)
{
	// Credits Gtk+ doc pour le dialog d'erreur
  // Function to open a dialog box with a message
  int activeId = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->menuDeroulant));
  if(activeId==-1)
  {
    GtkWidget *dialog, *label, *content_area;
    GtkDialogFlags flags;

    // Create the widgets
    flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons ("Message", GTK_WINDOW(fenetreAnim->widget), flags,
                                          "OK", GTK_RESPONSE_NONE, NULL);

    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    label = gtk_label_new("   Erreur ! \n   Aucunes traces sélectionnées !   ");

  	// Ensure that the dialog box is destroyed when the user responds
  	g_signal_connect_swapped (dialog, "response",
                            G_CALLBACK (gtk_widget_destroy), dialog);
  	gtk_container_add (GTK_CONTAINER (content_area), label);
  	gtk_widget_show_all(dialog);
  }
  else
  {
  	static active = 1;
  	if(active)
  	{
  		gtk_button_set_label(GTK_BUTTON(fenetreAnim->boutonMode), "Terminer");
  		getHeure();
  		bloqueCarte(0);
  		bloqueInterfaceAnim();
  		focusTrajet(getCarte(), gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->menuDeroulant)));

  		setLimite(0);
  		VITESSE_SPIN = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(fenetreAnim->vitesse));
  		setVitesse(VITESSE_SPIN);

  		switchMode(MODE_ANIMATION);
  		active = 0;
  	}
  	else
  	{
      printf("\nNON LAAAA");
  		gtk_button_set_label(GTK_BUTTON(fenetreAnim->boutonMode), "Valider");
  		debloqueCarte();
  		debloqueInterfaceAnim();
  		defocusTrajet(getCarte(), gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->menuDeroulant)));

      majCartes(activeId);
  		switchMode(MODE_NORMAL);
  		active = 1;
  	}
	}
}

void getHeure()
{
	dateDebut.tm_hour = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->comboHG));
	dateDebut.tm_min = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->comboMG));
	dateDebut.tm_sec = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->comboSG));
	tpsDebut = mktime(&dateDebut);

	dateFin.tm_hour = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->comboHD));
	dateFin.tm_min = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->comboMD));
	dateFin.tm_sec = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->comboSD));
	tpsFin = mktime(&dateFin);
}

void arriere(GtkWidget* widget, gpointer user_data)
{
	int idTraces = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->menuDeroulant));
	decrLimite(VITESSE_SPIN);
	majCartes(idTraces);
}

void stop(GtkWidget* widget, gpointer user_data)
{
	ANIMER = 0;
}

void playPause(GtkWidget* widget, gpointer user_data)
{
  static int active = 1;
  if(active)
  {
    active = 0;
    gtk_image_set_from_file(GTK_IMAGE(fenetreAnim->imgPlayPause), "../Data/icones/pause-32.png");
    /*
    ANIMER = 1;

    while(ANIMER)
    {
    	Je comptais utiliser avanceAux en boucle
    	mais comme GTK est solo-thread, ca bloque toute la GUI
    }
    */

  }
  else
  {
  	ANIMER = 0;
    active = 1;
    gtk_image_set_from_file(GTK_IMAGE(fenetreAnim->imgPlayPause), "../Data/icones/play-32.png");
  }
}

void avance(GtkWidget* widget, gpointer user_data)
{
	int idTraces = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnim->menuDeroulant));
	incrLimite(VITESSE_SPIN, varGlobFront.traces[idTraces]->ptrTrajet->taille);
	majCartes(idTraces);
	resetOnce();
}

int avanceAux(gpointer user_data)
{
	avance(NULL, NULL);
	return 1;
}

void initCombo()
{
	char tmp[4];
	int i;
	for(i=0; i<24; i++)
	{
		sprintf(tmp, "%dH", i);
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(fenetreAnim->comboHG), NULL, tmp);
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(fenetreAnim->comboHD), NULL, tmp);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(fenetreAnim->comboHG), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(fenetreAnim->comboHD), 0);
	for(i=0; i<60; i++)
	{
		sprintf(tmp, "%dm", i);
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(fenetreAnim->comboMG), NULL, tmp);
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(fenetreAnim->comboMD), NULL, tmp);
		sprintf(tmp, "%ds", i);
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(fenetreAnim->comboSG), NULL, tmp);
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(fenetreAnim->comboSD), NULL, tmp);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(fenetreAnim->comboMG), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(fenetreAnim->comboMD), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(fenetreAnim->comboSG), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(fenetreAnim->comboSD), 0);
}

void ajoutMenuTracesAnim(const gchar* nom)
{
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(fenetreAnim->menuDeroulant), NULL, nom);
}

void supprimeMenuTracesAnim(gint id)
{
  gtk_combo_box_text_remove(GTK_COMBO_BOX_TEXT(fenetreAnim->menuDeroulant), id);
}

void renommeMenuTracesAnim(gint id, const gchar* nom)
{
  supprimeMenuTracesAnim(id);
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(fenetreAnim->menuDeroulant), id, nom);
}

void bloqueInterfaceAnim()
{
	gtk_widget_set_sensitive(fenetreAnim->boxFrame, FALSE);
	gtk_widget_set_sensitive(fenetreAnim->entryZoneDeb, FALSE);
	gtk_widget_set_sensitive(fenetreAnim->boutonCalG, FALSE);
    gtk_widget_set_sensitive(fenetreAnim->comboHG, FALSE);
    gtk_widget_set_sensitive(fenetreAnim->comboMG, FALSE);
    gtk_widget_set_sensitive(fenetreAnim->comboSG, FALSE);

    gtk_widget_set_sensitive(fenetreAnim->entryZoneFin, FALSE);
	gtk_widget_set_sensitive(fenetreAnim->boutonCalD, FALSE);
    gtk_widget_set_sensitive(fenetreAnim->comboHD, FALSE);
    gtk_widget_set_sensitive(fenetreAnim->comboMD, FALSE);
    gtk_widget_set_sensitive(fenetreAnim->comboSD, FALSE);

    gtk_widget_set_sensitive(fenetreAnim->vitesse, FALSE);

    gtk_widget_set_sensitive(fenetreAnim->menuDeroulant, FALSE);

    gtk_widget_show(fenetreAnim->boxBoutons);
    gtk_widget_show(fenetreAnim->boxAffichage);
}

void debloqueInterfaceAnim()
{
	gtk_widget_set_sensitive(fenetreAnim->boxFrame, TRUE);
	gtk_widget_set_sensitive(fenetreAnim->entryZoneDeb, TRUE);
	gtk_widget_set_sensitive(fenetreAnim->boutonCalG, TRUE);
    gtk_widget_set_sensitive(fenetreAnim->comboHG, TRUE);
    gtk_widget_set_sensitive(fenetreAnim->comboMG, TRUE);
    gtk_widget_set_sensitive(fenetreAnim->comboSG, TRUE);

    gtk_widget_set_sensitive(fenetreAnim->entryZoneFin, TRUE);
	gtk_widget_set_sensitive(fenetreAnim->boutonCalD, TRUE);
    gtk_widget_set_sensitive(fenetreAnim->comboHD, TRUE);
    gtk_widget_set_sensitive(fenetreAnim->comboMD, TRUE);
    gtk_widget_set_sensitive(fenetreAnim->comboSD, TRUE);

    gtk_widget_set_sensitive(fenetreAnim->vitesse, TRUE);

    gtk_widget_set_sensitive(fenetreAnim->menuDeroulant, TRUE);

	gtk_widget_hide(fenetreAnim->boxBoutons);
    gtk_widget_hide(fenetreAnim->boxAffichage);
}

int compareTps(time_t date)
{
	if( (date >= tpsDebut) && (date <= tpsFin))
	{
		return 1;
	}
	return 0;
}
