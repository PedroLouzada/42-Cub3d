#include "cub3d.h"

void parse_exit(char *s);

void parsing(int ac, char **av)
{
    (void)av;
    if (ac != 2)
        parse_exit("Expected <fileName> <map.cub>\n");
    return ;
}