#ifndef LIFE_H
#define LIFE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_life
{
    char *grid;
    char *seq;
    int width;
    int height;
    int iter;
} t_life;

int getArg(t_life *life, char **gv);
int getCom(t_life *life);
int playGame(t_life *life);
int freeAll(t_life *life);
void printGrid(t_life *life);

#endif