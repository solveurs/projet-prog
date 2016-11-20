#include "headers/main.h"

//gcc main.c -D BACK -D FRONT -o test&& ./test
int main(int argc, char* argv[])
{
	
#ifdef FRONT
	printf("front\n");
	
#elif BACK
	printf("back\n");
	
	
#elif DEBUG
	printf("debug\n");
	
	double x=655712, y=6664882;	//position INSA
	lambert93ToGPS(&x,&y);
	printf("long : %lf , lat: %lf\n",x, y);
	
	printf("Date de %d : %s \n",1477070408,timestampToString(1477070408));
#endif
	//printf("toujours\n");
	return 0;
}
