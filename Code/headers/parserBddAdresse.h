#pragma once
#include "includes.h"
#include "structures.h"

FILE * openBddAddr(const char * nom);
bdd_addr * readAddr(FILE * fd);
//bdd_trace * readGeoloc(FILE * parFd);
