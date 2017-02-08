/**
 * \file      fctnCairo.c
 * \brief     Fichier main de la GUI de gestion des traces.
 * \author    T.Luu, G.Froger
 *
 * Le fichier contient toutes les fonctions utilisees pour le dessin des traces.
 * ====================
 *       TODO
 * ====================
 * + De nouvelles implementations ?
 * ====================
 *        MaJ
 * ====================
 * + Doxygen
 * + Implementation d'echelle des rayons
 *
 */
#include "../headers/front.h"

static int vitesse;
static int mode = MODE_NORMAL;
static int limite;
static int once = 0;


/**
 * \fn 		void faire_tracesCher(GtkWidget *widget, cairo_t *cr, gpointer user_data)
 * \brief   Fonction de tracer de la carte du Cher.
 *
 * \param 	widget Widget d'ou provient le signal "clicked".
 * \param 	cr Zone de dessin cairo creee automatiquement.
 * \param 	user_data Pointeur sur une information donnee dans le G_CALLBACK.
 *
 * \return 	None.
*/
void faire_tracesCher(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	tracesItem* ptrItem = (tracesItem *)user_data;
	faire_tracer(cr, 0, ptrItem);
}

/**
 * \fn 		void faire_tracesBourges(GtkWidget *widget, cairo_t *cr, gpointer user_data)
 * \brief   Fonction de tracer de la carte de Bourges.
 *
 * \param 	widget Widget d'ou provient le signal "clicked".
 * \param 	cr Zone de dessin cairo creee automatiquement.
 * \param 	user_data Pointeur sur une information donnee dans le G_CALLBACK.
 *
 * \return 	None.
*/
void faire_tracesBourges(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	tracesItem* ptrItem = (tracesItem *)user_data;
	faire_tracer(cr, 1, ptrItem);
}

/**
 * \fn 		void faire_tracesInsa(GtkWidget *widget, cairo_t *cr, gpointer user_data)
 * \brief   Fonction de tracer de la carte de l'Insa.
 *
 * \param 	widget Widget d'ou provient le signal "clicked".
 * \param 	cr Zone de dessin cairo creee automatiquement.
 * \param 	user_data Pointeur sur une information donnee dans le G_CALLBACK.
 *
 * \return 	None.
*/
void faire_tracesInsa(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	tracesItem* ptrItem = (tracesItem *)user_data;
	faire_tracer(cr, 2, ptrItem);
}

/**
 * \fn 		void faire_tracer(cairo_t *cr, int carte, tracesItem* item)
 * \brief   Fonction de tracer principale prenant aussi en charge les points d'interet.
 *
 * \param 	cr Zone de dessin cairo creee automatiquement.
 * \param   carte Id de la carte sur laquelle on dessine.
 * \param 	item Pointeur sur le trajet a tracer.
 *
 * \return 	None.
*/
void faire_tracer(cairo_t *cr, int carte, tracesItem* item)
{
	if(mode == MODE_NORMAL)
	{
		// Epaisseur des lignes
		cairo_set_line_width(cr, 1.0);
		// Traces en bleu
		cairo_set_source_rgb(cr, item->ptrCouleur->red, item->ptrCouleur->green, item->ptrCouleur->blue);
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
		for(ptr=item->ptrTrajet->premier; ptr!=item->ptrTrajet->dernier; ptr=ptr->suiv)
		{
			if(ptr->visibilite==1)
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
				
				if(item->ptrTrajet->visibilite) //si le trajet est visible
				{
					if(ptr->suiv != NULL && ptr->suiv->visibilite)
					{
						cairo_move_to(cr, x, y);
						x = (int)echelle(ptr->suiv->coord.y, carte, 1);
						y = (int)echelle(ptr->suiv->coord.x, carte, 0);
						cairo_line_to(cr, x, y);
					}
				}
			}
		}
		if(ptr->visibilite==1)
		{
			x = echelle(item->ptrTrajet->dernier->coord.x, carte, 1);
			y = echelle(item->ptrTrajet->dernier->coord.y, carte, 0);
			cairo_move_to(cr, x, y - TAILLE_TRACE);
			cairo_line_to(cr, x, y + TAILLE_TRACE);
			
			cairo_move_to(cr, x - TAILLE_TRACE, y);
			cairo_line_to(cr, x + TAILLE_TRACE, y);
		}

		cairo_stroke_preserve(cr);

		if(item->interet)
		{
			cairo_set_source_rgba(cr, item->ptrCouleur->red, item->ptrCouleur->green, item->ptrCouleur->blue, 0.35);
			int i;
			for(i=0; i<(item->ptrInteret->occupee); i++)
			{
				point centre = item->ptrInteret->t[i]->position;
				centre.x = echelle(centre.x, carte, 0);
				centre.y = echelle(centre.y, carte, 1);
				//double rayon = 50;
				//printf("\n%d", item->ptrInteret->t[i]->importance);
				double rayon = calculRayon(getCarte(), item->ptrInteret->importance_max, item->ptrInteret->t[i]->importance);
				faire_aggregation(cr, centre, rayon);
			}
		}
	}
	else
	{
		// Epaisseur des lignes
		cairo_set_line_width(cr, 1.0);
		// Traces en bleu
		cairo_set_source_rgb(cr, item->ptrCouleur->red, item->ptrCouleur->green, item->ptrCouleur->blue);
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
		trace* ptr = item->ptrTrajet->premier;
		int x, y;
		int incr = 0;
		int i;
		while(incr<limite)
		{
			for(i=0; i<vitesse; i++)
			{
				if(ptr == item->ptrTrajet->dernier)
				{
					break;
				}

				else if(ptr->visibilite==1 /*&& compareTps(ptr->date)*/)
				{
					// Inversion longitude et latitude
					x = (int)echelle(ptr->coord.y, carte, 1);
					y = (int)echelle(ptr->coord.x, carte, 0);				
					
					// Dessin d'un petit "+"
					cairo_move_to(cr, x, y - TAILLE_TRACE);
					cairo_line_to(cr, x, y + TAILLE_TRACE);
					
					cairo_move_to(cr, x - TAILLE_TRACE, y);
					cairo_line_to(cr, x + TAILLE_TRACE, y);
					
					if(item->ptrTrajet->visibilite) //si le trajet est visible
					{
						if(ptr->suiv != NULL && ptr->suiv->visibilite)
						{
							cairo_move_to(cr, x, y);
							x = (int)echelle(ptr->suiv->coord.y, carte, 1);
							y = (int)echelle(ptr->suiv->coord.x, carte, 0);
							cairo_line_to(cr, x, y);
						}
					}
				}

				ptr = ptr->suiv;
			}

			if(ptr == item->ptrTrajet->dernier)
			{
				cairo_move_to(cr, x, y - TAILLE_TRACE);
				cairo_line_to(cr, x, y + TAILLE_TRACE);
					
				cairo_move_to(cr, x - TAILLE_TRACE, y);
				cairo_line_to(cr, x + TAILLE_TRACE, y);

				if(!once)
				{
					popupMessage("Information", "Vous avez atteint la fin du trajet !", NULL);
					once++;
				}
			}

			incr += vitesse;
		}

		cairo_stroke_preserve(cr);
	}
}


/**
 * \fn 		double calculRayon(int carte, int importance_max, int importanceActuel)
 * \brief   Renvoie la taille du rayon d'un cercle en adequation avec la carte ciblee.
 *
 * \param   carte Id de la carte sur laquelle on dessine.
 * \param   importance_max Niveau d'importance maximale dans le trajet source.
 * \param 	importanceActuel Niveau d'importance dans le point d'interet a comparer.
 *
 * \return 	La taille du rayon adaptee a la carte.
*/
double calculRayon(int carte, int importance_max, int importanceActuel)
{
	double rayon = 0.0;
	double rapport = importanceActuel / importance_max;
	rapport = escalier(rapport);
	switch(carte)
	{
		case 0: // Cher
			rayon = rapport * TAILLE_RAYON_CHER;
			break;
		case 1: // Bourges
			rayon = rapport * TAILLE_RAYON_BOURGES;
			break;
		default: // Insa
			rayon = rapport * TAILLE_RAYON_INSA;
			break;
	}
	return rayon;
}

/**
 * \fn 		double escalier(double source)
 * \brief   Renvoie un coefficient pour moduler la taille du rayon d'un cercle.
 *
 * \param   source Rapport entre l'importance a tester par l'importance maximale du trajet.
 *
 * \return 	Le coefficient modulant la taille du rayon.
*/
double escalier(double source)
{
	/*int i;
	for(i=1; i<10; i++)
	{
		if(source<(i*0.1))
		{
			return (i*0.1);
		}
	}*/
	if(source<0.5)
	{
		return 0.5;
	}
	return source;
}

/**
 * \fn 		void faire_aggregation(cairo_t *cr, point centre, double r)
 * \brief   Tracer un cercle d'origine centre et de rayon r dans le contexte cr.
 *
 * \param   cr Pointeur sur la zone de dessin ou on effectue le trace.
 * \param   point Point servant de centre au cercle d'aggregation.
 * \param 	r Rayon du cercle.
 *
 * \return None.
*/
void faire_aggregation(cairo_t *cr, point centre, double r)
{
    cairo_set_line_width(cr, 2);  

    // Trace du cercle
    cairo_arc(cr, centre.y, centre.x, r, 0, 2 * M_PI);
    cairo_fill(cr);
    cairo_stroke_preserve(cr); 
}


/**
 * \fn 		double echelle(double valeur, int carte, int longitude)
 * \brief   Renvoie la valeur en coordonnee pixel d'une coordonnee GPS.
 *
 * \param   valeur Valeur initiale de la coordonnee GPS.
 * \param   carte Id de la carte sur laquelle on dessine.
 * \param   longitude Indique si l'on converti une longitude ou une latitude.
 *
 * \return 	La valeur de la coordonnee pixel.
*/
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

/**
 * \fn 		double conversionGPS(double valeur, int carte, int longitude)
 * \brief   Renvoie la valeur en coordonnee GPS d'une coordonnee pixel.
 *
 * \param   valeur Valeur initiale de la coordonnee pixel.
 * \param   carte Id de la carte sur laquelle on dessine.
 * \param   longitude Indique si l'on converti une longitude ou une latitude.
 *
 * \return 	La valeur de la coordonnee GPS.
*/
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

/**
 * \fn 		double rayonGPS(double rayonAConv, int carte)
 * \brief   Renvoie la taille d'un rayon a l'echelle GPS depuis un rayon a l'echelle pixel.
 *
 * \param   rayonAConv Rayon source a l'echelle pixel a convertir vers l'echelle GPS.
 * \param   carte Id de la carte sur laquelle on dessine.
 *
 * \return 	Le rayon converti a l'chelle GPS.
*/
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

/**
 * \fn 		void majCartes(int idCarte)
 * \brief   Met les cartes du Cher, Bourges et Insa d'un trajet a jour.
 *
 * \param   idCarte Id du trajet concerne.
 *
 * \return 	None.
*/
void majCartes(int idCarte)
{
	gtk_widget_queue_draw(varGlobFront.zoneDessinCher[idCarte]);
	gtk_widget_queue_draw(varGlobFront.zoneDessinBourges[idCarte]);
	gtk_widget_queue_draw(varGlobFront.zoneDessinInsa[idCarte]);
}

/**
 * \fn 		void majCartes(int idCarte)
 * \brief   Cache les cartes du Cher, Bourges et Insa d'un trajet.
 *
 * \param   idCarte Id du trajet a cacher.
 *
 * \return 	None.
*/
void cacheCartes(int idCarte)
{
	gtk_widget_hide(varGlobFront.zoneDessinCher[idCarte]);
	gtk_widget_hide(varGlobFront.zoneDessinBourges[idCarte]);
	gtk_widget_hide(varGlobFront.zoneDessinInsa[idCarte]);
}

/**
 * \fn 		void afficheCartes(int idCarte)
 * \brief   Affiche les cartes du Cher, Bourges et Insa d'un trajet.
 *
 * \param   idCarte Id du trajet a afficher.
 *
 * \return 	None.
*/
void afficheCartes(int idCarte)
{
	gtk_widget_show(varGlobFront.zoneDessinCher[idCarte]);
	gtk_widget_show(varGlobFront.zoneDessinBourges[idCarte]);
	gtk_widget_show(varGlobFront.zoneDessinInsa[idCarte]);
}

/**
 * \fn 		void switchMode(int type)
 * \brief   Permet de basculer entre le tracer d'animation ou le tracer statique.
 *
 * \param   type Mode vers lequel switch.
 *
 * \return 	None.
*/
void switchMode(int type)
{
	mode = type;
}

/**
 * \fn 		void setLimite(int max)
 * \brief   Affecte une valeur limite a la variable statique 'limite'.
 *
 * \param   max Nouvelle limite de la variable.
 *
 * \return 	None.
*/
void setLimite(int max)
{
	limite = max;
}
/**
 * \fn 		void setVitesse(int vit)
 * \brief   Affecte une nouvelle vitesse a la variable statique "vitesse".
 *
 * \param   vit Nouvelle vitesse de la variable.
 *
 * \return 	None.
*/
void setVitesse(int vit)
{
	vitesse = vit;
}
/**
 * \fn 		void incrLimite(int add, int taille)
 * \brief   Incremente de add la variable statique 'limite' si possible.
 *
 * \param   add Nombre d'incrementation de la variable.
 * \param   taille Taille maximale du trajet.
 *
 * \return 	None.
*/
void incrLimite(int add, int taille)
{
	limite += add;
	if(limite>taille)
	{
		limite = taille;
	}
}

/**
 * \fn 		void decrLimite(int sub)
 * \brief   Decremente de sub la variable statique 'limite' si possible.
 *
 * \param   sub Nombe de decrementation de 'limite'.
 *
 * \return 	None.
*/
void decrLimite(int sub)
{
	limite -= sub;
	if(limite<0)
	{
		limite = 0;
	}
}
/**
 * \fn 		void resetOnce()
 * \brief   Remet a zero la variable statique 'once'.
 *
 * \return 	None.
*/
void resetOnce()
{
	once = 0;
}
