#pragma once
#include "includes.h"
#include "structures.h"
#include "conversion.h"

FILE * openBddAddr(const char * nom);
void addAddr(bdd_addr * bdd, adresse addr, int intervalle, int index);
void ajout_adresse(bdd_addr * bdd, adresse addr, int index);
bdd_addr readAddr(FILE * fd);
//bdd_trace * readGeoloc(FILE * parFd);
