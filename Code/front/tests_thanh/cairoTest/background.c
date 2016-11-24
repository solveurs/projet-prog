#include <cairo.h>
#include <gtk/gtk.h>

static void do_drawing(cairo_t *, GtkWidget *widget);

struct 
{
  // coordonnees du coin superieur gauche
  double x;
  double y;
} rectangle;

cairo_t *monImg;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{
  // Sur le signal, on utilise la fonction do_drawing
  do_drawing(cr, widget);

  return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget)
{
  // On definit l'arriere plan avant
  cairo_set_source_surface(cr, monImg, 0, 0);
  cairo_paint(cr);

  // Couleur de notre rectangle ici blanc
  cairo_set_source_rgb(cr, 255, 255, 255);


  cairo_rectangle(cr, rectangle.y, rectangle.x, 100, 100);
  // 10, 10 == longueur, largeur
  cairo_stroke_preserve(cr);
  cairo_fill(cr);
  cairo_stroke(cr);   
}

static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{
    if(event->button == 1) // lick gauche
    {
      // Stockage des infos issues du click
      rectangle.y = event->x;
      rectangle.x = event->y;
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

    return TRUE;
}


int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  monImg = cairo_image_surface_create_from_png("europa.png"); 

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

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
  gtk_window_set_title(GTK_WINDOW(window), "Lines");

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}