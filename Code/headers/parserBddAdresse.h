#pragma once
#include "includes.h"
#include "structures.h"
#include "conversion.h"

FILE * openBddAddr(const char * nom);
FILE * pretreat_bddaddr(const char* source, const char* destination);
void addAddr(bdd_addr* racine, bdd_addr* new_addr);
bdd_addr* recherche_exacte(bdd_addr* racine, point rech);
bdd_addr* recherche_intervalle(bdd_addr* racine, point rech,float intervalle);//A faire
void write_infixe_bddAddr(bdd_addr *racine, FILE *fd);
void write_prefixe_bddAddr(bdd_addr *racine, FILE *fd);
void afficheAdresse(adresse addr);
void replace_char(char s_origine[], char s_remp[],int c_origine, int c_remp);
bdd_addr * readAddr(FILE * fd);
bdd_addr * readAddr2(FILE * fd);