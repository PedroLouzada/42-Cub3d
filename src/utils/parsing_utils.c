#include "cub3d.h"

void parse_exit(char *s)
{
    int len;

    len = ft_strlen(s);
    write(2, "Error\n", 6);
    write (2, s, len);
    exit (1);
}