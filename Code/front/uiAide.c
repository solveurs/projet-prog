#include "../headers/front.h"

int uiAide(GtkWidget* widget, gpointer user_data)
{
	// Variable static pour eviter de reconstruire la fenetre
	static int etat = 0;
	if(!etat)
	{
		etat = 1;
		PageInfo page[NB_PAGE] =
		{
			{NULL, -1,"Introduction", GTK_ASSISTANT_PAGE_INTRO},
			{NULL, -1, "Importation trace", GTK_ASSISTANT_PAGE_CONTENT},
			{NULL, -1, "Animation", GTK_ASSISTANT_PAGE_CONTENT},
			{NULL, -1, "Anonymisation", GTK_ASSISTANT_PAGE_CONTENT},
			{NULL, -1, "Cartes", GTK_ASSISTANT_PAGE_CONTENT},
			{NULL, -1, "Suggestion point d'interêt", GTK_ASSISTANT_PAGE_CONTENT},
			{NULL, -1, "Affichage points d'interêts", GTK_ASSISTANT_PAGE_CONTENT},
		};
		page[0].widget = gtk_label_new ("Test1");
		page[1].widget = gtk_label_new ("Test2");
		page[2].widget = gtk_label_new ("Test3");
		page[3].widget = gtk_label_new ("Test4");
		page[4].widget = gtk_label_new ("Test5");
		page[5].widget = gtk_label_new ("Test6");
		page[7].widget = gtk_label_new ("Test7");
		
		GtkWidget * UIassistant = gtk_assistant_new();
		gtk_window_set_title (GTK_WINDOW (UIassistant), "Aides au logiciel Geoloc");
		g_signal_connect (G_OBJECT (UIassistant), "destroy",
						  G_CALLBACK (gtk_main_quit), NULL);
		
		int i;
		for (i = 0; i < NB_PAGE; i++)
		{
		
			page[i].id = gtk_assistant_append_page(GTK_ASSISTANT(UIassistant),
													page[i].widget);
			gtk_assistant_set_page_title(GTK_ASSISTANT (UIassistant),
										  page[i].widget, page[i].title);
			gtk_assistant_set_page_type(GTK_ASSISTANT (UIassistant),
										 page[i].widget, page[i].type);
			

		}
		
	}
	
	return EXIT_SUCCESS;
}
