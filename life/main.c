#include "life.h"

int main(int gc, char **gv)
{
	if (gc != 4)
	    return 1;
	t_life life;
	if (!takeArg(&life, gv))
		return 1;
    if (!createLife(&life))
        return 1;
    readDraw(&life);
    runLife(&life);
    printLife(&life);
    destroyLife(&life);
    return 0;
}