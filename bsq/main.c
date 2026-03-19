#include "bsq.h"

int main(int gc, char **gv)
{
    if (gc < 2)
    {
        if (!procStream(stdin))
        {
            fputs("map error\n", stderr);
            return 1;
        }
        return 0;
    }
    int has_error = 0;
    for (int i = 1; i < gc; i++)
    {
        if (!procFile(gv[i]))
        {
            fputs("map error\n", stderr);
            has_error = 1;
        }
        if (i + 1 < gc)
            fputs("\n", stdout);
    }
    if (has_error)
        return 1;
    return 0;
}