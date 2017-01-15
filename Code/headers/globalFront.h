#pragma once

#include "includes.h"
#include "structures.h"
#include "carte.h"

/* ====== CONSTANTES ====== */
#define NOMBRE_MAX_TRAJETS	32

/* ====== Var. Glob ====== */
struct globFront
{
	int				trajetId[NOMBRE_MAX_TRAJETS];
	int				idTrajet;

	GtkWidget*		zoneDessinCher[NOMBRE_MAX_TRAJETS];
	GtkWidget*		zoneDessinBourges[NOMBRE_MAX_TRAJETS];
	GtkWidget*		zoneDessinInsa[NOMBRE_MAX_TRAJETS];

	GtkWidget   	*overlayCarteCher;
  	GtkWidget   	*overlayCarteBourges;
  	GtkWidget   	*overlayCarteInsa;

  	carte 			carte_Cher;
  	carte 			carte_Bourges;
  	carte 			carte_Insa;
};

extern struct globFront varGlobFront;
