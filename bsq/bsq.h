#ifndef BSQ_H
#define BSQ_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_map
{
    char **grid;
    int width;
    int height;
} t_map;

typedef struct s_elem
{
    int n_elem;
    char empty;
    char obst;
    char full;
} t_elem;

typedef struct s_square
{
    int size;
    int btm_i;
    int btm_j;
} t_square;

int procStream(FILE *f);
int procFile(char *path);

#endif