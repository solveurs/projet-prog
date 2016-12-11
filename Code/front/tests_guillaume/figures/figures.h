
#pragma once

#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>




void tailledessin(GtkWidget *widget, GtkAllocation *allocation, void *data);

gboolean draw_cb (GtkWidget *widget,cairo_t   *cr, gpointer   data);

void clear_surface (void);

gboolean efface(GtkWidget *widget,gpointer data);


gboolean configure_event_cb (GtkWidget *widget, GdkEventConfigure *event, gpointer data);

void draw_brush (GtkWidget *widget, gdouble x, gdouble y);

gboolean button_press_event_cb (GtkWidget *widget, GdkEventButton *event, gpointer data);

gboolean motion_notify_event_cb (GtkWidget *widget,GdkEventMotion *event, gpointer data);

void close_window (void);
