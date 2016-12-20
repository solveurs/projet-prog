#include "activate.h"
#include "ui.h"

void activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget* fenetre;

	fenetre = gtk_application_window_new(app);
	gtk_window_set_title (GTK_WINDOW(fenetre), "Geoloc v0.1a");
	gtk_window_set_default_size (GTK_WINDOW(fenetre), 800, 600);

	GtkWidget *boxUI;
	boxUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	ajoutWidget(fenetre, boxUI);

	//Menu bar + Menu + Menu Item
	// POSITION : TOP
	GtkWidget *boxMenu, *menuBar, *ssMenu1, *ssMenu2;
	GtkWidget *ssMenuItem1, *ssMenuItem2, *ssMenuItem3, *ssMenuItem4;

	boxMenu = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	menuBar = gtk_menu_bar_new();
	ssMenu1 = gtk_menu_new();
	ssMenu2 = gtk_menu_new();

	ssMenuItem1 = gtk_menu_item_new_with_label("Fichier");
	ssMenuItem2 = gtk_menu_item_new_with_label("Reste a faire");
	ssMenuItem3 = gtk_menu_item_new_with_label("A faire");
	ssMenuItem4 = gtk_menu_item_new_with_label("A faire");

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(ssMenuItem1), ssMenu1);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(ssMenuItem2), ssMenu2);

	gtk_menu_shell_append(GTK_MENU_SHELL(ssMenu1), ssMenuItem3);
	gtk_menu_shell_append(GTK_MENU_SHELL(ssMenu2), ssMenuItem4);

	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), ssMenuItem1);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), ssMenuItem2);

	gtk_box_pack_start(GTK_BOX(boxMenu), menuBar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(boxUI), boxMenu, FALSE, FALSE, 0);

	// Toolbar fenetres flottantes
	GtkWidget *boxFloat, *b1Box, *b2Box;
	GtkWidget *bouton1, *bouton2;

	boxFloat = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	b1Box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	b2Box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

	bouton1 = gtk_button_new_with_label("uiTraces");
	bouton2 = gtk_button_new_with_label("A faire");

	ajoutWidget(b1Box, bouton1);
	ajoutWidget(b2Box, bouton2);
	ajoutWidget(boxFloat, b1Box);
	ajoutWidget(boxFloat, b2Box);

	gtk_box_pack_start(GTK_BOX(boxFloat), menuBar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(boxUI), boxFloat, FALSE, FALSE, 0);

	// Carte
	GtkWidget* scrollCarte;
	scrollCarte = gtk_scrolled_window_new(NULL, NULL);

	GtkWidget* image;
	image = gtk_image_new_from_file("../france.png");
	ajoutWidget(scrollCarte, image);

	gtk_box_pack_start(GTK_BOX(boxUI), scrollCarte, TRUE, TRUE, 0);

	// Taskbar pour les fenetres flottantes
	GtkWidget *boxTask;
	GtkWidget *labelWIP;
	GtkWidget *l1, *l2;

	boxTask = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	l1 = gtk_label_new("premiere fenetre     |     ");
	l2 = gtk_label_new("deuxieme fenetre     |     ...");
	ajoutWidget(boxTask, l1);
	ajoutWidget(boxTask, l2);

	gtk_box_pack_start(GTK_BOX(boxUI), boxTask, FALSE, FALSE, 0);

	// ====== Signaux
	g_signal_connect(bouton1, "clicked", G_CALLBACK(uiTraces), fenetre);

	//Packaging
	gtk_widget_show_all(fenetre);
}