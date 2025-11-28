#ifndef CLASSES_H
# define CLASSES_H

# include "cub3d.h"

typedef struct s_player t_player;
typedef struct s_enemy t_enemy;
typedef struct s_wall t_wall;
typedef struct s_map t_map;


struct s_player
{
	int			pos_x;
	int			pos_y;
	int			lives;
	bool		collision;
	char		orientation;
	void		(*move)(t_player);
	void		(*damage)(t_player);
	void		(*render)(t_player);
} ;

struct s_enemy
{
	int			pos_x;
	int			pos_y;
	bool		collision;
	void		(*move)(t_enemy);
	void		(*render)(t_enemy);
	void		(*respawn)(t_enemy);
} ;

struct s_wall
{
	bool		door;
	bool		collision;
	char		orientation;
	void		(*render)(t_wall);
} ;

struct s_map
{
	int			width;
	int			length;
	void		(*resize)(t_map);
	void		(*render)(t_map);
} ;

typedef struct s_game
{
	t_map		map;
	t_enemy		enemy;
	t_player	player;
	t_wall		*walls;
	t_map		minimap;
}				t_game;

#endif