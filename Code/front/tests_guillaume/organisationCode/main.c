#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

// Definition de la structure de la fenetre
typedef struct s_Window
{
  GtkWidget *widget;
  GtkWidget *box;
  GtkWidget *barreMenu;
  GtkWidget *label;
  GtkWidget *entry;
  GtkWidget *button;
} t_Window;

gboolean on_click_button (GtkWidget *button, GdkEventButton *event, gpointer data)
{
  t_Window *my_w = (t_Window*) data;
  const gchar *buffer;

  // On récupère le texte contenu dans la GtkEntry
  buffer = gtk_entry_get_text(GTK_ENTRY(my_w->entry));

  // Puis on met ce texte dans le label
  gtk_label_set_text(GTK_LABEL(my_w->label), buffer);

  // Et pour finir, on vide la GtkEntry
  gtk_entry_set_text(GTK_ENTRY(my_w->entry), "");

  // On redonne la main à GTK
  return FALSE;
}

int main (int argc, char **argv)
{
  t_Window *my_window = (t_Window*) malloc (sizeof (t_Window));
  if (my_window == NULL)
    exit(EXIT_FAILURE);

  // On initialise GTK
  gtk_init(&argc, &argv);

  // On initialise les Widgets
  my_window->widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  my_window->box    = gtk_hbox_new( TRUE, 0 );
  my_window->button = gtk_button_new_with_label("C'est un Boutton !");
  my_window->label  = gtk_label_new("C'est un Label !");
  my_window->entry  = gtk_entry_new();

  // Tout d'abord, on met la GtkHBox dans la GtkWindow
  gtk_container_add(GTK_CONTAINER(my_window->widget), my_window->box);

  // Puis on met les Widgets dans la GtkHBox
  gtk_box_pack_start (GTK_BOX(my_window->box), my_window->entry, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX(my_window->box), my_window->button, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX(my_window->box), my_window->label, TRUE, TRUE, 0);

  // On connecte le bouton à l'évenement « clicked »
  g_signal_connect(my_window->button, "button-press-event", (GCallback)on_click_button, my_window);

  // On demande enfin à GTK de montrer notre Window et ce qu'elle contient :
  gtk_widget_show_all(my_window->widget);

  // Puis on entre dans la boucle GTK qui garde la fenêtre ouverte
  gtk_main();

  return 0;
}
