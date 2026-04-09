/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:05:42 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 19:07:23 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_vtr				dir;
	int					lives;
	t_vtr				plane;
	double				angle;
	void				(*damage)(t_obj *this);
	void				*(*get_texture)(t_obj *this, double dir);
};

struct					s_player
{
	t_vtr				pos;
	t_vtr				dir;
	int					lives;
	t_vtr				plane;
	double				angle;
	void				(*damage)(t_obj *this);
	void				*(*get_texture)(t_obj *this, double dir);
	void				(*update)(t_obj *this, t_map *map);
	double				battery;
	t_ray				*ray;
	int					level;
	double				stamina;
};

struct					s_enemy
{
	t_vtr				pos;
	t_vtr				dir;
	int					lives;
	t_vtr				plane;
	double				angle;
	void				(*damage)(t_obj *this);
	void				*(*get_texture)(t_obj *this, double dir);
	void				(*update)(t_obj *this, t_map *map);
	t_imgs				*textures[6];
	t_ray				*ray;
	bool				chase;
	int					frame;
};

struct					s_door
{
	t_vtr				pos;
	t_vtr				dir;
	int					lives;
	t_vtr				plane;
	double				angle;
	void				(*damage)(t_obj *this);
	void				*(*get_texture)(t_obj *this, double dir);
};

struct					s_map
{
	t_str				*map;
	t_imgs				*door;
	int					level;
	t_obj				**objs;
	t_imgs				*player;
	t_vtr				map_size;
	t_vtr				mini_size;
	char				direction;
	int					colors[2][4];
	t_imgs				*textures[4];
	void				(*clean)(t_map *);
	void				(*minimap)(t_map *);
	void				(*destroy)(t_map *);
	double				zbuffer[WIN_WIDTH];
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
	bool				door;
	t_thread			*pool;
}						t_eng;

struct					s_game
{
	t_mlx				*mlx;
	t_map				*map[6];
	t_eng				eng;
};

#endif
