#include "bsq.h"

int main(int argc, char **argv)
{
    if (argc < 2) 
	{
        if (!process_stream(stdin))
            fputs("map error\n", stderr);
    } 
	else 
	{
        for (int i = 1; i < argc; i++)
		{
            if (!process_file(argv[i]))
                fputs("map error\n", stderr);
            if (i + 1 < argc)
                fputs("\n", stdout);
        }
    }
    return 0;
}