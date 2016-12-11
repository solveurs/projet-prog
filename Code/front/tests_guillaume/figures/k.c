/* compiler avec gcc dessinsouris.c -o dessinsouris $(pkg-config --cflags --libs gtk+-3.0)
 */

#include <gtk/gtk.h>

int largeur=600,hauteur=300,bordure=8;


void tailledessin(GtkWidget *widget, GtkAllocation *allocation, void *data) {
  largeur=allocation->width;
  hauteur=allocation->height;
  printf("largeur = %d, hauteur = %d\n", largeur,hauteur);
}

/* Surface to store current scribbles */
static cairo_surface_t *surface = NULL;


static gboolean draw_cb (GtkWidget *widget, cairo_t   *cr, gpointer   data);

static void clear_surface (void)
{
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  /* cairo_destroy (cr); */
}

static gboolean efface(GtkWidget *widget, gpointer data )
{

  clear_surface();
  gtk_widget_queue_draw_area(widget,bordure+1,bordure+1,largeur,hauteur);

  return TRUE;
}


/* Create a new surface of the appropriate size to store our scribbles */
static gboolean configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data)
{
  printf("refresh !\n");
  if (surface)
    cairo_surface_destroy (surface);

  surface = gdk_window_create_similar_surface (gtk_widget_get_window (widget),
					       CAIRO_CONTENT_COLOR,
					       gtk_widget_get_allocated_width (widget),
					       gtk_widget_get_allocated_height (widget));

  /* Initialize the surface to white */
  /* clear_surface (); */

  /* We've handled the configure event, no need for further processing. */
  return TRUE;
}

/* Redraw the screen from the surface. Note that the ::draw
 * signal receives a ready-to-be-used cairo_t that is already
 * clipped to only draw the exposed areas of the widget
 */
static gboolean draw_cb (GtkWidget *widget, cairo_t *cr, gpointer data)
{
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);

  return FALSE;
}

/* Draw a rectangle on the surface at the given position */
static void draw_brush(GtkWidget *widget, gdouble    x,gdouble    y)
{
  cairo_t *cr;

  /* Paint to the surface, where we store our state */
  cr = cairo_create (surface);

  cairo_rectangle (cr, x - 3, y - 3, 6, 6);
  cairo_fill (cr);

  cairo_destroy (cr);

  /* Now invalidate the affected region of the drawing area. */
  gtk_widget_queue_draw_area (widget, x - 3, y - 3, 6, 6);
}

/* Handle button press events by either drawing a rectangle
 * or clearing the surface, depending on which button was pressed.
 * The ::button-press signal handler receives a GdkEventButton
 * struct which contains this information.
 */
static gboolean button_press_event_cb (GtkWidget *widget, GdkEventButton *event, gpointer data)
{
  /* paranoia check, in case we haven't gotten a configure event */
  if (surface == NULL)
    return FALSE;

  if (event->button == GDK_BUTTON_PRIMARY)
    {
      draw_brush (widget, event->x, event->y);
    }
  else if (event->button == GDK_BUTTON_SECONDARY)
    {
      clear_surface ();
      gtk_widget_queue_draw (widget);
    }

  /* We've handled the event, stop processing */
  return TRUE;
}

/* Handle motion events by continuing to draw if button 1 is
 * still held down. The ::motion-notify signal handler receives
 * a GdkEventMotion struct which contains this information.
 */
static gboolean motion_notify_event_cb (GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
  /* paranoia check, in case we haven't gotten a configure event */
  if (surface == NULL)
    return FALSE;

  if (event->state & GDK_BUTTON1_MASK)
    draw_brush (widget, event->x, event->y);

  /* We've handled it, stop processing */
  return TRUE;
}

static void close_window (void)
{
  if (surface)
    cairo_surface_destroy (surface);

  gtk_main_quit ();
}





/* MAIN*/



int main (int   argc, char *argv[])
{

  GtkWidget *window;
  GtkWidget *frame;
  GtkWidget *da;
  GtkWidget *grille;
  GtkWidget *bouton1,*bouton2;


  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Dessin à la souris avec GTK/cairo");

  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

  g_signal_connect (window, "destroy", G_CALLBACK (close_window), NULL);

  gtk_container_set_border_width (GTK_CONTAINER (window), 8);

  grille=gtk_grid_new();

  gtk_container_add(GTK_CONTAINER(window),grille);



  bouton1=gtk_button_new_with_label("Quitter");
  g_signal_connect(bouton1,"clicked",G_CALLBACK(close_window),NULL);

  bouton2=gtk_button_new_with_label("Effacer");
  g_signal_connect(bouton2,"clicked",G_CALLBACK(efface),NULL);

  gtk_grid_attach(GTK_GRID(grille),bouton2,0,1,1,2);
  gtk_grid_attach(GTK_GRID(grille),bouton1,1,1,2,2);


  frame = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);

  gtk_grid_attach(GTK_GRID(grille),frame,0,0,2,1);


  da = gtk_drawing_area_new ();
  /* set a minimum size */
  gtk_widget_set_size_request (da, bordure+largeur,bordure+hauteur);
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
