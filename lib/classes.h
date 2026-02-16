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
	void		(*update)(t_obj *this, t_map *map);
	bool		(*collision)(t_obj *this, t_obj *target);
	void 		*(*get_texture)(t_obj *this, double dir);	
	
};

struct s_player
{
	t_vtr		pos;
	int 		lives;
	char 		direction; // necessario?
	void		(*damage)(t_obj *this);
	void		(*update)(t_obj *this, t_map *map);
	bool		(*collision)(t_obj *this, t_obj *target);
	void 		*(*get_texture)(t_obj *this, double dir);
	t_vtr		dir;
	t_vtr		plane;
	double		angle;
	void		(*rotate)(t_player *player, double angle);
};

struct s_enemy
{
	t_vtr		pos;
	int 		lives;
	char 		direction;
	void		(*damage)(t_obj *this);
	void		(*update)(t_obj *this, t_map *map);
	bool		(*collision)(t_obj *this, t_obj *target);
	void 		*(*get_texture)(t_obj *this, double dir);
	double 		angle;
};

struct s_door
{
	t_vtr		pos;
	int 		lives;
	char 		direction;
	void		(*damage)(t_obj *this);
	void		(*update)(t_obj *this, t_map *map);
	bool		(*collision)(t_obj *this, t_obj *target);
	void 		*(*get_texture)(t_obj *this, double dir);
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
	double		zbuffer[WIN_WIDTH];
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