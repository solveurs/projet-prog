#include "figures.h"

int main (int   argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *da; //Drawing area
  GtkWidget *grille;
  GtkWidget *bouton1,*bouton2;


  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Dessin à la souris avec GTK/cairo");

  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

  g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);

  gtk_container_set_border_width (GTK_CONTAINER (window), 8);

  grille=gtk_grid_new();

  gtk_container_add(GTK_CONTAINER(window),grille); /*ajout*/



  bouton1=gtk_button_new_with_label("Quitter"); /* ajout */
  g_signal_connect(bouton1,"clicked",G_CALLBACK(close_window),NULL); /* ajout */

  bouton2=gtk_button_new_with_label("Effacer"); /* ajout */
  g_signal_connect(bouton2,"clicked",G_CALLBACK(efface),NULL); /* ajout */

  gtk_grid_attach(GTK_GRID(grille),bouton2,0,1,1,2); /* ajout */
  gtk_grid_attach(GTK_GRID(grille),bouton1,1,1,2,2); /* ajout */


  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);

  gtk_grid_attach(GTK_GRID(grille),frame,0,0,2,1);


  da = gtk_drawing_area_new ();
  /* set a minimum size */
  //gtk_widget_set_size_request (da, bordure+largeur,bordure+hauteur);
  gtk_widget_set_hexpand (da, TRUE);
gtk_widget_set_vexpand (da, TRUE);
  gtk_container_add (GTK_CONTAINER (frame), da);


  /* Signals used to handle the backing surface */
  g_signal_connect (da, "draw",
		    G_CALLBACK (draw_cb), NULL);
  g_signal_connect (da,"configure-event",
		    G_CALLBACK (configure_event_cb), NULL);
  g_signal_connect(da, "size-allocate", G_CALLBACK(tailledessin), NULL);


  /* Event signals */
  g_signal_connect (da, "motion-notify-event",
		    G_CALLBACK (motion_notify_event_cb), NULL);
  g_signal_connect (da, "button-press-event",
		    G_CALLBACK (button_press_event_cb), NULL);

  /* Ask to receive events the drawing area doesn't normally
   * subscribe to. In particular, we need to ask for the
   * button press and motion notify events that want to handle.
   */
  gtk_widget_set_events (da, gtk_widget_get_events (da)
			 | GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
