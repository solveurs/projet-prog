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
#include "../headers/front.h"
/*#include "../headers/fctnCairo.h"
 #include "../headers/globalFront.h"*/

void faire_tracesCher(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	tracesItem* ptrItem = (tracesItem *)user_data;
	//printf("\nSignal Cher provenant de : %d", ptrItem->id);
	faire_tracer(cr, 0, ptrItem->ptrTrajet, ptrItem->ptrCouleur);
}

void faire_tracesBourges(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	tracesItem* ptrItem = (tracesItem *)user_data;
	//printf("\nSignal Bourges provenant de : %d", ptrItem->id);
	faire_tracer(cr, 1, ptrItem->ptrTrajet, ptrItem->ptrCouleur);
}

void faire_tracesInsa(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	tracesItem* ptrItem = (tracesItem *)user_data;
	//printf("\nSignal Insa provenant de : %d", ptrItem->id);
	faire_tracer(cr, 2, ptrItem->ptrTrajet, ptrItem->ptrCouleur);
}

void faire_tracer(cairo_t *cr, int carte, trajet *cible, GdkRGBA* couleur)
{
	int x;
	int y;
	// Epaisseur des lignes
	cairo_set_line_width(cr, 1.0);
	// Traces en bleu
	cairo_set_source_rgb(cr, couleur->red, couleur->green, couleur->blue);
	
	// Tracer des points
	trace* ptr;
	for(ptr=cible->premier; ptr!=cible->dernier; ptr=ptr->suiv)
	{
		if(ptr->visibilite==1 /* && condition date */)
		{
			// Inversion longitude et latitude
			x = (int)echelle(ptr->coord.y, carte, 1);
			y = (int)echelle(ptr->coord.x, carte, 0);
			//printf("%lf,%lf\n",ptr->coord.y,ptr->coord.x);
			
			
			// Dessin d'un petit "+"
			cairo_move_to(cr, x, y - TAILLE_TRACE);
			cairo_line_to(cr, x, y + TAILLE_TRACE);
			
			cairo_move_to(cr, x - TAILLE_TRACE, y);
			cairo_line_to(cr, x + TAILLE_TRACE, y);
			
			if(cible->visibilite) //si le trajet est visible
			{
				cairo_move_to(cr, x, y);
				x = (int)echelle(ptr->suiv->coord.y, carte, 1);
				y = (int)echelle(ptr->suiv->coord.x, carte, 0);
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
	double conversion = 0.0;
	switch(carte)
	{
		
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
	gtk_widget_queue_draw(varGlobFront.zoneDessinCher[idCarte]);
	gtk_widget_queue_draw(varGlobFront.zoneDessinBourges[idCarte]);
	gtk_widget_queue_draw(varGlobFront.zoneDessinInsa[idCarte]);
}

void cacheCartes(int idCarte)
{
	gtk_widget_hide(varGlobFront.zoneDessinCher[idCarte]);
	gtk_widget_hide(varGlobFront.zoneDessinBourges[idCarte]);
	gtk_widget_hide(varGlobFront.zoneDessinInsa[idCarte]);
}

void afficheCartes(int idCarte)
{
	gtk_widget_show(varGlobFront.zoneDessinCher[idCarte]);
	gtk_widget_show(varGlobFront.zoneDessinBourges[idCarte]);
	gtk_widget_show(varGlobFront.zoneDessinInsa[idCarte]);
}
