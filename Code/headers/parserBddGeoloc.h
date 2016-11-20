#pragma once
#include "includes.h"
#include "structures.h"

FILE * openGeoloc(const char * nom);
bdd_trace * readGeoloc(FILE * parFd);
