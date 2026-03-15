#include "bsq.h"

static void freeMap(t_map *map)
{
    if (!map || !map->grid)
        return;
    for (int i = 0; i < map->height; i++)
        free(map->grid[i]);
    free(map->grid);
}

static int freeAll(char *line, t_map *map)
{
    free(line);
    freeMap(map);
    return 0;
}

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

static int parseElem(FILE *f, t_elem *el)
{
    if (!f || !el)
        return 0;
    int n = fscanf(f, "%d %c %c %c\n", &el->n_elem, &el->free, &el->obstacle, &el->full);
    if (n != 4)
        return 0;
    if (el->n_elem <= 0)
        return 0;
    if (el->free == el->obstacle || el->free == el->full || el->obstacle == el->full)
        return 0;
    return 1;
}

static int parseMap(FILE *f, t_map *map, t_elem *el)
{
    char *line = NULL;
    size_t cap = 0;
    int j;
    int i;
    if (!map || !f || !el)
        return 0;
    map->height = el->n_elem;
    map->width = 0;
    map->grid = malloc((size_t)map->height * sizeof(char *));
    if (!map->grid)
        return 0;
    for (i = 0; i < map->height; i++) 
	{
        ssize_t len = getline(&line, &cap, f);
        if (len == -1 || len <= 1 || line[--len] != '\n')
            return freeAll(line, map);
        line[len] = '\0';
        if (map->width == 0) 
            map->width = (int)len;
		else if (map->width != (int)len) 
            return freeAll(line, map);
        map->grid[i] = malloc((size_t)map->width + 1);
        if (!map->grid[i]) 
		    return freeAll(line, map);
        for (j = 0; j < map->width; j++) 
		{
            if (line[j] != el->free && line[j] != el->obstacle) 
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
    int temp = a;
    if (b < temp)
        temp = b;
    if (c < temp)
        temp = c;
    return temp;
}

static int solve_bsq(t_map *map, t_elem *el)
{
    int *prev;
    int *curr;
    t_square best;
    int i;
    int j;
    if (!map || !el)
        return 0;
    best.size = 0;
    best.botm_i = 0;
    best.botm_j = 0;
    prev = calloc((size_t)map->width, sizeof(int));
    curr = calloc((size_t)map->width, sizeof(int));
    if (!prev || !curr)
    {
        free(prev);
        free(curr);
        return 0;
    }
    for (i = 0; i < map->height; i++)
	{
        for (j = 0; j < map->width; j++) 
		{
            if (map->grid[i][j] == el->obstacle)
                curr[j] = 0;
            else 
			{
                if (i == 0 || j == 0)
                    curr[j] = 1;
                else
                    curr[j] = 1 + min3(prev[j], prev[j - 1], curr[j - 1]);
                if (curr[j] > best.size)
				{
                    best.size = curr[j];
                    best.botm_i = i;
                    best.botm_j = j;
                }
            }
        }
        {
            int *tmp = prev;
            prev = curr;
            curr = tmp;
        }
    }
    if (best.size > 0)
    {
        int top = best.botm_i - best.size + 1;
        int left = best.botm_j - best.size + 1;
        for (i = top; i <= best.botm_i; i++)
            for (j = left; j <= best.botm_j; j++)
                map->grid[i][j] = el->full;
    }
    free(prev);
    free(curr);
    return 1;
}

int procStream(FILE *f)
{
    t_map map;
    t_elem el;
    int rez = 1;
    if (!parseElem(f, &el))
        return 0;
    if (!parseMap(f, &map, &el))
        return 0;
    rez = solve_bsq(&map, &el);
    if (rez == 1)
        printMap(&map);
    freeMap(&map);
    return rez;
}

int procFile(char *path)
{
    int rez;
    FILE *f;
    f = fopen(path, "r");
    if (!f)
        return 0;
    rez = procStream(f);
    fclose(f);
    return rez;
}