#pragma once

#include "includes.h"
#include "signal.h"
#include "globalFront.h"

/* ====== UI.h ====== */
#include "activate.h"
#include "uiTraces.h"
#include "uiAnimation.h"
#include "uiAnonymite.h"
#include "uiAide.h"
#include "uiMenu.h"

/* ====== Structures ====== */
#include "structures.h"
#include "carte.h"
#include "point.h"
#include "rectangle.h"

/* ====== Fonctions ====== */
#include "fctnCairo.h"
#include "fctnUsuelles.h"
#include "fonctionFront.h"

extern void activate(GtkApplication *app, gpointer user_data);
