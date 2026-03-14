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
typedef struct s_thread	t_thread;

struct					s_obj
{
	t_vtr				pos;
	int					lives;
	char				direction;
	t_vtr				dir;
	t_vtr				plane;
	double				angle;
	void				(*damage)(t_obj *this);
	void				(*update)(t_obj *this, t_map *map);
	bool				(*collision)(t_obj *this, t_obj *target);
	void				*(*get_texture)(t_obj *this, double dir);
};

struct					s_player
{
	t_vtr				pos;
	int					lives;
	char direction; // necessario?
	t_vtr				dir;
	t_vtr				plane;
	double				angle;
	void				(*damage)(t_obj *this);
	void				(*update)(t_obj *this, t_map *map);
	bool				(*collision)(t_obj *this, t_obj *target);
	void				*(*get_texture)(t_obj *this, double dir);
	double				battery;
	t_ray				*ray;
	int					level;
	double				stamina;
};

struct					s_enemy
{
	t_vtr				pos;
	int					lives;
	char				direction;
	t_vtr				dir;
	t_vtr				plane;
	double				angle;
	void				(*damage)(t_obj *this);
	void				(*update)(t_obj *this, t_map *map);
	bool				(*collision)(t_obj *this, t_obj *target);
	void				*(*get_texture)(t_obj *this, double dir);
};

struct					s_door
{
	t_vtr				pos;
	int					lives;
	char				direction;
	t_vtr				dir;
	t_vtr				plane;
	double				angle;
	void				(*damage)(t_obj *this);
	void				(*update)(t_obj *this, t_map *map);
	bool				(*collision)(t_obj *this, t_obj *target);
	void				*(*get_texture)(t_obj *this, double dir);
};

struct					s_map
{
	int					level;
	t_str				*map;
	t_obj				**objs;
	t_imgs *player; // temporario
	t_ray				*rays[2];
	t_vtr				map_size;
	t_vtr				mini_size;
	char				direction;
	t_vtr				player_pos;
	void				*colors[2];
	t_imgs				*textures[4];
	void				(*clean)(t_map *);
	void				(*minimap)(t_map *);
	void				(*destroy)(t_map *);
	t_imgs				*door;
};

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	t_imgs				**img;
}						t_mlx;

typedef struct s_eng
{
	double				dt;
	bool				screen[3];
	bool				key[80000];
	int					in_button[4];
	int					current_map;
	int					battery;
	t_thread			*pool;
}						t_eng;

struct					s_game
{
	t_mlx				*mlx;
	t_map				*map[6];
	t_eng				eng;
};

#endif