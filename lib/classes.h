#ifndef CLASSES_H
# define CLASSES_H

# include "cub3d.h"

typedef struct s_player
{
	int		pos_x;
	int 	pos_y;
	int 	lives;
	bool	collision;
	char	orientation;
	void	(*damage)(t_player*);
	void	(*render)(t_player*);
	void	(*move)(t_player*, int, int);
}	t_player;

typedef struct s_enemy
{
	int		pos_x;
	int		pos_y;
	bool	collision;
	void	(*render)(t_enemy*);
	void	(*respawn)(t_enemy*);
	void	(*move)(t_enemy*, int, int);
}	t_enemy;

typedef struct s_wall
{
	bool	door;
	bool 	collision;
	char	orientation;
	void	(*render)(t_wall*);
}	t_wall;

typedef struct s_map
{
	int		width;
	int		length;
	void	(*render)(t_map*);
	void	(*resize)(t_map*, int, int);
}	t_map;

typedef struct s_game
{
	t_map		map;
	t_enemy		enemy;
	t_player	player;
	t_wall		*walls;
	t_map		minimap;
}	t_game;

#endif