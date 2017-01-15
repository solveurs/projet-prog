/**
 * \file      uiTraces.c
 * \brief     Fichier main de la GUI de gestion des traces.
 * \author    Thanh.L, Guillaume.F
 * \version   0.4a
 *
 * Le fichier contient toutes les fonctions liees au PopUp de gestion des traces.
 * ====================
 *       TODO
 * ====================
 * + Gerer la liberation de la memoire
 * + Prendre en compte les icones de Data/
 * ====================
 *        MaJ
 * ====================
 * Prise en compte de l'importation des traces.
 *
*/

#include "../headers/front.h"
/*#include "../headers/uiTraces.h"
#include "../headers/fonctionFront.h"
#include "../headers/activate.h"
#include "../headers/globalFront.h"*/

/**
 * \fn      int uiTraces(GtkWidget* widget, gpointer user_data)
 * \brief   Affiche une GUI pour la gestion des traces.
 *
 * \details La fonction est appelée suite à l'utilisation d'un bouton.
 *          Un signal est relié à ce bouton qui appelle la fonction.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  1 en cas de succès.
 *          0 sinon.
*/
int uiTraces(GtkWidget* widget, gpointer user_data)
{
  // Variable static pour eviter de reconstruire la fenetre
  static int etat = UI_TRACE_FERME;
  // Declaration static pour eviter un SegFault
  static tracesUI *fenetreTraces;

  if(!etat)
  {
    // ============== Initialisation widgets ==============
    // ====== Validation d'ouverture
    etat = UI_TRACE_OUVERT;

    // ====== Fenetre
    fenetreTraces = (tracesUI *)malloc(sizeof(tracesUI));
    /* Si on alloue manuellement, il faudrait qu'on libere avec un signal */

    if(fenetreTraces == NULL)
    {
      printf("Erreur malloc tracesUI");
      exit(EXIT_FAILURE);
    }

    fenetreTraces->widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(fenetreTraces->widget), "Gestion des traces");

    // On n'affiche pas la fenetre dans la barre des taches
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(fenetreTraces->widget), TRUE);
    // Sera toujours au dessus de la fenetre mere. Ici la fenetre principale.
    gtk_window_set_transient_for(GTK_WINDOW(fenetreTraces->widget), GTK_WINDOW(user_data));
    gtk_window_set_destroy_with_parent(GTK_WINDOW(fenetreTraces->widget), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(fenetreTraces->widget), UI_TRACE_TAILLE_X, UI_TRACE_TAILLE_Y);

    // ====== Layout : Box
    fenetreTraces->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_TRACE_ESPACEMENT);

    // ------ Widgets : Bouton et Box 'Importer'
    //fenetreTraces->boutonImporter = gtk_button_new_with_label("Importer");
    fenetreTraces->boutonImporter = gtk_button_new();
    fenetreTraces->imgImport = gtk_image_new_from_file("../Data/icones/download-64.png");
    gtk_button_set_image(GTK_BUTTON(fenetreTraces->boutonImporter), fenetreTraces->imgImport);


    // ===--- Layout : Frame
    fenetreTraces->frameTraces = gtk_frame_new("Liste des traces");
    // --- Widget : Zone de scroll
    fenetreTraces->zoneScroll = gtk_scrolled_window_new(NULL, NULL);
    // --- Widget : Box des items de la zone de scroll
    fenetreTraces->zoneScrollBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

    // ===================== Signaux =====================
    g_signal_connect(fenetreTraces->boutonImporter, "clicked", G_CALLBACK(importer), fenetreTraces);
    g_signal_connect(fenetreTraces->widget, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);

    // ==================== Packaging ====================
    // Fenetre principale <- Box principale
    gtk_container_add(GTK_CONTAINER(fenetreTraces->widget), fenetreTraces->boxPrincipale);
    // Box principale <- bouton importer + frame traces
    gtk_box_pack_start(GTK_BOX(fenetreTraces->boxPrincipale), fenetreTraces->boutonImporter, FALSE, FALSE, UI_TRACE_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(fenetreTraces->boxPrincipale), fenetreTraces->frameTraces, TRUE, TRUE, UI_TRACE_ESPACEMENT);
      // Frame traces <- zone de scroll + box
    gtk_container_add(GTK_CONTAINER(fenetreTraces->frameTraces), fenetreTraces->zoneScroll);
    gtk_container_add(GTK_CONTAINER(fenetreTraces->zoneScroll), fenetreTraces->zoneScrollBox);

    // ==================== Affichage ====================
    gtk_widget_show_all(fenetreTraces->widget);
  }
  else
  {
    gtk_window_present(GTK_WINDOW(fenetreTraces->widget));
  }

  return EXIT_SUCCESS;
}

/**
 * \fn      void importer(GtkWidget* widget, gpointer user_data)
 * \brief   Affiche une GUI pour choisir le fichier log à importer.
 *
 * \details Credits : gtk+ documentation.
 *          On donne a l'utilisateur une GUI lui permettant de naviguer dans
 *          ses differents dossiers et ici de selectionner le fichier log.
 *          Aucun test n'est effectuer pour verifier la validite du fichier.
 *          Une fois le fichier choisi, on y extrait les traces présentes et on les affiche.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  Une chaine de caractere contenant le chemin absolu du fichier.
*/
void importer(GtkWidget* widget, gpointer user_data)
{
  
  tracesUI* fenetre = (tracesUI *)user_data;
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(fenetre->widget), action,
                                        "Cancel", GTK_RESPONSE_CANCEL,
                                        "Open", GTK_RESPONSE_ACCEPT, NULL);

  res = gtk_dialog_run(GTK_DIALOG(dialog));
  if (res==GTK_RESPONSE_ACCEPT && varGlobFront.idTrajet<(NOMBRE_MAX_TRAJETS-1) )
    {
      char *filename;

      GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
      filename = gtk_file_chooser_get_filename(chooser);

      /* Creation du trajet */
      trajet* tmpTrajet = IimportTrajet(filename);
      
      /* Ajout du trajet en tant qu'item graphique */
      ajoutItemTraces(fenetre->zoneScrollBox, (char *)g_path_get_basename(filename), tmpTrajet);
      varGlobFront.idTrajet++;
      g_free(filename);
    }
  gtk_widget_destroy (dialog);
}

/**
 * \fn      void ajoutItemTraces(GtkWidget* widget, gpointer user_data)
 * \brief   Ajoute un item représentant un ensemble de trace issu d'un fichier log.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  None.
*/
void ajoutItemTraces(GtkWidget* boxScroll, const char* nomTrajet, trajet* ptrTrajet)
{
  static int id;
  tracesItem *item = (tracesItem *)malloc(sizeof(tracesItem));

  if(item == NULL)
    exit(EXIT_FAILURE);
  item->etat = 0;
  item->id = id;
  varGlobFront.trajetId[varGlobFront.idTrajet] = id;
  id++;

  // ============== Initialisation widgets ==============
  // ====== Layout : Box principale
  item->widget = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_TRACE_ESPACEMENT);
  item->details = (tdUI *)malloc(sizeof(tdUI));
  if(item->details == NULL)
  {
    printf("Erreur malloc tdUI");
    exit(EXIT_FAILURE);
  }

  item->ptrTrajet = (trajet *)malloc(sizeof(trajet));
  if(item->ptrTrajet == NULL)
  {
    printf("Erreur malloc ptrTrajet");
    exit(EXIT_FAILURE);
  }
  item->ptrTrajet = ptrTrajet;


  item->ptrCouleur = (GdkRGBA *)malloc(sizeof(GdkRGBA));
  if(item->ptrCouleur == NULL)
  {
    printf("Erreur malloc ptrCouleur");
    exit(EXIT_FAILURE);
  }

  // ===--- Layout : BoxG
  item->boxG = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_TRACE_ESPACEMENT);
  item->labelNom = gtk_label_new(nomTrajet);

  // ===--- Layout : BoxD
  item->boxD = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_TRACE_ESPACEMENT);

  // --- Widgets : Boutons
  item->boutonRoute = gtk_button_new();
  item->boutonOption = gtk_button_new();
  item->boutonVisible = gtk_button_new();
  item->boutonSupprimer = gtk_button_new();

  item->imgRoute = gtk_image_new_from_file("../Data/icones/linked-16.png");
  item->imgOption = gtk_image_new_from_file("../Data/icones/gear-16.png");
  item->imgVisible = gtk_image_new_from_file("../Data/icones/eye-16.png");
  item->imgSupprimer = gtk_image_new_from_file("../Data/icones/trash-16.png");

  gtk_button_set_image(GTK_BUTTON(item->boutonRoute), item->imgRoute);
  gtk_button_set_image(GTK_BUTTON(item->boutonOption), item->imgOption);
  gtk_button_set_image(GTK_BUTTON(item->boutonVisible), item->imgVisible);
  gtk_button_set_image(GTK_BUTTON(item->boutonSupprimer), item->imgSupprimer);

  // ===================== Signaux =====================
  g_signal_connect(item->boutonRoute, "clicked", G_CALLBACK(traceRoute), item);
  g_signal_connect(item->boutonOption, "clicked", G_CALLBACK(optionItemTraces), item);
  g_signal_connect(item->boutonVisible, "clicked", G_CALLBACK(switchVisibilite), item);
  g_signal_connect(item->boutonSupprimer, "clicked", G_CALLBACK(confirmeSupprItem), item);

  // ==================== Packaging ====================
  // Box principale <- Boxes gauche et droite
  gtk_box_pack_start(GTK_BOX(item->widget), item->boxG, TRUE, TRUE, UI_TRACE_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(item->widget), item->boxD, FALSE, FALSE, UI_TRACE_ESPACEMENT);

    // Box gauche <- Label nom
  gtk_box_pack_start(GTK_BOX(item->boxG), item->labelNom, TRUE, TRUE, UI_TRACE_ESPACEMENT);

    // Box droite <- Boutons
  gtk_box_pack_start(GTK_BOX(item->boxD), item->boutonRoute, TRUE, TRUE, UI_TRACE_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(item->boxD), item->boutonOption, TRUE, TRUE, UI_TRACE_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(item->boxD), item->boutonVisible, TRUE, TRUE, UI_TRACE_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(item->boxD), item->boutonSupprimer, TRUE, TRUE, UI_TRACE_ESPACEMENT);

  ajoutOverlays(item);
  ajoutMenuTraces(nomTrajet, item->id);

  // ==================== Affichage ====================
  gtk_widget_show_all(item->widget);
  gtk_box_pack_start(GTK_BOX(boxScroll), item->widget, FALSE, FALSE, UI_TRACE_ESPACEMENT);
}


/**
 * \fn      void traceRoute(GtkWidget* widget, gpointer user_data)
 * \brief   Relie les traces entre elles pour former la route.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  None.
*/
void traceRoute(GtkWidget* widget, gpointer user_data)
{
  static int visible = 1;
  tracesItem* item = (tracesItem *)user_data;
  if(visible)
  {
    item->ptrTrajet->visibilite = 0;    
    visible = 0;
  }
  else
  {
    item->ptrTrajet->visibilite = 1;
    visible = 1;
  }

  majCartes(item->id);
}

/**
 * \fn      void switchVisibilite(GtkWidget* widget, gpointer user_data)
 * \brief   Affiche les traces sur la carte.

 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  None.
*/
void switchVisibilite(GtkWidget* widget, gpointer user_data)
{
  static int visible = 1;
  tracesItem* item = (tracesItem *)user_data;
  if(visible)
  {
    visible = 0;
    gtk_image_set_from_file(GTK_IMAGE(item->imgVisible), "../Data/icones/eye-disabled-16.png");
    cacheCartes(item->id);
  }
  else
  {
    visible = 1;
    gtk_image_set_from_file(GTK_IMAGE(item->imgVisible), "../Data/icones/eye-16.png");
    afficheCartes(item->id);
  }
}

/**
 * \fn      void detruireFen(GtkWidget* widget, gpointer user_data)
 * \brief   Detruit la fenetre passée par user_data et libere la memoire.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  None.
*/
void detruireFen(GtkWidget* widget, gpointer user_data)
{
  confirmeTUI* fen = (confirmeTUI *) user_data;
  gtk_widget_destroy(fen->widget);
  free(user_data);
}


/**
 * \fn      void confirmeSupprItem(GtkWidget* widget, gpointer user_data)
 * \brief   Demande la confirmation pour la suppression d'un ensemble de traces.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  None.
*/
void confirmeSupprItem(GtkWidget* widget, gpointer user_data)
{
  confirmeTUI* popup = (confirmeTUI *) malloc(sizeof(confirmeTUI));

  if(popup == NULL)
  {
    perror("Erreur creation confirmeTUI");
    exit(EXIT_FAILURE);
  }

  tracesItem* itemASuppr = (tracesItem *)user_data;
  char txt[] = "Si vous supprimez cet ensemble de traces, vous ne pourrez plus l'utiliser.\n\n \t\t\t\tConfirmer pour supprimer ";

  // ============== Initialisation widgets ==============
  // ====== Fenetre principale
  popup->widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(popup->widget), GTK_WIN_POS_CENTER);
  gtk_window_set_keep_above(GTK_WINDOW(popup->widget), TRUE);
  gtk_window_set_title(GTK_WINDOW(popup->widget), "Confirmation de suppression");
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popup->widget), TRUE);
  gtk_window_set_modal(GTK_WINDOW(popup->widget), TRUE);
  gtk_window_set_destroy_with_parent(GTK_WINDOW(popup->widget), TRUE);

  // ===--- Layout : Box principale
  popup->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_TRACE_ESPACEMENT);
  // --- Widget : label du texte de confirmation
  popup->labelTxt = gtk_label_new(strcat(txt, gtk_label_get_text(GTK_LABEL(itemASuppr->labelNom))));
  // ===--- Layout : Box des boutons 'annuler' et 'confirmer'
  popup->boxBoutons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_TRACE_ESPACEMENT);
  // --- Widgets : boutons annuler et confirmer
  popup->boutonAnnuler = gtk_button_new_with_label("Annuler");
  popup->boutonConfirmer = gtk_button_new_with_label("Confirmer");

  // ===================== Signaux =====================
  g_signal_connect(popup->boutonAnnuler, "clicked", G_CALLBACK(annulerTD), popup->widget);
  g_signal_connect(popup->boutonConfirmer, "clicked", G_CALLBACK(supprimeItemTraces), user_data);
  g_signal_connect(popup->boutonConfirmer, "clicked", G_CALLBACK(detruireFen), popup);

  // ==================== Packaging ====================
  // Fenetre principale <- box principale
  gtk_container_add(GTK_CONTAINER(popup->widget), popup->boxPrincipale);
  // Box principale <- Label text + box des boutons
  gtk_box_pack_start(GTK_BOX(popup->boxPrincipale), popup->labelTxt, TRUE, TRUE, UI_TRACE_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(popup->boxPrincipale), popup->boxBoutons, TRUE, TRUE, UI_TRACE_ESPACEMENT);
    // Box des boutons <- Boutons annuler et confirmer
  gtk_box_pack_start(GTK_BOX(popup->boxBoutons), popup->boutonAnnuler, TRUE, TRUE, UI_TRACE_ESPACEMENT);
  gtk_box_pack_start(GTK_BOX(popup->boxBoutons), popup->boutonConfirmer, TRUE, TRUE, UI_TRACE_ESPACEMENT);

  // ==================== Affichage ====================
  gtk_widget_show_all(popup->widget);
}

/**
 * \fn      void supprimeItemTraces(GtkWidget* widget, gpointer user_data)
 * \brief   Supprime l'item représentant un ensemble de traces de la liste d'importation.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  None.
*/
void supprimeItemTraces(GtkWidget* widget, gpointer user_data)
{
  tracesItem *itemASuppr = (tracesItem *)user_data;

  gtk_container_remove(GTK_CONTAINER(varGlobFront.overlayCarteCher), varGlobFront.zoneDessinCher[itemASuppr->id]);
  gtk_container_remove(GTK_CONTAINER(varGlobFront.overlayCarteBourges), varGlobFront.zoneDessinBourges[itemASuppr->id]);
  gtk_container_remove(GTK_CONTAINER(varGlobFront.overlayCarteInsa), varGlobFront.zoneDessinInsa[itemASuppr->id]);
  supprimeMenuTraces(itemASuppr->id);
  free(itemASuppr->details);
  gtk_widget_destroy(itemASuppr->widget);
  free((tracesItem *)user_data);

  /* Supprimer aussi la liste de traces */
}

/**
 * \fn      void optionItemTraces(GtkWidget* widget, gpointer user_data)
 * \brief   Affiche une GUI pour modifier les options d'un ensemble de traces.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  None.
*/
void optionItemTraces(GtkWidget* widget, gpointer user_data)
{
  tracesItem* itemTD = (tracesItem*)user_data;

  if(itemTD->etat != UI_TRACE_INITIALISE)
  {
    // ============== Initialisation widgets ==============
    // ====== Validation d'ouverture
    itemTD->etat = UI_TRACE_OUVERT;
    tdUI* popupTD = itemTD->details;

    // ====== Fenetre
    popupTD->widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_keep_above(GTK_WINDOW(popupTD->widget), TRUE);
    gtk_window_set_title(GTK_WINDOW(popupTD->widget), "Option de la trace");
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popupTD->widget), TRUE);
    gtk_widget_set_can_focus(popupTD->widget, TRUE);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(popupTD->widget), TRUE);

    // ====== Layout : Box principale
    popupTD->boxPrincipale = gtk_box_new(GTK_ORIENTATION_VERTICAL, UI_TRACE_ESPACEMENT);

    // ===--- Layout : Frame couleur
    popupTD->frameCouleur = gtk_frame_new("Couleur");

       // --- Widget : bouton de modification de couleur
    popupTD->boutonModifierCouleur = gtk_color_button_new();

    // ===--- Layout : Frame du nom
    popupTD->frameNom = gtk_frame_new("Nom");

       // --- Widget : zoneEntry du nom
    GtkEntryBuffer* monBuffer;
    monBuffer = gtk_entry_buffer_new(gtk_label_get_text(GTK_LABEL(itemTD->labelNom)), -1);
    popupTD->zoneEntry = gtk_entry_new_with_buffer(monBuffer);

    // ===--- Layout : Box des boutons
    popupTD->boxBoutonsTD = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, UI_TRACE_ESPACEMENT);

    // ------ Widgets : Boutons appliquer et annuler
    popupTD->boutonAppliquer = gtk_button_new_with_label("Appliquer");
    popupTD->boutonAnnuler = gtk_button_new_with_label("Annuler");

    // ===================== Signaux =====================
    g_signal_connect(popupTD->boutonAppliquer, "clicked", G_CALLBACK(appliquerTD), user_data);
    g_signal_connect(popupTD->boutonAnnuler, "clicked", G_CALLBACK(annulerTD), popupTD->widget);
    g_signal_connect(popupTD->widget, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
    g_signal_connect(popupTD->boutonModifierCouleur, "color-set", G_CALLBACK(changeCouleur), user_data);

    // ==================== Packaging ====================
    // Fenetre principale <- Box principale
    gtk_container_add(GTK_CONTAINER(popupTD->widget), popupTD->boxPrincipale);
    // Box principale <- Frame couleur + Frame nom + Box boutons
    gtk_box_pack_start(GTK_BOX(popupTD->boxPrincipale), popupTD->frameCouleur, TRUE, TRUE, UI_TRACE_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(popupTD->boxPrincipale), popupTD->frameNom, TRUE, TRUE, UI_TRACE_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(popupTD->boxPrincipale), popupTD->boxBoutonsTD, TRUE, TRUE, UI_TRACE_ESPACEMENT);

      // Frame couleur <- Bouton modifier
    gtk_container_add(GTK_CONTAINER(popupTD->frameCouleur), popupTD->boutonModifierCouleur);
      // Frame nom <- Entry zone
    gtk_container_add(GTK_CONTAINER(popupTD->frameNom), popupTD->zoneEntry);
      // Box boutons <- Boutons annuler et appliquer
    gtk_box_pack_start(GTK_BOX(popupTD->boxBoutonsTD), popupTD->boutonAnnuler, TRUE, TRUE, UI_TRACE_ESPACEMENT);
    gtk_box_pack_start(GTK_BOX(popupTD->boxBoutonsTD), popupTD->boutonAppliquer, TRUE, TRUE, UI_TRACE_ESPACEMENT);

    // ==================== Affichage ====================
    gtk_widget_show_all(popupTD->widget);
  }
  else
  {
    gtk_entry_set_text(GTK_ENTRY(itemTD->details->zoneEntry), gtk_label_get_text(GTK_LABEL(itemTD->labelNom)));
    gtk_window_present(GTK_WINDOW(itemTD->details->widget));
  }
}

/**
 * \fn      changeCouleur(GtkWidget* widget, gpointer user_data)
 * \brief   Appliquer la modification de la couleur des traces.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  None.
*/
void changeCouleur(GtkWidget* widget, gpointer user_data)
{
  tracesItem* item = (tracesItem *)user_data;
  gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(widget), item->ptrCouleur);
  majCartes(item->id);
}

/**
 * \fn      void appliquerTD(GtkWidget* widget, gpointer user_data)
 * \brief   Applique les modifications des options d'un ensemble de traces.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  None.
*/
void appliquerTD(GtkWidget* widget, gpointer user_data)
{
  tracesItem* item = (tracesItem*)user_data;
  gtk_label_set_text(GTK_LABEL(item->labelNom), gtk_entry_get_text(GTK_ENTRY(item->details->zoneEntry)));
  renommeMenuTraces(item->id, gtk_label_get_text(GTK_LABEL(item->labelNom)));
  gtk_widget_hide(item->details->widget);
}

/**
 * \fn      void annulerTD(GtkWidget* widget, gpointer user_data)
 * \brief   Annule les modifications des options d'un ensemble de traces.
 *
 * \param   widget    Widget d'où provient le signal.
 * \param   user_data Variable passée par le signal.
 *
 * \return  None.
*/
void annulerTD(GtkWidget* widget, gpointer user_data)
{
  gtk_widget_hide(GTK_WIDGET(user_data));
}
