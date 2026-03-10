#include "bsq.h"

static void print_map(t_map *map) 
{
    if (!map || !map->grid)
        return ;
    for (int i = 0; i < map->height; i++) 
	{
        fputs(map->grid[i], stdout);
        fputs("\n", stdout);
    }
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

static void free_map(t_map *map) 
{
    if (!map || !map->grid)
        return ;
    for (int i = 0; i < map->height; i++)
        free(map->grid[i]);
    free(map->grid);
    map->grid = NULL;
    map->height = 0;
    map->width = 0;
}

static int parse_elements(FILE *f, t_elements *el) 
{
    if (!f || !el)
        return 0;
    int res = fscanf(f, "%d %c %c %c\n", &el->n_lines, &el->empty, &el->obstacle, &el->full);
    if (res != 4)
        return 0;
    if (el->n_lines <= 0)
        return 0;
    if (el->empty == el->obstacle || el->empty == el->full || el->obstacle == el->full)
        return 0;
    return 1;
}

static int parse_map(FILE *f, t_map *map, t_elements *el)
{
    char *line = NULL;
    size_t cap = 0;
    int cols = -1;
    int j;
    int i;
    if (!map || !f || !el)
        return 0;
    map->grid = NULL;
    map->height = el->n_lines;
    map->width = 0;
    map->grid = malloc((size_t)map->height * sizeof(char *));
    if (!map->grid)
        return 0;
    for (i = 0; i < map->height; i++) 
	{
        ssize_t len = getline(&line, &cap, f);
        if (len == -1 || len <= 1 || line[len -1] != '\n') 
		{
            free(line);
            free_map(map);
            return 0;
        }
        line[len - 1] = '\0';
        len--;
        if (cols == -1) 
		{
            cols = (int)len;
            if (cols <= 0)
			{
                free(line);
                free_map(map);
                return 0;                  
            }
            map->width = cols;
        }
		else if (cols != (int)len) 
		{
                free(line);
                free_map(map);
                return 0;              
        }
        map->grid[i] = malloc((size_t)cols + 1);
        if (!map->grid[i]) 
		{
            free(line);
            free_map(map);
            return 0;  
        }
        for (j = 0; j < cols; j++) 
		{
            char c = line[j];
            if (c != el->empty && c != el->obstacle) 
			{
                free(line);
                free_map(map);
                return 0;              
            }
        }
        for (j = 0; j < cols; j++)
            map->grid[i][j] = line[j];
        map->grid[i][cols] = '\0';
    }
    free(line);
    return 1;
}

static int solve_bsq(t_map *map, t_elements *el)
{
    int *prev;
    int *curr;
    t_square best;
    int i;
    int j;
    if (!map || !el)
        return 0;
    best.size = 0;
    best.bottom_i = 0;
    best.bottom_j = 0;
    prev = calloc((size_t)map->width, sizeof(int));
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
                    best.bottom_i = i;
                    best.bottom_j = j;
                }
            }
        }
    }
    return 1;
}

int process_stream(FILE *f) 
{
    t_map map;
    t_elements el;
    int res;

    if (!parse_elements(f, &el))
        return 0;
    if (!parse_map(f, &map, &el))
        return 0;
    res = solve_bsq(&map, &el);
    if (res == 1)
        print_map(&map);
    return res;
}

int process_file(char *path) 
{
    int res;
    FILE *f;

    f = fopen(path, "r");
    if (!f)
        return 0;
    res = process_stream(f);
    fclose(f);
    return res;
}