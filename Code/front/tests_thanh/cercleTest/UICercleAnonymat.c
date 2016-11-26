/**
 * \file      UICercleAnonymat.c
 * \brief     Definition des cercles d'anonymat via l'UI
 * \author    Thanh.L
 * \version   0.1
 *
 * Dans ce programme, on peut definir une zone à anonymiser via la souris.
 * La fonction d'anonymisation etant a faire, ceci n'est que l'aspect
 * graphique.
 *
 * ===== INSTRUCTION =====
 * 1er Click gauche : definit le centre du cercle
 * 2e Click gauche : Apres definition du rayon grace a la souris,
 * anonymise la zone
 * Click droit : Annule la creation du cercle en cours,
 * et/ou nettoie la zone.
 *
*/

#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


// ===== Global =====
int CLICKED = 0;

struct {
  cairo_surface_t *image; 
  cairo_surface_t *copy;  
} carte;

struct
{
  int x;
  int y;
  int r;
} cercle;

// ====== Fonctions =====

/**
 * \fn      static void do_drawing(cairo_t *cr)
 * \brief   Initialise la carte et trace le cercle d'anonymat.
 *
 * \param   cr Pointeur sur un Cairo Context où on applique nos dessins.
 * \return  Void.
*/
static void do_drawing(cairo_t *cr)
{
  if(CLICKED)
  {
    // On definit le background de la surface
    cairo_set_source_surface(cr, carte.image, 0, 0);
    cairo_paint(cr); 

    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_set_line_width(cr, 2);  

    // Trace du cercle
    cairo_arc(cr, cercle.x, cercle.y, cercle.r, 0, 2 * M_PI);
    cairo_stroke(cr); 
  } 
  else // On definit l'image de base
  {
    cairo_set_source_surface(cr, carte.image, 0, 0);
    cairo_paint(cr); 
  }
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{      
  do_drawing(cr);

  return FALSE;
}

/**
 * \fn      static int rayon(int centreX, int centreY, int rayonX, int rayonY)
 * \brief   Calcul le rayon d'un cercle.
 *
 * \param   centreX Coordonnees X du centre du cercle.
 * \param   centreY Coordonnees Y du centre du cercle.
 * \param   rayonX Coordonnees X du rayon du cercle.
 * \param   rayonY Coordonnees Y du rayon du cercle.
 * \return  Retourne la longueur du rayon.
*/
static int rayon(int centreX, int centreY, int rayonX, int rayonY)
{
  double hyp;
  int AB = abs(rayonX - centreX);
  int BC = abs(rayonY - centreY);

  // Pythagore, je t'invoque !!!!
  hyp = sqrt((double)(AB*AB + BC*BC));

  return (int)hyp;
}

/**
 * \fn      static gboolean mouse_moved(GtkWidget *widget,GdkEvent *event, gpointer user_data)
 * \brief   Detecte le mouvement de la souris pour la previsualisation du cercle.
 *
 * \param   widget      Instance a laquelle est rattachee le signal.
 * \param   event       Evenement GdkEvent.
 * \param   user_data   Donnees transferee par le signal.
 * \return  gboolean.
*/
static gboolean mouse_moved(GtkWidget *widget,GdkEvent *event, gpointer user_data)
{
  if(event->type==GDK_MOTION_NOTIFY && CLICKED) 
  {
    // On recupere la position du curseur
    GdkEventMotion* e=(GdkEventMotion*)event;
    cercle.r = rayon(cercle.x, cercle.y, (guint)e->x, (guint)e->y);

    // Creation du Cairo Context
    cairo_t *crtmp;
    // On cree une copie du background, sur laquelle on dessine le cercle
    crtmp = cairo_create(carte.copy);
    do_drawing(crtmp);
    // On est oblige de vider la pile de dessin a chaque appel
    // Si tu ne comprends pas, met le en commentaire, tu comprendras
    // ... c'est plutot drole
    gtk_widget_queue_draw(widget); 
  }
}

/**
 * \fn      static gboolean clicked(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
 * \brief   Detecte le click de la souris et agit en consequence.
 *
 * \param   widget      Instance a laquelle est rattachee le signal.
 * \param   event       Evenement lie au click de la souris.
 * \param   user_data   Donnees transferee par le signal.
 * \return  gboolean.
*/
static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{
    if(event->button == 1)  // Premier click gauche.
    {
      if(CLICKED)           // Normalement au deuxieme, on anonymise.
      {
        CLICKED = 0;         
      }
      else                  // Au premier click, on definit le cercle.
      {
        cercle.x = event->x;
        cercle.y = event->y;
        CLICKED = 1;
      }
    }

    if(event->button == 3) // Click droit
    {
      CLICKED = 0;
      gtk_widget_queue_draw(widget);  // Vidage de la pile de dessin.
    }

    return TRUE;
}

int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;
  
  carte.image = cairo_image_surface_create_from_png("../france.png");
  carte.copy = cairo_image_surface_create_from_png("../france.png");

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);

  g_signal_connect(G_OBJECT(darea), "draw", 
      G_CALLBACK(on_draw_event), NULL); 
  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (G_OBJECT(window), "motion-notify-event",
      G_CALLBACK (mouse_moved), NULL);
  g_signal_connect(window, "button-press-event", 
    G_CALLBACK(clicked), NULL);

  // Je comprends pas trop, mais il est necessaire d'initialiser
  // l'evenement via le MASK, malgre le g_signal_connect()
  gtk_widget_set_events(window, GDK_POINTER_MOTION_MASK);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 220); 
  gtk_window_set_title(GTK_WINDOW(window), "Cercles d'anonymat");

  gtk_widget_show_all(window);

  gtk_main();

  cairo_surface_destroy(carte.image);
  cairo_surface_destroy(carte.copy);

  return 0;
}


