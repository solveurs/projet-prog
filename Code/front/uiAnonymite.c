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
 * Spin button
 * Fonction calendrier
 * Modifier faire_trace en fonction du temps
 * Fonction avancer, reculer
 * Doxygen
 *
 * ====================
 *        MaJ
 * ====================
 * Creation du fichier.
 * Ceci n'est que le squelette graphique, les fonctions ne sont pas encore ecrites.
 *
*/

#include "../headers/front.h"
//#include "../headers/uiAnonymite.h"

static uiAnon* fenetreAnon;
//static GtkWidget* fenetrePrincipale;
static GtkWidget* ZONE_CERCLE;
static GtkWidget* EVENT_BOX;

static point CERCLE_BORD;
static cercle CERCLE_UTILISATEUR;
static int CLICKED = 0;


int uiAnonymite(GtkWidget* widget, gpointer user_data)
{
  static int etat = UI_ANON_FERME;

  if(!etat)
  {
    // ============== Initialisation widgets =============
    // ====== Validation d'ouverture
    etat = UI_ANON_OUVERT;

    // ====== Layout : Fenetre principale
    fenetreAnon = (uiAnon *)malloc(sizeof(uiAnon));

    if(fenetreAnon == NULL)
    {
      printf("Erreur malloc anonUI");
      exit(EXIT_FAILURE);
    }

    fenetreAnon->widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(fenetreAnon->widget), "Gestion de l'anonymat");
    gtk_window_set_position(GTK_WINDOW(fenetreAnon->widget), GTK_WIN_POS_MOUSE);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(fenetreAnon->widget), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(fenetreAnon->widget), GTK_WINDOW(user_data));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(fenetreAnon->widget), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(fenetreAnon->widget), UI_ANON_TAILLE_X, UI_ANON_TAILLE_Y);

    // ====== Layout : Box principale
    fenetreAnon->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_ANON_ESPACEMENT);

    // ------ Widget : Bouton de tracer du cercle
	  fenetreAnon->frameFigure = gtk_frame_new("Tracer une zone d'anonymat");
    fenetreAnon->boutonCercle = gtk_button_new();
    fenetreAnon->imgCercle = gtk_image_new_from_file("../Data/icones/circle-outline-64.png");
    gtk_button_set_image(GTK_BUTTON(fenetreAnon->boutonCercle), fenetreAnon->imgCercle);

    // ---=== Layout : Box de confirmation du tracer
    fenetreAnon->boxTracer = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_ANON_ESPACEMENT);
    fenetreAnon->labelInfo = gtk_label_new("             === Instructions ===\
                                          \n  Click gauche : choix du centre du cercle\
                                          \n  Click droit  : tracer du cercle\
                                          \n  Bouger la souris pour définir le rayon\
                                          \n\n");
    fenetreAnon->boxBoutons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_ANON_ESPACEMENT);
    fenetreAnon->boutonAnnuler = gtk_button_new_with_label("Annuler");
    fenetreAnon->boutonConfirmer = gtk_button_new_with_label("Confirmer");

    // ---=== Layout : Frame du choix de cible
	  fenetreAnon->frameCible = gtk_frame_new("Trace ciblée");
       // --- Widget : Menu deroulant du choix de cible
    fenetreAnon->menuDeroulant = gtk_combo_box_text_new();

    // ---=== Layout : Frame de scroll des items
	  fenetreAnon->frameScroll = gtk_frame_new("Liste des zones anonymisées");
       // === Layout : Box + Zone de scroll
	  fenetreAnon->zoneScroll = gtk_scrolled_window_new(NULL, NULL);
	  fenetreAnon->boxItem = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_ANON_ESPACEMENT);

    // ===================== Signaux =====================
    g_signal_connect(fenetreAnon->widget, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
    g_signal_connect(fenetreAnon->boutonCercle, "clicked", G_CALLBACK(ajouteCercle), fenetreAnon);
    g_signal_connect(fenetreAnon->boutonAnnuler, "clicked", G_CALLBACK(annulerCercle), NULL);
    g_signal_connect(fenetreAnon->boutonConfirmer, "clicked", G_CALLBACK(confirmerCercle), NULL);
    //g_signal_connect(fenetreAnon->boutonCercle, "clicked", G_CALLBACK(ajoutItemAnon), fenetreAnon);

    // ==================== Packaging ====================
    // Fenetre principale <- Box principale
    gtk_container_add(GTK_CONTAINER(fenetreAnon->widget), fenetreAnon->boxPrincipale);
    // Box principale <- Frame figre + Box tracer +  Frame cible + Frame scroll
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxPrincipale), fenetreAnon->frameFigure, FALSE, FALSE, UI_ANON_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxPrincipale), fenetreAnon->boxTracer, FALSE, FALSE, UI_ANON_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxPrincipale), fenetreAnon->frameCible, FALSE, FALSE, UI_ANON_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxPrincipale), fenetreAnon->frameScroll, TRUE, TRUE, UI_ANON_ESPACEMENT);

      // Frame figure <- Bouton cercle
    gtk_container_add(GTK_CONTAINER(fenetreAnon->frameFigure), fenetreAnon->boutonCercle);
      // Box tracer <- Label info + Box boutons
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxTracer), fenetreAnon->labelInfo, FALSE, TRUE, UI_ANON_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxTracer), fenetreAnon->boxBoutons, FALSE, TRUE, UI_ANON_ESPACEMENT);
        // Box boutons <- Boutons
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxBoutons), fenetreAnon->boutonAnnuler, TRUE, TRUE, UI_ANON_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(fenetreAnon->boxBoutons), fenetreAnon->boutonConfirmer, TRUE, TRUE, UI_ANON_ESPACEMENT);

      // Frame cible <- Menu deroulant
    gtk_container_add(GTK_CONTAINER(fenetreAnon->frameCible), fenetreAnon->menuDeroulant);

      // Frame scroll <- Zone scroll
    gtk_container_add(GTK_CONTAINER(fenetreAnon->frameScroll), fenetreAnon->zoneScroll);
      // Zone scroll <- Box des items
    gtk_container_add(GTK_CONTAINER(fenetreAnon->zoneScroll), fenetreAnon->boxItem);

    // ==================== Affichage ====================
    gtk_widget_show_all(fenetreAnon->widget);
    gtk_widget_hide(fenetreAnon->boxTracer);
    gtk_widget_hide(fenetreAnon->widget);

    return EXIT_SUCCESS;
  }
  else
  {
  	gtk_window_present(GTK_WINDOW(fenetreAnon->widget));
  }
	return EXIT_SUCCESS;
}

void annulerCercle(GtkWidget* widget, gpointer user_data)
{
  int idTraces = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnon->menuDeroulant));
  overlayTempSuppr(EVENT_BOX, idTraces);

  gtk_widget_hide(fenetreAnon->boxTracer);
  gtk_widget_show(fenetreAnon->boutonCercle);
  CERCLE_UTILISATEUR.centre.x = 0.0;
  CERCLE_UTILISATEUR.centre.y = 0.0;
  CERCLE_UTILISATEUR.rayon = 0.0;
  debloqueCarte();
}

void confirmerCercle(GtkWidget* widget, gpointer user_data)
{
  //IModeAnonymisation();
  int idTraces = gtk_combo_box_get_active(GTK_COMBO_BOX(fenetreAnon->menuDeroulant));
  overlayTempSuppr(EVENT_BOX, idTraces);

  CERCLE_UTILISATEUR.centre.x = conversionGPS(CERCLE_UTILISATEUR.centre.x, getCarte(), 1);
  CERCLE_UTILISATEUR.centre.y = conversionGPS(CERCLE_UTILISATEUR.centre.y, getCarte(), 0);
  CERCLE_UTILISATEUR.rayon = rayonGPS(CERCLE_UTILISATEUR.rayon, getCarte());

  int nb = anonymisationPendantEditionC(varGlobFront.traces[idTraces]->ptrTrajet, CERCLE_UTILISATEUR);
  majCartes(idTraces);
  char msg[64];
  sprintf(msg, "%d traces ont ete anonymisees !", nb);
  popupMessage("Succes !", msg, fenetreAnon->widget);

  gtk_widget_hide(fenetreAnon->boxTracer);
  gtk_widget_show(fenetreAnon->boutonCercle);
  CERCLE_UTILISATEUR.centre.x = 0.0;
  CERCLE_UTILISATEUR.centre.y = 0.0;
  CERCLE_UTILISATEUR.rayon = 0.0;
  debloqueCarte();
  IfinModeAnonymisation(*(varGlobFront.traces[idTraces]->ptrTrajet));
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
    gtk_window_set_position(GTK_WINDOW(popupAD->widget), GTK_WIN_POS_MOUSE);
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

void ajouteCercle(GtkWidget* widget, gpointer user_data)
{
  // Credits Gtk+ doc pour le dialog d'erreur
  // Function to open a dialog box with a message
  uiAnon* parent = (uiAnon *)user_data;
  int activeId = gtk_combo_box_get_active(GTK_COMBO_BOX(parent->menuDeroulant));
  if(activeId==-1)
  {
    GtkWidget *dialog, *label, *content_area;
    GtkDialogFlags flags;

    // Create the widgets
    flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons ("Message", GTK_WINDOW(parent->widget), flags,
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
    ZONE_CERCLE = gtk_drawing_area_new();
    EVENT_BOX = gtk_event_box_new();
    if(overlayTempAjout(ZONE_CERCLE, EVENT_BOX, activeId))
    {
      gtk_widget_queue_draw(ZONE_CERCLE);
      gtk_widget_hide(parent->boutonCercle);
      gtk_widget_show(parent->boxTracer);
      bloqueCarte(1);
    }
  }
}

/**
 * \fn      static void do_drawing(cairo_t *cr)
 * \brief   Initialise la carte et trace le cercle d'anonymat.
 *
 * \param   cr Pointeur sur un Cairo Context où on applique nos dessins.
 * \return  Void.
*/
void traceCercle(GtkWidget* widget, cairo_t* cr, gpointer user_data)
{
  cairo_set_source_rgb(cr, 1, 0, 0);
  cairo_set_line_width(cr, 2);  

  // Trace du cercle
  cairo_arc(cr, CERCLE_UTILISATEUR.centre.x, CERCLE_UTILISATEUR.centre.y, CERCLE_UTILISATEUR.rayon, 0, 2 * M_PI);
  cairo_stroke(cr); 
}

void ajoutMenuTracesAnon(const gchar* nom)
{
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(fenetreAnon->menuDeroulant), NULL, nom);
}

void supprimeMenuTracesAnon(gint id)
{
  gtk_combo_box_text_remove(GTK_COMBO_BOX_TEXT(fenetreAnon->menuDeroulant), id);
}

void renommeMenuTracesAnon(gint id, const gchar* nom)
{
  supprimeMenuTracesAnon(id);
  gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(fenetreAnon->menuDeroulant), id, nom);
}

void deplacementSouris(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
  /* Credits StackOverflow forum */
  if(CLICKED) 
  {
    // On recupere la position du curseur
    GdkEventMotion* e = (GdkEventMotion*)event;
    // Calcul du rayon puis tracer
    CERCLE_UTILISATEUR.rayon = rayonAnon(CERCLE_UTILISATEUR.centre, (int)(e->x), (int)(e->y));
    gtk_widget_queue_draw(ZONE_CERCLE); 
  }
}

/**
 * \fn      static int rayon(int centreX, int centreY, int rayonX, int rayonY)
 * \brief   Calcul le rayon d'un cercle.
 *
 * \param   centreX Coordonnees X du centre du cercle.
 * \param   centreY Coordonnees Y du centre du cercle.
 * \param   rayonX Coordonnees X du rayon du cercle.
 * \param   rayonY Coordonnees Y du rayon du cercle.
 * \return  Retourne la longueur du rayon.
*/
double rayonAnon(point centre, int rayonX, int rayonY)
{
  double hyp;
  double AB = fabs(rayonX - centre.x);
  double BC = fabs(rayonY - centre.y);

  // Pythagore, je t'invoque !!!!
  hyp = sqrt((AB*AB + BC*BC));

  return hyp;
}

/**
 * \fn      static gboolean clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
 * \brief   Detecte le click de la souris et agit en consequence.
 *
 * \param   widget      Instance a laquelle est rattachee le signal.
 * \param   event       Evenement lie au click de la souris.
 * \param   user_data   Donnees transferee par le signal.
 * \return  gboolean.
*/
void clickCercle(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
  if(event->button == 1)  // Premier click gauche.
  {
    if(CLICKED)           // Normalement au deuxieme, on anonymise.
    {
      //CERCLE_BORD.x = (double)event->x;
      //CERCLE_BORD.y = (double)event->y;
      CLICKED = 0;         
    }
    else                  // Au premier click, on definit le cercle.
    {
      CERCLE_UTILISATEUR.centre.x = (double)event->x;
      CERCLE_UTILISATEUR.centre.y = (double)event->y;
      CLICKED = 1;
    }
  }
}

