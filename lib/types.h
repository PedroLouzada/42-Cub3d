#ifndef TYPES_H
# define TYPES_H

typedef char		*t_str;

typedef struct s_vtr
{
	double		x;
	double		y;
}				t_vtr;

typedef struct s_imgs
{
	void			*img;
	char			*addr;
	int				bpp;
	int				sline;
	int				endian;
	int				width;
	int				height;
}					t_imgs;

typedef struct s_ray
{
	t_vtr		dir;
	t_vtr		map;
	t_vtr		step;
	int			side;
	double		perp;
	t_vtr		sDist;
	t_vtr		dltDist;
}				t_ray;


#endif