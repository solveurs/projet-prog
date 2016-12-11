
#include "figures.h"

int largeur=600,hauteur=300,bordure=8;

void tailledessin(GtkWidget *widget, GtkAllocation *allocation, void *data) {
  largeur=allocation->width;
  hauteur=allocation->height;
  printf("largeur = %d, hauteur = %d\n", largeur,hauteur);
}

/* Surface to store current scribbles */
 cairo_surface_t *surface = NULL;


 gboolean draw_cb (GtkWidget *widget,cairo_t   *cr, gpointer   data);

 void clear_surface (void)
{
  cairo_t *cr;

  cr = cairo_create (surface);

  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);

  /* cairo_destroy (cr); */
}

 gboolean efface(GtkWidget *widget,
		       /* GdkEventExpose *event, */
		       /* GtkAllocation *allocation, */
		       /* cairo_t *cr, */
		        gpointer data )
{

  clear_surface();
  gtk_widget_queue_draw_area(widget,bordure+1,bordure+1,largeur,hauteur);

  return TRUE;
}


/* Create a new surface of the appropriate size to store our scribbles */
 gboolean configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data)
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
 gboolean draw_cb (GtkWidget *widget, cairo_t   *cr, gpointer   data)
{
  cairo_set_source_surface (cr, surface, 0, 0);
  cairo_paint (cr);

  return FALSE;
}

/* Draw a rectangle on the surface at the given position */
 void draw_brush (GtkWidget *widget, gdouble    x, gdouble    y)
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
 gboolean button_press_event_cb (GtkWidget      *widget, GdkEventButton *event, gpointer        data)
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
 gboolean motion_notify_event_cb (GtkWidget *widget,GdkEventMotion *event, gpointer data)
{
  /* paranoia check, in case we haven't gotten a configure event */
  if (surface == NULL)
    return FALSE;

  if (event->state & GDK_BUTTON1_MASK)
    draw_brush (widget, event->x, event->y);

  /* We've handled it, stop processing */
  return TRUE;
}

 void close_window (void)
{
  if (surface)
    cairo_surface_destroy (surface);

  gtk_main_quit ();
}
