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

void faire_tracesCher(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	tracesItem* ptrItem = (tracesItem *)user_data;
	faire_tracer(cr, 0, ptrItem->ptrTrajet, ptrItem->ptrCouleur);
}

void faire_tracesBourges(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	tracesItem* ptrItem = (tracesItem *)user_data;
	faire_tracer(cr, 1, ptrItem->ptrTrajet, ptrItem->ptrCouleur);
}

void faire_tracesInsa(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	tracesItem* ptrItem = (tracesItem *)user_data;
	faire_tracer(cr, 2, ptrItem->ptrTrajet, ptrItem->ptrCouleur);
}

void faire_tracer(cairo_t *cr, int carte, trajet *cible, GdkRGBA* couleur)
{
	// Epaisseur des lignes
	cairo_set_line_width(cr, 1.0);
	// Traces en bleu
	cairo_set_source_rgb(cr, couleur->red, couleur->green, couleur->blue);
	// Taille des traces
	double TAILLE_TRACE;
	switch(carte)
	{
		case 0:
			TAILLE_TRACE = TAILLE_TRACE_CHER;
			break;
		case 1:
			TAILLE_TRACE = TAILLE_TRACE_BOURGES;
			break;
		default:
			TAILLE_TRACE = TAILLE_TRACE_INSA;
	}
	
	// Tracer des points
	trace* ptr;
	int x, y;
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
				conversion = ((valeur - LON_HG_CHER) * TAILLE_X_CHER / (LON_BD_CHER - LON_HG_CHER));
				return conversion;
			}
			conversion = ((valeur - LAT_HG_CHER) * TAILLE_Y_CHER / (LAT_BD_CHER - LAT_HG_CHER));
			return conversion;
			
		case 1: // Bourges
			if(longitude)
			{
				conversion = ((valeur - LON_HG_BOURGES) * TAILLE_X_BOURGES / (LON_BD_BOURGES - LON_HG_BOURGES));
				return conversion;
			}
			conversion = ((valeur - LAT_HG_BOURGES) * TAILLE_Y_BOURGES / (LAT_BD_BOURGES - LAT_HG_BOURGES));
			return conversion;
			
		default: // Insa
			if(longitude)
			{
				conversion = ((valeur - LON_HG_INSA) * TAILLE_X_INSA / (LON_BD_INSA - LON_HG_INSA));
				return conversion;
			}
			conversion = ((valeur - LAT_HG_INSA) * TAILLE_Y_INSA / (LAT_BD_INSA - LAT_HG_INSA));
			return conversion;
	}
}

double conversionGPS(double valeur, int carte, int longitude)
{
	double conversion = 0.0;
	switch(carte)
	{
	  	case 0: // Cher
			if(longitude)
			{
				conversion = ( ((valeur * (LON_BD_CHER - LON_HG_CHER) / TAILLE_X_CHER)) + LON_HG_CHER );
				return conversion;
			}
			conversion = ( ((valeur * (LAT_BD_CHER - LAT_HG_CHER) / TAILLE_Y_CHER)) + LAT_HG_CHER );
			return conversion;	

		case 1: // Bourges
			if(longitude)
			{
				conversion = ( ((valeur * (LON_BD_BOURGES - LON_HG_BOURGES) / TAILLE_X_BOURGES)) + LON_HG_BOURGES );
				return conversion;
			}
			conversion = ( ((valeur * (LAT_BD_BOURGES - LAT_HG_BOURGES) / TAILLE_Y_BOURGES)) + LAT_HG_BOURGES );
			return conversion;	

		default: // Insa
			if(longitude)
			{
				conversion = ( ((valeur * (LON_BD_INSA - LON_HG_INSA) / TAILLE_X_INSA)) + LON_HG_INSA );
				return conversion;
			}
			conversion = ( ((valeur * (LAT_BD_INSA - LAT_HG_INSA) / TAILLE_Y_INSA)) + LAT_HG_INSA );
			return conversion;	
	}
}

double rayonGPS(double rayonAConv, int carte)
{
	double r;
	switch(carte)
	{
		case 0:
			r = ((LON_BD_CHER - LON_HG_CHER) * rayonAConv / TAILLE_X_CHER );
			break;
		case 1:
			r = ((LON_BD_BOURGES - LON_HG_BOURGES) * rayonAConv / TAILLE_X_BOURGES );
			break;
		default:
			r = ((LON_BD_INSA - LON_HG_INSA) * rayonAConv / TAILLE_X_INSA );
	}
  	return r;
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
