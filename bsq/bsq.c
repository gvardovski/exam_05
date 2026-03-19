#include "bsq.h"

static void printMap(t_map *map)
{
    if (!map || !map->grid)
        return;
    for (int i = 0; i < map->height; i++)
    {
        fputs(map->grid[i], stdout);
        fputs("\n", stdout);
    }
}

static void freeMap(t_map *map)
{
    if (!map || !map->grid)
        return;
    for (int i = 0; i < map->height; i++)
    {
        if (map->grid[i])
            free(map->grid[i]);
    }
    free(map->grid);
    map->grid = NULL;
}

static int freeAll(char *line, t_map *map)
{
    free(line);
    freeMap(map);
    return 0;
}

int getArg(FILE *f, t_elem *el)
{
    if (!f || !el)
        return 0;
    int n = fscanf(f, "%d %c %c %c\n", &el->n_elem, &el->empty, &el->obst, &el->full);
    if (n != 4 || el->n_elem <= 0 || el->empty == el->obst || el->empty == el->full || el->obst == el->full)
        return 0;
    return 1;
}

int getMap(FILE *f, t_map *map, t_elem *el)
{
    if (!f || !el || !map)
        return 0;
    char *line = NULL;
    size_t cap = 0;
    map->height = el->n_elem;
    map->width = 0;
    map->grid = calloc(map->height, sizeof(char *));
    if (!map->grid)
        return 0;
    for (int i = 0; i < map->height; i++)
    {
        ssize_t len = getline(&line, &cap, f);
        if (len <= 0)
            return freeAll(line, map);
        if (line[len - 1] == '\n')
            line[--len] = '\0';
        else if (i + 1 < map->height)
            return freeAll(line, map);
        else
            line[len] = '\0';
        if (map->width == 0)
            map->width = (int)len;
        else if (map->width != (int)len)
            return freeAll(line, map);
        map->grid[i] = malloc((map->width + 1) * sizeof(char));
        if (!map->grid[i])
            return freeAll(line, map);
        for (int j = 0; j < map->width; j++)
        {
            if (line[j] != el->empty && line[j] != el->obst)
               return freeAll(line, map);
            map->grid[i][j] = line[j]; 
        }
        map->grid[i][map->width] = '\0';
    }
    free(line);
    return 1;
}

static int min3(int a, int b, int c)
{
    int tmp = a;
    if (b < tmp)
        tmp = b;
    if (c < tmp)
        tmp = c;
    return tmp;
}

static int slvBsq(t_map *map, t_elem *el)
{
    if (!map || !el)
        return 0;
    int *priv;
    int *curr;
    t_square best;
    int i;
    int j;
    best.size = 0;
    best.btm_i = 0;
    best.btm_j = 0;
    priv = calloc(map->width + 1, sizeof(int));
    if (!priv)
        return 0;
    curr = calloc(map->width + 1, sizeof(int));
    if (!curr)
    {
        free(priv);
        return 0;
    }
    for (i = 0; i < map->height; i++)
    {
        for (j = 0; j < map->width; j++)
        {
            if (map->grid[i][j] == el->obst)
                curr[j] = 0;
            else
            {
                if (i == 0 || j == 00)
                    curr[j] = 1;
                else
                    curr[j] = 1 + min3(priv[j], priv[j - 1], curr[j - 1]);
                if (curr[j] > best.size)
                {
                    best.size = curr[j];
                    best.btm_i = i;
                    best.btm_j = j;
                }
            }
        }
        int *tmp = priv;
        priv = curr;
        curr = tmp;
    }
    if (best.size > 0)
    {
        int top = best.btm_i - best.size + 1;
        int left = best.btm_j - best.size + 1;
        for (i = top; i <= best.btm_i; i++)
            for (j = left; j <= best.btm_j; j++)
                map->grid[i][j] = el->full;
    }
    free(priv);
    free(curr);
    return 1;
}

int procStream(FILE *f)
{
    t_map map;
    t_elem el;
    if (!getArg(f, &el))
        return 0;
    if (!getMap(f, &map, &el))
        return 0;
    int rez = slvBsq(&map, &el);
    if (rez == 1)
        printMap(&map);
    freeMap(&map);
    return rez;
}

int procFile(char *path)
{
    FILE *f = fopen(path, "r");
    if (!f)
        return 0;
    int rez = procStream(f);
    fclose(f);
    return rez;
}