#include "life.h"

void printGrid(t_life *life)
{
    if (!life)
        return;
    int i = 0;
    while (i < (life->width * life->height))
    {
        putchar(life->grid[i++] ? 'O' : ' ');
        if (i % life->width == 0)
            putchar('\n');
    }
}

int freeAll(t_life *life)
{
    if (!life)
        return 0;
    if (life->seq)
        free(life->seq);
    if (life->grid)
        free(life->grid);
    life->seq = NULL;
    life->grid = NULL;
    return 0;
}

int getArg(t_life *life, char **gv)
{
    if (!life)
        return 0;
    life->width = atoi(gv[1]);
    life->height = atoi(gv[2]);
    life->iter = atoi(gv[3]);
    if (life->width <= 0 || life->height <= 0 || life->iter < 0)
        return 0;
    return 1;
}

int getCom(t_life *life)
{
    if (!life)
        return 0;
    int cap = 256;
    int len = 0;
    char buf[256];
    ssize_t r;

    life->seq = malloc((cap + 1) * sizeof(char));
    if (!life->seq)
        return 0;
    while ((r = read(0, buf, sizeof(buf))) > 0)
    {
        while (len + (int)r > cap)
        {
            char *tmp;

            cap *= 2;
            tmp = realloc(life->seq, (cap + 1) * sizeof(char));
            if (!tmp)
                return freeAll(life);
            life->seq = tmp;
        }
        for (ssize_t i = 0; i < r; i++)
            life->seq[len++] = buf[i];
    }
    if (r < 0)
        return freeAll(life);
    life->seq[len] = '\0';
    return 1;
}

static void draw_initial_grid(t_life *life)
{
    int x = 0;
    int y = 0;
    int pen_down = 0;
    int i = 0;
    while (life->seq[i])
    {
        if (life->seq[i] == 'x')
        {
            pen_down = !pen_down;
            if (pen_down)
                life->grid[y * life->width + x] = 1;
        }
        else
        {
            int nx = x;
            int ny = y;
            if (life->seq[i] == 'w')
                ny--;
            else if (life->seq[i] == 'a')
                nx--;
            else if (life->seq[i] == 's')
                ny++;
            else if (life->seq[i] == 'd')
                nx++;
            if (nx >= 0 && nx < life->width && ny >= 0 && ny < life->height)
            {
                x = nx;
                y = ny;
                if (pen_down)
                    life->grid[y * life->width + x] = 1;
            }
        }
        i++;
    }
}

static int count_neighbors(t_life *life, int x, int y)
{
    int count = 0;

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int nx;
            int ny;

            if (dx == 0 && dy == 0)
                continue;
            nx = x + dx;
            ny = y + dy;
            if (nx >= 0 && nx < life->width && ny >= 0 && ny < life->height)
                count += life->grid[ny * life->width + nx] ? 1 : 0;
        }
    }
    return count;
}

int playGame(t_life *life)
{
    if (!life)
        return freeAll(life);
    life->grid = calloc(life->width * life->height, sizeof(char));
    if (!life->grid)
        return freeAll(life);
    draw_initial_grid(life);
    for (int step = 0; step < life->iter; step++)
    {
        char *next = calloc(life->width * life->height, sizeof(char));
        if (!next)
            return freeAll(life);
        for (int y = 0; y < life->height; y++)
        {
            for (int x = 0; x < life->width; x++)
            {
                int idx = y * life->width + x;
                int n = count_neighbors(life, x, y);

                if (life->grid[idx])
                    next[idx] = (n == 2 || n == 3);
                else
                    next[idx] = (n == 3);
            }
        }
        free(life->grid);
        life->grid = next;
    }
    return 1;
}