
#pragma once

#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>


struct {
  int count;
  double coordx[100];
  double coordy[100];
} glob;



static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,gpointer user_data);

static void do_drawing(cairo_t *cr);

static gboolean clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data);

static gboolean draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data);
