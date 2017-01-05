/**
 * \file      fctnCairo.c
 * \brief     Fichier main de la GUI de gestion des traces.
 * \author    Thanh.L
 *
 * Le fichier contient toutes les fonctions utilisees pour le dessin des traces.
 * ====================
 *       TODO
 * ====================
 * + Gerer la liberation de la memoire
 * + Adapter la fonction d'anonymisation a la structure globale
 * + Adapter la fonction d'aggregation avec les returns des fonctions du back.
 * ====================
 *        MaJ
 * ====================
 * Creation du fichier.
 *
*/

#include "../headers/fctnCairo.h"
#include "../headers/globalFront.h"

void faire_tracesCher(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
  tracesItem* ptrTmp = (tracesItem *)user_data;
  faire_tracer(cr, 0, ptrTmp->ptrTrajet);
}

void faire_tracesBourges(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
  tracesItem* ptrTmp = (tracesItem *)user_data;
  faire_tracer(cr, 1, ptrTmp->ptrTrajet);
}

void faire_tracesInsa(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
  tracesItem* ptrTmp = (tracesItem *)user_data;
  faire_tracer(cr, 2, ptrTmp->ptrTrajet);
}

void faire_tracer(cairo_t *cr, int carte, trajet *cible)
{
  double x;
  double y;
  // Epaisseur des lignes
  cairo_set_line_width(cr, 1.0);
  // Couleur de notre point de depart ici rouge
  cairo_set_source_rgb(cr, 1, 0, 0);

  // Tracer des points
  trace* ptr;

  // Traces en rouge
  cairo_set_source_rgb(cr, 1, 0, 0);
  for(ptr=cible->premier; ptr!=cible->dernier; ptr=ptr->suiv)
  {
    if(ptr->visibilite==1 /* && condition date */)
    {
      x = echelle(ptr->coord.x, carte, 1);
      y = echelle(ptr->coord.y, carte, 0);

      // Dessin d'un petit "+"
      cairo_move_to(cr, x, y - TAILLE_TRACE);
      cairo_line_to(cr, x, y + TAILLE_TRACE);

      cairo_move_to(cr, x - TAILLE_TRACE, y);
      cairo_line_to(cr, x + TAILLE_TRACE, y);

      if(cible->visibilite) //si le trajet est visible
      {
        cairo_move_to(cr, x, y);
        x = echelle(ptr->suiv->coord.x, carte, 1);
        y = echelle(ptr->suiv->coord.y, carte, 0);
        cairo_line_to(cr, x, y);
      }
    }
  }
  if(ptr->visibilite==1 /* && condition date */)
  {
    x = echelle(cible->dernier->coord.x, carte, 1);
    y = echelle(cible->dernier->coord.y, carte, 0);
    cairo_move_to(cr, x, y - TAILLE_TRACE);
    cairo_line_to(cr, x, y + TAILLE_TRACE);

    cairo_move_to(cr, x - TAILLE_TRACE, y);
    cairo_line_to(cr, x + TAILLE_TRACE, y);
  }

  cairo_stroke_preserve(cr);
}

void faire_aggregation(cairo_t *cr, cercle *cercle)
{
  //
}

double echelle(double valeur, int carte, int longitude)
{
  switch(carte)
  {
    double conversion;
    case 0: // Cher
      if(longitude)
      {
        conversion = ((valeur - 1.726227) * TAILLE_X_CHER / 1.389770);
        return conversion;
      }
      conversion = (-1.0 * (valeur - 47.988083) * TAILLE_Y_CHER / 1.793991);
      return conversion;

    case 1: // Bourges
      if(longitude)
      {
        conversion = ((valeur - 2.313738) * TAILLE_X_BOURGES / 0.158872);
        return conversion;
      }
      conversion = (-1.0 * (valeur - 47.113540) * TAILLE_Y_BOURGES / 0.063064);
      return conversion;

    default: // Insa
      if(longitude)
      {
        conversion = ((valeur - 2.392981) * TAILLE_X_INSA / 0.039783);
        return conversion;
      }
      conversion = (-1.0 * (valeur - 47.088723) * TAILLE_Y_INSA / 0.015766);
      return conversion;
  }
}

void majCartes(int idCarte)
{
  gtk_widget_queue_draw(globFront.zoneDessinCher[idCarte]);
  gtk_widget_queue_draw(globFront.zoneDessinBourges[idCarte]);
  gtk_widget_queue_draw(globFront.zoneDessinInsa[idCarte]);
}

void cacheCartes(int idCarte)
{
  gtk_widget_hide(globFront.zoneDessinCher[idCarte]);
  gtk_widget_hide(globFront.zoneDessinBourges[idCarte]);
  gtk_widget_hide(globFront.zoneDessinInsa[idCarte]);
}

void afficheCartes(int idCarte)
{
  gtk_widget_show(globFront.zoneDessinCher[idCarte]);
  gtk_widget_show(globFront.zoneDessinBourges[idCarte]);
  gtk_widget_show(globFront.zoneDessinInsa[idCarte]);
}
