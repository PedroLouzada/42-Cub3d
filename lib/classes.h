#ifndef CLASSES_H
# define CLASSES_H

# include "cub3d.h"

typedef struct s_map	t_map;
typedef struct s_wall	t_wall;
typedef struct s_game	t_game;
typedef struct s_enemy	t_enemy;
typedef struct s_player	t_player;

typedef struct s_mlx
{
	int			bpp;
	void		*mlx;
	void		*win;
	void		*img;
	t_str		data;
	int			endn;
	int			sline;
}	t_mlx;

struct s_player
{
	int			pos_x;
	int 		pos_y;
	int 		lives;
	bool		collision;
	char		orientation;
	void		(*damage)(t_player*);
	void		(*render)(t_player*);
	void		(*move)(t_player*, int, int);
};

struct s_enemy
{
	int			pos_x;
	int			pos_y;
	bool		collision;
	void		(*render)(t_enemy*);
	void		(*respawn)(t_enemy*);
	void		(*move)(t_enemy*, t_vtr);
};

struct s_wall
{
	bool		door;
	bool 		collision;
	char		orientation;
	void		(*render)(t_wall*);
};

struct s_map
{
	t_mlx		*mlx;
	t_str		*map;
	t_vtr		size;
	void		(*print)(t_map*);
	void		(*render)(t_map*);
	void		(*destroy)(t_map*);
	void		(*generate)(t_map*);
	void		(*resize)(t_map*, t_vtr);
};

struct s_game
{
	t_map		map;
	t_enemy		enemy;
	t_player	player;
	t_wall		*walls;
	t_map		minimap;
};

#endif