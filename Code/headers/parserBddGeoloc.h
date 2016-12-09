#pragma once
#include "includes.h"
#include "structures.h"
#include "trace.h"
#include "trajet.h"

FILE * openGeoloc(const char * nom);
bdd_trace * readGeoloc(FILE * parFd);
