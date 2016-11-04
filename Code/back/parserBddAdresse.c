#include "../headers/parserBddAdresse.h"
/**
 * \fn void const char* recuperer_champ(char* ligne, int numero_champ)
 * \brief Récupère un champ dans un fichier csv
 * \param ligne numéro de ligne
 * \param numero_champ numéro de champ
 */
 
const char* recuperer_champ(char* ligne, int numero_champ)
{
  const char* tok;
  for (tok = strtok(ligne, ",");tok && *tok;tok = strtok(NULL, ",\n")) // strtok écrit sur ligne
  {
    if (!--numero)
    {
      return tok;
    }
  }
  return NULL;
}
 
int main()
{
  char ligne[1024];
  while (fgets(ligne, 1024, stdin))
  {
    char* temp = strdup(ligne);
    const char X=recuperer_champ(temp, 13);
    const char Y=recuperer_champ(temp, 14);
    printf("Coordonnees en lambert, %s %s", X, Y);
    free(temp);
  }
} 


