#include "../headers/parserBddAdresse.h"
/**
 * \fn void const char* recuperer_champ(char* ligne, int numero_champ)
 * \brief Récupère un champ dans un fichier csv
 * \param ligne numéro de ligne
 * \param numero_champ numéro de champ
 */

FILE * openBddAddr(const char * nom)
{
	FILE * fd = NULL;
	if((fd = fopen(nom,"r")) == NULL){
		perror("Erreur lors de l'ouverture de la base de donnees adresses\n");
	}
	return fd;
	
}


/*
bdd_trace * readGeoloc(FILE * parFd)
{
	
}*/
const char* recuperer_champ(char* ligne, int numero_champ)
{
	
//  const char* tok;
//  for (tok = strtok(ligne, ",");tok && *tok;tok = strtok(NULL, ",\n")) // strtok écrit sur ligne
//  {
//    //if (!--numero)
//    {
//      return tok;
//    }
//  }
//  return NULL;
	
}
