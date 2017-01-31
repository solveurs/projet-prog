#pragma once
#include "includes.h"
#include "structures.h"
#include "conversion.h"
#include "parserBddGeoloc.h"
#include "trace.h"
#include "trajet.h"
#include "fonctionFront.h"
#include "pointInteret.h"
#include "config.h"
#include "utils.h"
#include "parserBddAdresse.h"

#include "front.h"
//#include "globalFront.h"
//#include "uiTraces.h"
//#include "uiAnimation.h"
//#include "uiAnonymite.h"
//#include "activate.h"
//#include "fctnCairo.h"
//#include "carte.h"
//#include "rectangle.h"
//#include "point.h"


void debugBack(void);
void debugFront(int argc, char* argv[]);

void initGlobFront(void);
void libereGlob(void);
