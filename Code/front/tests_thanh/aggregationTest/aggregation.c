/**
 * \file      aggregation.c
 * \brief     Programme de tests.
 * \author    Thanh.L
 * \version   0.1
 *
 * Programme de test l'aggregation des traces
 *
 *
 * === INSTRUCTIONS ===
 * Click gauche pour charger des traces en memoire pseudo-aleatoirement
 * Click droit pour afficher les traces
 * Click molette pour afficher avec une aggregation fixe definie par (XC, YC, R)
 * TAILLE definit le nombre de points
 *
 * J'adapterai le code lorsqu'on fera le main front
*/


#include <stdlib.h>
#include <stdio.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <errno.h>
#include <math.h>

#define TAILLE 500
#define XC 500      // Coordonnee X de notre aggregation
#define YC 500      // Coordonnee Y de notre aggregation
#define R 50        // Rayon de l'aggregation


struct point
{
  // coordonnees du coin superieur gauche
  int x;
  int y;
  int temps;
  int visible;
};

// ===== Global =========
cairo_t *monImg;
struct point tab[TAILLE];
int ROUTE = 0;
int aggregation = 0;


// ===== Fonctions ======

/**
 * \fn      void genereTrace()
 * \brief   Genere pseudo-aleatoirement une trace dans "trace.txt".
 *
 * \return  Si erreur, modifie errno en consequence.
*/
void genereTrace()
{ 
  FILE *fp;

  if( (fp=fopen("trace.txt", "w+"))==NULL )
  {
    perror("creation");
    exit(EXIT_FAILURE);
  }

  int i, aleaX, aleaY;
  for(i=0; i<TAILLE; i++)
  {
    aleaX = rand() % (999 + 1 - 1) + 1;
    aleaY = rand() % (948 + 1 - 1) + 1;
    fprintf(fp, "%d %d\n", aleaX, aleaY);
  }
  fclose(fp);
}


/**
 * \fn      void lectureTrace()
 * \brief   Lis les coordonnees d'une trace situee dans "trace.txt".
 *
 * \return  Si erreur, modifie errno en consequence.
*/
void lectureTrace()
{
  FILE *fp;

  if( (fp=fopen("trace.txt", "r"))==NULL )
  {
    perror("lecture");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i=0; i<TAILLE; i++)
  {
    fscanf(fp, "%d %d", &tab[i].x, &tab[i].y);
    tab[i].visible = 1;
  }

  fclose(fp);
}



/**
 * \fn      static int cmp_cercle(int xm, int ym, int xc, int yc)
 * \brief   Compare si le point M(xm, ym) appartient au cercle C(xc, yc, R)
 *
 * \param   xm    Coordonnee X de M(xm, ym)
 * \param   ym    Coordonnee Y de M(xm, ym)
 * \param   xm    Coordonnee X de C(xc, yc, R)
 * \param   ym    Coordonnee Y de C(xc, yc, R)
*/
static int cmp_cercle(int xm, int ym, int xc, int yc)
{
  int X, Y;
  X = (xm - xc) * (xm - xc);
  Y = (ym - yc) * (ym - yc);
  if ( (X+Y) <= R*R )
    return 1;

  return 0;
}


/**
 * \fn      static void do_trace(cairo_t *cr)
 * \brief   Rend invisibles les points dans la zone d'aggregation
 *
 * \param   xc    Coordonnee X de C(xc, yc, R)
 * \param   yc    Coordonnee Y de C(xc, yc, R)
*/
static void do_aggregation(int xc, int yc)
{
  int i;

  for(i=0; i<TAILLE; i++)
  {
    if(cmp_cercle(tab[i].x, tab[i].y, XC, YC))
    {
      tab[i].visible = 0;
    }
  }
}


/**
 * \fn      static void do_trace(cairo_t *cr)
 * \brief   Effectue l'affichage des traces, et celle de la route si demandee.
 *
 * \param   cr Contexte Cairo.
*/
static void do_trace(cairo_t *cr)
{
  /* === Notes ===
  * Trace toutes les traces situees dans un tableau de traces (type point ici)
  * Verifie a la fin si on doit tracer les aggregations
  * Trace un cercle puis le rempli pour former l'aggregation
  */

  // On definit l'arriere plan
  cairo_set_source_surface(cr, monImg, 0, 0);
  cairo_paint(cr);

  // Epaisseur des lignes
  cairo_set_line_width(cr, 1.0);
  // Couleur de notre point de depart ici bleu
  cairo_set_source_rgb(cr, 0, 0, 1);

  // Aggregation
  if(aggregation)
  {
    do_aggregation(XC, YC);
    cairo_move_to(cr, XC, YC);
    cairo_arc(cr, XC, XC, R, 0, 2 * M_PI);
    //cairo_fill(cr);
    cairo_stroke(cr); 
  }

  // Trace des points
  int i;

  cairo_set_source_rgb(cr, 1, 0, 1);
  for(i=0; i<TAILLE; i++)
  {
    if(tab[i].visible)
    {
      cairo_move_to(cr, tab[i].x, tab[i].y - 5);
      cairo_line_to(cr, tab[i].x, tab[i].y + 5);

      cairo_move_to(cr, tab[i].x - 5, tab[i].y);
      cairo_line_to(cr, tab[i].x + 5, tab[i].y);
    }
  }

  // Affichage dernier point
  cairo_stroke(cr); 
}



static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{
  // Sur le signal, on utilise la fonction do_trace
  do_trace(cr);

  return FALSE;
}

static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{
    if(event->button == 1) // Click gauche
    {
      // Creation, lecture de traces aleatoires
      genereTrace();
      lectureTrace();
    }

    if(event->button == 2) // Click molette
    {
      aggregation = 1;
      gtk_widget_queue_draw(widget);        
    }

    if(event->button == 3) // Click droit
    { 
      aggregation = 0;
      // on pourrait re-rendre visible
      gtk_widget_queue_draw(widget); 
    }

    return TRUE;
}



int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  // Chargement de l'img de fond
  monImg = cairo_image_surface_create_from_png("../france.png"); 

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  // Zone de dessin
  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), darea);
 
  gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

  g_signal_connect(G_OBJECT(darea), "draw", 
      G_CALLBACK(on_draw_event), NULL); 
  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);  
    
  g_signal_connect(window, "button-press-event", 
      G_CALLBACK(clicked), NULL);
 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); 
  gtk_window_set_title(GTK_WINDOW(window), "Aggregation fixe");

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}