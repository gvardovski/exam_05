#include "life.h"

int main(int gc, char **gv)
{
    if (gc != 4)
        return 1;
    t_life life;
    if (!getArg(&life, gv))
        return 1;
    if (!getCom(&life))
        return 1;
    if (!playGame(&life))
        return 1;
    printGrid(&life);
    freeAll(&life);
    return 0;
}