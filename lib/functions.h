#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "cub3d.h"

//Data
t_game	*game(void);

//Time Utils
void	set_time(long *time);

//Math Utils
int		ft_min(int a, int b);

//Draw Utils
void	draw_tile(t_mlx *mlx, t_vtr tpos, int scale, int color);
void	draw_circle(t_mlx *mlx, t_vtr cpos, int radius, int color);

//Map Utils
void	where_to_next(int *direction);
bool	valid_door(t_map *map, t_vtr pos);
int		in_range(t_vtr range, int x, int y);
int		which_direction(int right, int left);
void	check_path(t_vtr range, t_vtr pos, int *direction);
void	move_in_path(t_vtr range, t_vtr *pos, int direction);

//Rand Utils
void	init_rand(void);
t_vtr	rand_pos(t_vtr range);

//Libft Utils
t_str	ft_joinstr(t_str s1, t_str s2);
void	*ft_calloc(size_t nm, size_t sz);

//Map Methods
void	print_map(t_map *map);
void	destroy_map(t_map *map);
void	generate_map(t_map *map);

//Initializors
t_obj	*create_enemy(void);
t_obj	*create_player(void);
t_map	*create_map(int level);
t_obj	*create_door(t_vtr pos);
void	init_game(int ac, t_str *av);

#endif
