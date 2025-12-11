#ifndef DEFINES_H
# define DEFINES_H

# include "cub3d.h"


typedef enum e_direct {
    NORTH = 1,
    EAST = 2,
    WEST  = 3,
    SOUTH = 4
} t_direct;

# define MAP_WIDTH 100
# define MAP_HEIGHT 40
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TITLE "||BACKROOMS | CUB3D||"
# define MLX_ERR "Error on mlx initialization\n"

#endif