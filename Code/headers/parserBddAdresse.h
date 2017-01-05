#pragma once
#include "includes.h"
#include "structures.h"
#include "conversion.h"

FILE * openBddAddr(const char * nom);
bdd_addr * readAddr(FILE * fd);
//bdd_trace * readGeoloc(FILE * parFd);
