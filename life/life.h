#ifndef LIFE_H
#define LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_life 
{
    int width;
    int height;
	int iter;
    char *curr;
    char *next;
} t_life;

int createLife(t_life *life);
void destroyLife(t_life *life);
void readDraw(t_life *life);
void runLife(t_life *life);
void printLife(t_life *life);
int takeArg(t_life *life, char **gv);

#endif