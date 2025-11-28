#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <curses.h>
# include "classes.h"
# include <sys/time.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

//========================== PARSING =====================

void    parsing(int ac, char **av);

//=========================== UTILS ======================

int     ft_strlen(char *s);

#endif