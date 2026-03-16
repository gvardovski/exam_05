#include "life.h"

int takeArg(t_life *life, char **gv)
{
	if (!life || atoi(gv[1]) <= 0 || atoi(gv[2]) <= 0 || atoi(gv[3]) < 0)
		return 0;
	life->width = atoi(gv[1]);
	life->height = atoi(gv[2]);
	life->iter = atoi(gv[3]);
	return 1;
}

int createLife(t_life *life)
{
	size_t size = life->height * life->width;
    life->curr = calloc(size, sizeof(char));
    life->next = calloc(size, sizeof(char));
    if (!life->curr || !life->next)
	{
		destroyLife(life);
		return 0;
	}
    return 1;
}

void destroyLife(t_life *life)
{
    if (!life)
        return;
    free(life->curr);
    free(life->next);
}

static int inside(t_life *life, int x, int y) 
{
    return (x >= 0 && y >= 0 && x < life->width && y < life->height);
}

static int idx(t_life *life, int x, int y) 
{
    return y * life->width + x;
}

static void setActive(t_life *life, int x, int y) 
{
    if (inside(life, x, y))
        life->curr[idx(life, x, y)] = 1;
}

static int getCell(char *grid, t_life *life, int x, int y) 
{
    if (!inside(life, x, y))
        return 0;
    return (grid[idx(life, x, y)] != 0);
}

static int countNeighbors(t_life *life, int x, int y) 
{
    int dx;
    int dy;
    int count = 0;
    dy = -1;
    while (dy <= 1) 
	{
        dx = -1;
        while (dx <= 1) 
		{
            if (!(dx == 0 && dy == 0))
                count += getCell(life->curr, life, x + dx, y + dy);
            dx++;
        }
        dy++;
    }
    return count;
}

static void clear_grid(char *grid, int size) 
{
    int i = 0;
    while (i < size) 
        grid[i++] = 0;
}

static void runIteration(t_life *life) 
{
    int x;
    int y;
    int alive;
    int n;
    char *tmp;
    y = 0;
    while (y < life->height) 
	{
        x = 0;
        while (x < life->width) 
		{
            alive = getCell(life->curr, life, x, y);
            n = countNeighbors(life, x, y);
            if (alive)
                life->next[idx(life, x, y)] = (n == 2 || n == 3);
            else 
                life->next[idx(life, x, y)] = (n == 3);
            x++;
        }
        y++;
    }
    tmp = life->curr;
    life->curr = life->next;
    life->next = tmp;
    clear_grid(life->next, life->height * life->width);
}

void runLife(t_life *life) 
{
    int i = 0;
    while (i < life->iter)
	{
        runIteration(life);
        i++;
    }
}

void readDraw(t_life *life) 
{
    int i;
    ssize_t len;
    int x = 0;
    int y = 0;
    int draw = 0;
    char buf[256];
    while ((len = read(0, buf, sizeof(buf))) > 0)
	{
        i = 0;
        while (i < len) 
		{
            if (buf[i] == 'x')
			{
                draw = !draw;
                if (draw)
                    setActive(life, x, y);
            }
            else if (buf[i] == 'w')
                y--;
            else if (buf[i] == 'a')
                x--;
            else if (buf[i] == 's')
                y++;
            else if (buf[i] == 'd')
                x++;
            if (draw && (buf[i] == 'w' || buf[i] == 'a' || buf[i] == 's' || buf[i] == 'd'))
                setActive(life, x, y);
            i++;
        }
    }
}

void printLife(t_life *life)
{
    int x;
    int y;
    y = 0;
    while (y < life->height)
	{
        x = 0;
        while (x < life->width) 
		{
            if (life->curr[idx(life, x, y)])
                putchar('O');
            else 
                putchar(' ');
            x++;
        }
        putchar('\n');
        y++;
    }
}