#ifndef CLASSES_H
# define CLASSES_H

# include "cub3d.h"
# include "types.h"

typedef struct s_obj	t_obj;
typedef struct s_map	t_map;
typedef struct s_door	t_door;
typedef struct s_game	t_game;
typedef struct s_enemy	t_enemy;
typedef struct s_player	t_player;

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
	char 		direction; // necessario?
	void		(*damage)(t_obj *this);
	void		(*update)(t_obj *this);
	bool		(*collision)(t_obj *this, t_obj *target);
	void 		*(*get_texture)(t_obj *this, char direction);
	t_vtr		dir; // oq e isso
	t_vtr		plane;
	double		fov;
	void		(*rotate)(t_player *player, double angle);
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
	t_ray		*rays;
	int			level;
	t_obj		**objs;
	t_vtr		map_size;
	t_vtr		mini_size;
	t_vtr		player_pos;
	char		direction;
	void 		*colors[2];
	void 		*textures[4];
	void		(*clean)(t_map*);
	void		(*minimap)(t_map*);
	void		(*destroy)(t_map*);
};

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_imgs		*img;
}	t_mlx;

typedef struct s_eng
{
	bool	title[2];
	bool	key[80000];
	int		in_button[4];
} t_eng;

struct s_game
{
	t_mlx		*mlx;
	t_map		*map[6];
	t_eng		*eng;
};

#endif