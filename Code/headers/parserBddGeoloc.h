#pragma once
#include "includes.h"
#include "structures.h"
#include "trace.h"

FILE * openGeoloc(const char * nom);
bdd_trace * readGeoloc(FILE * parFd);
