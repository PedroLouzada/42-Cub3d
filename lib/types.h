#ifndef TYPES_H
# define TYPES_H

typedef char		*t_str;

typedef struct s_vtr
{
	double			x;
	double			y;
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

typedef struct s_texture
{
	int				tex_x;
	int				tex_y;
	int				txt_id;
	double			tex_step;
	double			tex_pos;
} t_texture;

typedef struct s_ray
{
	t_vtr			dir;
	t_vtr			map;
	t_vtr			step;
	t_vtr			pos;
	int				side;
	double			perp;
	t_vtr			sDist;
	t_vtr			dltDist;
	t_texture		tex;
}					t_ray;

#endif