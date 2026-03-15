#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <unistd.h>
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
    char free;
    char obstacle;
    char full;
} t_elem;

typedef struct s_square
{
    int size;
    int botm_i;
    int botm_j;
} t_square;

int procFile(char *path);
int procStream(FILE *f);

#endif