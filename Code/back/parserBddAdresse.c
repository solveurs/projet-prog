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
bdd_addr * readAddr(FILE * fd)
{
adresse ** varBddAddr=(adresse**)malloc(sizeof(adresse));
int compteurvirgule = 0;
adresse varAddr; //avant insertion dans la BDD

        while (fscanf(fd,"id:%s,id_tr:%s,methode:%s,numero:%i,rep:%s,compl:%s,nom_voie:%s,alias:%s,nom_ld:%s,insee:%i,c_postal:%i,type:%s,cote:%s,x_lambert:%i,y_lambert:%f" ) > 0)
        {
                vardAddr.numero=numero;
                varAddr.nom_rue=nom_voie;
                strncat(var.Addr.nom_rue,alias);
                if (strncmp(nom_voie,nom_ld) != 0)
                {
                        strncat(var.Addr.nom_rue,nom_ld);
                }
                varAddr.code_postal=c_postal;
        }



/* const char* recuperer_champ(char* ligne, int numero_champ)
{
	
  const char* tok;
  for (tok = strtok(ligne, ",");tok && *tok;tok = strtok(NULL, ",\n")) // strtok écrit sur ligne
  {
    //if (!--numero)
    {
      return tok;
    }
  }
  return NULL;
	
}*/
