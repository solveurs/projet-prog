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
 * \fn void  addAddr (adresse * bdd, adresse addr)
 * \brief Ajoute une adresse à la table d'adresse en fonction de ses coordonnées
 * \param *bdd le tableau d'adresse qui sert de base de données
 * \param addr l'adresse à ajouter dans la bdd
 * \param intervalle nous sert pour la récursivité (taille de la base au premier appel)
 * \param intervalle nous sert pour la récursivité (0 au premier appel)
 */
void addAddr(bdd_addr *  bdd, adresse addr, int intervalle, int index)
{

	if (intervalle > 1) 
	{
		if (bdd->addr[index + intervalle%2].coord.x > addr.coord.x)
		{
			addAddr(bdd,addr,intervalle%2, index);
		}
		if(bdd->addr[index + intervalle%2].coord.x == addr.coord.x)
		{
			//Tri selon les y
			if(bdd->addr[index + intervalle%2 ].coord.y > addr.coord.y){
			
			}
		}
		else {
			addAddr(bdd,addr,intervalle%2+1, intervalle%2);
		}
	}
	else 
	{
		if (bdd->addr[index].coord.x > addr.coord.x)
		{
			ajout_adresse(bdd, addr, index);
			/*
			adresse * nv_table = (adresse*)malloc((bdd->taille+1)*sizeof(adresse));
			int i;
			for (i=0, i<index, i++){
				nv_table[i]=bdd->addr[i];
			}
			nv_table[index]=addr;
			for (i=index+1, i<bdd->taille+1, i++){
				nv_table[i]=bdd->addr[i-1];
			}
			free(bdd->addr);
			bdd->addr=nv_table;
			*/
		}	
	}

}

/**
 * \fn void ajout_adresse(bdd_addr * bdd, adresse addr, int index)
 * \brief Insère une adresse dans une base d'adresse à un index donné
 * \param bdd la base d'adresse
 * \param addr l'adresse à insérer
 * \param index l'index auquel insérer
 */
void ajout_adresse(bdd_addr * bdd, adresse addr, int index)
{
	adresse * nv_table = (adresse*)malloc((bdd->taille+1)*sizeof(adresse));
        int i;
        for (i=0; i<index; i++)
	{
        	nv_table[i]=bdd->addr[i];
        }
        nv_table[index]=addr;
        for (i=index+1; i<bdd->taille+1; i++)
	{
        	nv_table[i]=bdd->addr[i-1];
        }
        free(bdd->addr);
        bdd->addr=nv_table;
	bdd->taille++;
}


/**
 * \fn bdd_addr * readAddr(FILE * fd)
 * \brief Lit le fichier d'adresse .csv et renvoit un tableau d'adresses
 * \param *fd descripteur sur le fichier d'adresse
 */
bdd_addr readAddr(FILE * fd)
{
bdd_addr varBddAddr; 
varBddAddr.taille=0;
varBddAddr.addr=(adresse*)malloc(sizeof(adresse));
adresse varAddr; //avant insertion dans la BDD
char id, id_tr, methode, rep, compl, nom_rue, alias, nom_ld, type, cote;
int numero, c_insee, c_postal;
double x, y;

        while (fscanf(fd,"%[^,],%[^,],%[^,],%i,%[^,],%[^,],%[^,],%[^,],%[^,],%i,%i,%[^,],%[^,],x:%lf,y:%lf\n",&id, &id_tr, &methode, &numero, &rep, &compl, &nom_rue, &alias, &nom_ld, &c_insee, &c_postal, &type, &cote, &x, &y) > 0)
        {
                varAddr.numero=numero;
         //       strcpy(&varAddr.nom_rue,&nom_rue);//strcpy avant strcat sinon problème de string non initialisé
           //     strcat(&varAddr.nom_rue,&alias);
                if (strcmp(&nom_rue,&nom_ld) != 0)
                {
             //           strcat(&varAddr.nom_rue,&nom_ld);
                }
		varAddr.code_postal=c_postal;
		lambert93ToGPS(&x,&y);
		varAddr.coord.x=x;
		varAddr.coord.y=y;
		addAddr(&varBddAddr, varAddr,varBddAddr.taille,0);
		
        }
	return varBddAddr;

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
