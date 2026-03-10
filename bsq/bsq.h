#ifndef BSQ_H
#define BSQ_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_elements 
{
    int n_lines;
    char empty;
    char obstacle;
    char full;
} t_elements;

typedef struct s_map 
{
    char **grid;
    int width;
    int height;
} t_map;

typedef struct s_square
{
    int size;
    int bottom_i;
    int bottom_j;
} t_square;

int process_stream(FILE *f);
int process_file(char *path);

#endif