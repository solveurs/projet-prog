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

/**
 * \fn bdd_addr * readAddr(FILE * fd)
 * \brief Lit le fichier d'adresse .csv et renvoit un tableau d'adresses
 * \param *fd descripteur sur le fichier d'adresse
 */
adresse * readAddr(FILE * fd)
{
adresse * varBddAddr=(adresse*)malloc(sizeof(adresse));
int compteurvirgule = 0;
adresse varAddr; //avant insertion dans la BDD

        while (fscanf(fd,"id:%s,id_tr:%s,methode:%s,numero:%i,rep:%s,compl:%s,nom_voie:%s,alias:%s,nom_ld:%s,insee:%i,c_postal:%i,type:%s,cote:%s,x:%lf,y:%lf" ) > 0)
        {
                vardAddr.numero=numero;
                varAddr.nom_rue=nom_voie;
                strncat(var.Addr.nom_rue,alias);
                if (strncmp(nom_voie,nom_ld) != 0)
                {
                        strncat(var.Addr.nom_rue,nom_ld);
                }
		varAddr.code_postal=c_postal;
		lambert93ToGPS(&x,&y);
		varAddr.coord.x=x;
		varAddr.coord.y=y;
        }

/* //Tentative avec un switch :
                int compteurvirgule = 0;
        while (fscanf(fd) != '\0')
        {
                switch (compteurvirgule){
                        case 1;//Non utilisé
                        case 2;//Non utilisé
                        //Numéro
                        case 3:
                                while(fscanf(fd) != ",")
                                {
                                // /!\ Vérifier string.h
                                
                                }
                                compteurvirgule++;
                        break;
                        //Nom rue
                        case [5,7]
                                while(fscanf(fd) != ",")
                                {

                                }
                                compteurvirgule++;
                        break;
                        //Nom rue suite (alias)
                        //Nom rue suite (nom LDC)
                        default;
                                compteurvirgule++;

                }
        }
*/
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
	
/*
bdd_trace * readGeoloc(FILE * parFd)
{
	
}*/
