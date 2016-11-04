#include "headers/main.h"

//gcc main.c -D BACK -D FRONT -o test&& ./test
int main(int argc, char* argv[])
{

     #ifdef FRONT
          printf("front\n");
     #endif

     #ifdef BACK
          printf("back\n");
     #endif

     #ifdef DEBUG
          printf("debug\n");
     #endif
     printf("toujours\n");
     return 0;
}
