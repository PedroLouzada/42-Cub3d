#ifndef CLASSES_H
# define CLASSES_H

# include "cub3d.h"

typedef struct s_map	t_map;
typedef struct s_wall	t_door;
typedef struct s_game	t_game;
typedef struct s_enemy	t_enemy;
typedef struct s_player	t_player;
typedef struct s_obj	t_obj;

struct s_obj
{
	t_vtr		pos;
	int 		lives;
	char 		direction;
	void		(*damage)(t_obj *this);
	void		(*update)(t_obj *this);
	bool		(*collision)(t_obj *this, t_obj *target);
	void 		*(*get_texture)(t_obj *this, char direction);	
	
};

struct s_player
{
	t_vtr		pos;
	int 		lives;
	char 		direction;
	void		(*damage)(t_obj *this);
	void		(*update)(t_obj *this);
	bool		(*collision)(t_obj *this, t_obj *target);
	void 		*(*get_texture)(t_obj *this, char direction);
};

struct s_enemy
{
	t_vtr		pos;
	int 		lives;
	char 		direction;
	void		(*damage)(t_obj *this);
	void		(*update)(t_obj *this);
	bool		(*collision)(t_obj *this, t_obj *target);
	void 		*(*get_texture)(t_obj *this, char direction);
};

struct s_door
{
	t_vtr		pos;
	int 		lives;
	char 		direction;
	void		(*damage)(t_obj *this);
	void		(*update)(t_obj *this);
	bool		(*collision)(t_obj *this, t_obj *target);
	void 		*(*get_texture)(t_obj *this, char direction);
};

struct s_map
{
	t_str		*map;
	t_map		*next;
	t_vtr		map_size;
	t_vtr		mini_size;
	void 		*colors[2];
	void 		*textures[4];
	void		(*print)(t_map*, int);
	void		(*destroy)(t_map*, int);
	void		(*generate)(t_map*, int);
};

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

struct s_game
{
	t_mlx		*mlx;
	t_map		*map;
	t_obj		*objs;
	void		(*run)(t_game*);
	void		(*parsing)(t_game*, int, char**);
};

t_game *game_init();

#endif