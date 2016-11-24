#include <stdlib.h>
#include <stdio.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <errno.h>

#define TAILLE 50

/* === INSTRUCTIONS ===
*
* Click gauche pour charger des traces en memoire
* Click droit pour les afficher les traces
* Click central pour afficher la route (traces reliees)
* TAILLE definit le nombre de points
*
* J'adapterai le code lorsqu'on aura les structures
* deifinitives du backend
*/

struct point
{
  // coordonnees du coin superieur gauche
  int x;
  int y;
};

// ===== Global =========
cairo_t *monImg;
struct point tab[TAILLE];
int ROUTE = 0;


// ===== Fonctions ======

void genereTrace()
{
  FILE *fp;

  if( (fp=fopen("trace.txt", "w+"))==NULL)
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

void lectureTrace()
{
  FILE *fp;

  if( (fp=fopen("trace.txt", "r"))==NULL)
  {
    perror("lecture");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i=0; i<TAILLE; i++)
  {
    fscanf(fp, "%d %d", &tab[i].x, &tab[i].y);
  }

  fclose(fp);
}

static void do_trace(cairo_t *cr)
{
  /* === Notes ===
  * La fonction est bordelique pour des raisons
  * esthetiques : j'arriche le depart et l'arrivee
  * d'une couleur differente
  * Retracer deux fois le meme trait fait un Seg Fault
  * Donc j'ai manuellement fait les 2 premieres iterations
  * du for ainsi que la derniere.
  */

  // On definit l'arriere plan avant
  cairo_set_source_surface(cr, monImg, 0, 0);
  cairo_paint(cr);

  // Epaisseur des lignes
  cairo_set_line_width(cr, 1.0);
  // Couleur de notre point de depart ici rouge
  cairo_set_source_rgb(cr, 1, 0, 0);


  // Trace des points
  int i;

  cairo_move_to(cr, tab[0].x, tab[0].y - 5);
  cairo_line_to(cr, tab[0].x, tab[0].y + 5);

  cairo_move_to(cr, tab[0].x - 5, tab[0].y);
  cairo_line_to(cr, tab[0].x + 5, tab[0].y);

  if(ROUTE)
  {
    cairo_move_to(cr, tab[1].x, tab[1].y);
    cairo_line_to(cr, tab[0].x, tab[0].y);
  }

  // Affichage du premier point
  cairo_stroke(cr);

  cairo_move_to(cr, tab[1].x, tab[1].y - 5);
  cairo_line_to(cr, tab[1].x, tab[1].y + 5);

  cairo_move_to(cr, tab[1].x - 5, tab[1].y);
  cairo_line_to(cr, tab[1].x + 5, tab[1].y);

  // Points intermediaires en magenta
  cairo_set_source_rgb(cr, 1, 0, 1);
  for(i=2; i<(TAILLE-1); i++)
  {
    if(ROUTE)
    {
      cairo_move_to(cr, tab[i].x, tab[i].y);
      cairo_line_to(cr, tab[i-1].x, tab[i-1].y);
    }

    cairo_move_to(cr, tab[i].x, tab[i].y - 5);
    cairo_line_to(cr, tab[i].x, tab[i].y + 5);

    cairo_move_to(cr, tab[i].x - 5, tab[i].y);
    cairo_line_to(cr, tab[i].x + 5, tab[i].y);
  }

  // Affichage intermediaire
  cairo_stroke(cr);

  // Couleur d'arrivee : bleue
  cairo_set_source_rgb(cr, 0, 0, 1);
  if(ROUTE)
    {
      cairo_move_to(cr, tab[TAILLE-1].x, tab[TAILLE-1].y);
      cairo_line_to(cr, tab[TAILLE-2].x, tab[TAILLE-2].y);
    }

  cairo_move_to(cr, tab[TAILLE-1].x, tab[TAILLE-1].y - 5);
  cairo_line_to(cr, tab[TAILLE-1].x, tab[TAILLE-1].y + 5);

  cairo_move_to(cr, tab[TAILLE-1].x - 5, tab[TAILLE-1].y);
  cairo_line_to(cr, tab[TAILLE-1].x + 5, tab[TAILLE-1].y);

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

    if(event->button == 2)
    {
      ROUTE = 1;

      /*
      Ordonne l'affichage des traces en memoire
      le probleme de son appel, c'est qu'il efface
      les traces precedents.

      J'ai pas enormement planche sur cette fonction,
      faudrait que je l'etudie de plus pres plus tard.

      Regarder s'il n'existe pas une fonction
      similaire mais qui n'efface pas les precedents.
      Sinon on va devoir sauvegarder en memoire le contexte
      precedent et reecrire dessus a chaque fois.

      Sinon, dans l'exemple d'origine, le programmeur utilisait
      une pile de trace, l'incrementait et puis tracait tout
      d'un coup. On peut dans le pire des cas faire ca.
      */

      gtk_widget_queue_draw(widget); 
    }

    if(event->button == 3)
    {
      ROUTE = 0;
      gtk_widget_queue_draw(widget); 
    }

    return TRUE;
}



int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  // Chargement de l'img de fond
  monImg = cairo_image_surface_create_from_png("france.png"); 

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
  gtk_window_set_title(GTK_WINDOW(window), "Traces et route");

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}