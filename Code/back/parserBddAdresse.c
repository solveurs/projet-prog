#include "../headers/parserBddAdresse.h"

/**
 * \fn FILE * openBddAddr(const char * nom)
 * \brief Ouvre un fichier pour écriture de la bdd
 * \param *path le chemin du fichier à ouvrir
 */
FILE * openBddAddr(const char * nom)
{
    FILE * fd = NULL;
    if((fd = fopen(nom,"w")) == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier pour la bdd adresse.\n");
    }
    return fd;
}

/**
 * \fn FILE * pretreat_bddaddr(const char* source, const char* destination)
 * \brief Copie en changeant la mise en page le fichier IGN pour pouvoir utiliser readAddr sur ce nouveau fichier
 * \param *source le path vers le fichier source (généralement ADRESSE.csv)
 * \param *destination le path vers le nouveau fichier (généralement ADRESSE2.csv)
 */
FILE * pretreat_bddaddr(const char* source, const char* destination)
{
char c,c1; 
char ligne1[208];
FILE *fd_s, *fd_d;

    fd_s = fopen(source, "r");

    if( fd_s == NULL )
    {
        printf("Erreur...\n");
        exit(EXIT_FAILURE);
    }

    fd_d = fopen(destination, "w");

    if( fd_d == NULL )
    {
        fclose(fd_s);
        printf("Erreur...\n");
        exit(EXIT_FAILURE);
    }

    fgets(ligne1, 207,fd_s);
    fputs(ligne1, fd_d);

    while( ( c = fgetc(fd_s) ) != EOF )
    {
        
        if( c==',')
        {
            if (c1==',')
            {
                fputc('_',fd_d);
            }
            fputc(',',fd_d);
        }
        if (c == ' ')
        {
            fputc('_',fd_d);    
        }
        if ((c!=' ') && (c!=','))
        {
            fputc(c, fd_d); 
        }
        c1=c;
    }

    printf("Fichier pre-traite rempli.\n");

    fclose(fd_s);
    fclose(fd_d);
    fd_d = fopen(destination, "r");

    return fd_d;
}

/**
 * \fn void addAddr(bdd_addr* racine, bdd_addr* new_addr)
 * \brief Insère une nouvelle adresse dans la bdd
 * \param *racine la base de données dans laquelle insérer
 * \param *new_addr la nouvelle case de bdd à insérer
 */
void addAddr(bdd_addr* racine, bdd_addr* new_addr)
{
    //printf("rentre addAddr\n");
    if (racine!=NULL)
    {
       /* printf("racine non nulle\n");
        printf("%lf,\n", racine->addr.coord.x);
        printf("%lf,\n", racine->addr.coord.y);
        printf("%lf,\n", new_addr->addr.coord.x);
        printf("%lf,\n", new_addr->addr.coord.y);*/
        bdd_addr* fils;
        if ((racine->addr.coord.x > new_addr->addr.coord.x) || ((racine->addr.coord.x == new_addr->addr.coord.x) && (racine->addr.coord.y > new_addr->addr.coord.y)))
        {
            fils=racine->FGauche;
        }
        //if ((racine->addr.coord.x < new_addr->addr.coord.x) || ((racine->addr.coord.x == new_addr->addr.coord.x) && (racine->addr.coord.y <= new_addr->addr.coord.y)))
        else
        {
            fils=racine->FDroit;
        }

            if (fils==NULL)
            {
                if ((racine->addr.coord.x > new_addr->addr.coord.x) || ((racine->addr.coord.x == new_addr->addr.coord.x) && (racine->addr.coord.y > new_addr->addr.coord.y)))
                {
                    racine->FGauche=new_addr;
                }
                else
                {
                    racine->FDroit=new_addr;
                }
            }
            else 
            {
                addAddr(fils,new_addr);
            }
    }
    else
    {
        printf("Racine non initialisée");
    }
}

/**
 * \fn bdd_addr* recherche_exacte(bdd_addr* racine, point rech)
 * \brief Recherche dans la bdd si les coordonnées exactes d'un point ont une adresse
 * \param *racine la racine de la bdd dans laquelle on cherche
 * \param point le point que l'on cherche
 */
bdd_addr* recherche_exacte(bdd_addr* racine, point rech){
    bdd_addr* p;
    if (racine!=NULL)
    {
        if ((racine->addr.coord.x==rech.x) && (racine->addr.coord.y==rech.y))
        {
                p=racine;
        }
        else
        {
            if ((racine->addr.coord.x > rech.x) || ((racine->addr.coord.x == rech.x) && (racine->addr.coord.y > rech.y)))
            {
                p=recherche_exacte(racine->FGauche,rech);
            }
            else
            {
                p=recherche_exacte(racine->FDroit,rech);
            }
        }
    }
    else
    {
        p=NULL;
    }
    return p;
}
/**
 * \fn bdd_addr* recherche_intervalle(bdd_addr* racine, point rech, float intervalle)
 * \brief Recherche dans la bdd l'adresse la plus proche (s'il y a) d'un point dans un intervalle donné
 * \param *racine la racine de la bdd dans laquelle on cherche
 * \param point le point que l'on cherche
 * \param intervalle l'intervalle donné
 */
bdd_addr* recherche_intervalle(bdd_addr* racine, point rech,float intervalle){

    //A FAIRE APRES LA LOGIQUE
        //idée a voir : récursion sur un intervalle plus grand au lieu de p=NULL
        //utilisation de isInCercle ou dis2points ?
}

/**
 * \fn void write_infixe_bddAddr(bdd_addr *racine, File *fd)
 * \brief Écrit la bdd d'adresse en infixe dans un fichier
 * \param *racine la racine de la bdd à parcourir
 * \param *fd le descripteur du fichier ouvert en écriture dans lequel on retranscrit la base
 */
void write_infixe_bddAddr(bdd_addr *racine, FILE *fd)
{
    if (racine != NULL)
    {
        write_infixe_bddAddr(racine->FGauche,fd);
        char denomination[128];
        replace_char(racine->addr.nom_rue, denomination,' ','_');
        fprintf(fd,"%lf:%lf:%d:%s:%d\n",racine->addr.coord.x, racine->addr.coord.y, racine->addr.numero, denomination,  racine->addr.code_postal);
        write_infixe_bddAddr(racine->FDroit,fd);
    }
}

/**
 * \fn void write_prefixe_bddAddr(bdd_addr *racine, File *fd)
 * @brief Écrit la bdd d'adresse en prefixe dans un fichier
 * \param *racine la racine de la bdd à parcourir
 * \param *fd le descripteur du fichier ouvert en écriture dans lequel on retranscrit la base
 */
void write_prefixe_bddAddr(bdd_addr *racine, FILE *fd)
{
    if (racine != NULL)
    {
        char denomination[128];
        replace_char(racine->addr.nom_rue, denomination,' ','_');
        fprintf(fd,"%lf:%lf:%d:%s:%d\n",racine->addr.coord.x, racine->addr.coord.y, racine->addr.numero, denomination,  racine->addr.code_postal);
        write_prefixe_bddAddr(racine->FGauche,fd);
        write_prefixe_bddAddr(racine->FDroit,fd);
    }
}
/**
 * \fn void afficheAdresse(adresse addr)
 * @brief Affiche le contenu d'une adresse
 * \param addr l'adresse à afficher
 */
void afficheAdresse(adresse addr)
{
        printf("################################\n");
        printf("N ° %d\n",addr.numero);
        printf("%s\n",addr.nom_rue);
        printf("Code Postal :       %d\n",addr.code_postal);
        printf("Coordonées : %lf, %lf\n",addr.coord.x, addr.coord.y);
        printf("################################\n");
}

/**
 * \fn void replace_char(char s_origine[], char s_remp[],int c_origine, int c_remp)
 * \brief Copie s_point dans s_espace en remplaçant les points par des espaces
 * \param s_origine[] la chaîne de caractère dont les occurences d'un caractère sont à remplacer
 * \param s_remp[] chaîne de caractère vide qui aura la version avec le caractère remplacé
 * \param c_origine le code ASCII du caractère que l'on veut remplacer
 * \param c_remp le code ASCII du caractère par lequel on veut remplacer
 */
void replace_char(char s_origine[], char s_remp[],int c_origine, int c_remp)
{
    int i;
    for (i=0; s_origine[i]!= '\0'; i++)
    {
        if (s_origine[i] == c_origine)
        {
            s_remp[i] = c_remp;
        }
        else
        {
            s_remp[i] = s_origine[i];
        }
    }
    s_remp[i]='\0';
}

/**
 * \fn bdd_addr * readAddr(FILE * fd)
 * \brief Lit le fichier d'adresse .csv et renvoit la racine de l'arbre d'adresses correspondant
 * \param *fd descripteur sur le fichier au format d'ADRESSE2.csv
 */
bdd_addr * readAddr(FILE * fd)
{
    bdd_addr *varBddAddr=(bdd_addr*)malloc(sizeof(bdd_addr));
    varBddAddr->addr.coord.x=47.096689;
    varBddAddr->addr.coord.y=2.486328;
    varBddAddr->addr.numero=0;
    varBddAddr->addr.code_postal=18390;
    varBddAddr->FGauche=NULL;
    varBddAddr->FDroit=NULL;
    strcpy(varBddAddr->addr.nom_rue,"Valeur de reference bdd");
    afficheAdresse(varBddAddr->addr);

    char id[24], id_tr[24], methode[7], rep[9], compl[38], nom_rue[40], alias[30], nom_ld[42], type[16], cote[6], line[206];
    int numero, c_insee, c_postal;
    double x, y;    
    int i;
    float compteur=1;
    adresse varAddr;
    fscanf(fd,"%[^\n]\n",&line);
    printf("Première Ligne : %s\n",line);

    //for(i=0;i<4;i++) 
    //{ 
        //printf("Boucle For n°%d\n",i+1);
        
    	while(fscanf(fd,"%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,],%[^,],%lf,%lf\n",&id, &id_tr, &methode, &numero, &rep, &compl, &nom_rue, &alias, &nom_ld, &c_insee, &c_postal, &type, &cote, &x, &y)>0)
        {
            //printf("%f\n",compteur);
            //printf("\n%s|%s|%s|%d|%s|%s|%s|%s|%s|%d|%d|%s|%s|%lf|%lf\n",&id, &id_tr, &methode, numero, &rep, &compl, &nom_rue, &alias, &nom_ld, c_insee, c_postal, &type, &cote, x, y);
        
            varAddr.numero=numero;
            //printf("\nnumero : %i\n",numero);
            //Remplacement des '.' par des ' '
            char nom_voie[40];
            replace_char(nom_rue,nom_voie,'_',' ');
            strcpy(varAddr.nom_rue,nom_voie);//strcpy avant strcat sinon problème de string non initialisée
            //printf("Nom rue : %s\n", varAddr.nom_rue);
            if(strcmp(".",alias) != 0)
            {
                strcat(varAddr.nom_rue,", ");
                char alias2[30];
                replace_char(alias,alias2,'_',' ');
                strcat(varAddr.nom_rue,alias2);
                //printf("Avec Alias : %s\n",varAddr.nom_rue);
            }
            if ((strcmp(nom_rue,nom_ld) != 0) && (strcmp("_",nom_ld) != 0))
            {
                strcat(varAddr.nom_rue,", ");
                char nom_ld2[42];
                replace_char(nom_ld,nom_ld2,'.',' ');
                strcat(varAddr.nom_rue,nom_ld2);
                //printf("Avec Nom LD : %s\n",varAddr.nom_rue);
            }
            varAddr.code_postal=c_postal;
            //printf("Code Postal : %i\n",varAddr.code_postal);
            lambert93ToGPS(&x,&y);
            // DIRE A FLAVIEN QUE C'EST PAS LOGIQUE COMME RETOUR AVEC LES CONVENTIONS DU PROJET
            varAddr.coord.x=y;
            varAddr.coord.y=x;
            //printf("Coordonnées X: %lf, Y: %lf\n",varAddr.coord.x, varAddr.coord.y);
            //afficheAdresse(varAddr);  //A mettre en commentaire si l'on veut faire toute la base : ajoute du temps pour rien (1m10)

            bdd_addr *new=(bdd_addr*)malloc(sizeof(bdd_addr));
            new->addr=varAddr;
            /*
            bdd_addr *new2=(bdd_addr*)malloc(sizeof(bdd_addr));
            new2->addr.coord.x=47.0;
            new2->addr.coord.y=2.0;
            new2->addr.numero=42;
            new2->addr.code_postal=18000;
            new2->FGauche=NULL;
            new2->FDroit=NULL;
            strcpy(new2->addr.nom_rue,"Test");
            printf("avant affectation\n");
            printf("avant addAddr\n");
            addAddr(varBddAddr, new2);
            */
            addAddr(varBddAddr, new);

            //printf("apres addAddr\n");

           // compteur++;
       }//end while ou if fscanf
    //}//endfor
    printf("avant return\n");
	return varBddAddr;
}
/**
 * \fn bdd_addr * readAddr2(FILE * fd)
 * \brief Lit le fichier d'adresse .txt déjà généré et renvoit la racine de l'arbre d'adresses correspondant
 * \param *fd descripteur sur le fichier d'adresse (généralement bdd_adresse.txt)
 */
bdd_addr * readAddr2(FILE * fd)
{
    bdd_addr *varBddAddr=(bdd_addr*)malloc(sizeof(bdd_addr));
    varBddAddr->addr.coord.x=47.096689;
    varBddAddr->addr.coord.y=2.486328;
    varBddAddr->addr.numero=0;
    varBddAddr->addr.code_postal=18390;
    varBddAddr->FGauche=NULL;
    varBddAddr->FDroit=NULL;
    strcpy(varBddAddr->addr.nom_rue,"Valeur de reference bdd");
    afficheAdresse(varBddAddr->addr);

    char nom_rue[128];
    double x,y;
    int numero, c_postal;
    float compteur;
    adresse varAddr;

    while(fscanf(fd,"%lf:%lf:%d:%s:%d\n",&x,&y,&numero,nom_rue,&c_postal) > 0 )
    {
        //printf("%f\n",compteur);
        varAddr.numero=numero;
        char nom_voie[40];
        replace_char(nom_rue,nom_voie,'_',' ');
        strcpy(varAddr.nom_rue,nom_voie);
        varAddr.code_postal=c_postal;
        varAddr.coord.x=x;
        varAddr.coord.y=y;
        //afficheAdresse(varAddr);  //idem que plus haut, A mettre en commentaire si l'on veut faire toute la base : ajoute du temps pour rien (1m10)

        bdd_addr *new=(bdd_addr*)malloc(sizeof(bdd_addr));
        new->addr=varAddr;
        addAddr(varBddAddr, new);
        //compteur++;
    }
    return varBddAddr;
}