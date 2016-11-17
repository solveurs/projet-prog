#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "widgets.h"

//gcc `pkg-config --cflags gtk+-3.0` -o maintest fentest.c `pkg-config --libs gtk+-3.0` && ./maintest

//test

int main (int argc, char **argv)
  {
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
  }