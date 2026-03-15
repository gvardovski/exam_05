#include "bsq.h"

int main(int gc, char **gv)
{
    if (gc < 2)
    {
        if (!procStream(stdin))
            return fputs("map error\n", stderr);
    }
    else
    {
        for(int i = 1; i < gc; i++)
        {
            if(!procFile(gv[i]))
                return fputs("map error\n", stderr);
            if(i + 1 < gc)
                return fputs("\n", stdout);
        }
    }
    return 0;
}