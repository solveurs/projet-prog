#include <stdio.h>
#include <math.h>

int main(){

float x=655413, y=6664691;
lambert93(&x,&y);

printf("Ouh lala ça marche ??? %f°N %f°E",x, y);

return 0;
}
