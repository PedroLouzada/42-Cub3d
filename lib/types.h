#ifndef TYPES_H
# define TYPES_H

typedef char		*t_str;

typedef struct s_vtr
{
	int				x;
	int				y;
}					t_vtr;

typedef struct s_imgs
{
	int				index;
	void			*img;
	char			*addr;
	int				bpp;
	int				sline;
	int				endian;
	int				width;
	int				height;
	struct s_imgs	*next;
}					t_imgs;

#endif