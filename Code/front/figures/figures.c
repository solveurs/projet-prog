#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include "figures.h"




static gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
  guint width, height;
  GdkRGBA color;

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);
  cairo_arc (cr,
    width / 2.0, height / 2.0,
    MIN (width, height) / 2.0,
    0, 2 * G_PI);

    gtk_style_context_get_color (gtk_widget_get_style_context (widget),
    0,
    &color);
    gdk_cairo_set_source_rgba (cr, &color);

    cairo_fill (cr);

    return FALSE;
}


static gboolean clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
    printf("clicked at %f %f\n", event->x, event->y);
    if (event->button == 1) {
      glob.coordx[glob.count] = event->x;
      glob.coordy[glob.count++] = event->y;
    }
    if (event->button == 3) {
      gtk_widget_queue_draw(widget);
    }

    return TRUE;


}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,gpointer user_data)
{
    do_drawing(cr);
    return FALSE;
}

static void do_drawing(cairo_t *cr)
{
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, 0.5);

  int i, j;
  for (i = 0; i <= glob.count - 1; i++ ) {
      for (j = 0; j <= glob.count - 1; j++ ) {
          cairo_move_to(cr, glob.coordx[i], glob.coordy[i]);
          cairo_line_to(cr, glob.coordx[j], glob.coordy[j]);
      }
  }

  glob.count = 0;
  cairo_stroke(cr);
}
