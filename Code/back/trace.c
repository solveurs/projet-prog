#include "../headers/trace.h"

trace * createTrace(void)
{
	trace * varT = (trace*)malloc(sizeof(trace));
	return varT;
}

void initTrace(trace * parT, long parDate, point parCoord, trace * parPrec, trace * parSuiv)
{
	if (parT == NULL)
	{
		parT = createTrace();
	}
	parT->date			= parDate;
	parT->coord			= parCoord;
	parT->prec			= parPrec;
	parT->suiv			= parSuiv;
	parT->visibilite	= 1;
}

void afficheTrace(trace * parT)
{
	printf("--------------------------------\n");
	printf("date :       %s\n",timestampToString(parT->date));
	printf("Coordonées : %lf, %lf\n",parT->coord.x, parT->coord.y);
	printf("--------------------------------\n");
}
