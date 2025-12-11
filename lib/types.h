#ifndef TYPES_H
# define TYPES_H

# include "cub3d.h"

typedef char	*t_str;

typedef struct s_vtr
{
	int			x;
	int			y;
}				t_vtr;

typedef struct s_imgs
{
	void		*img;
	char		*addr;
	int			bpp;
	int			sline;
	int			endian;
	int 		width;
	int 		height;
}				t_imgs;

#endif