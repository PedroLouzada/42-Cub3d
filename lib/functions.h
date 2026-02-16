#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "cub3d.h"
# include "types.h"

//Raycasting
void	cast_rays(t_map *map, t_player *p);

//Data
t_game	*game(void);

//Time Utils
void	set_time(long *time);

//Math Utils
int		ft_min(int a, int b);
void	round_vtrs(t_vtr *a, t_vtr *b);

//Draw Utils
void	draw_fov(t_map *map, t_player *p);
void	draw_line(t_vtr start, t_vtr end);
void	draw_column(t_ray *r, int column);
void	ft_pixel_put(t_imgs *img, int x, int y, int color);
void	draw_tile(t_mlx *mlx, t_vtr tpos, int scale, int color);
void	draw_circle(t_mlx *mlx, t_vtr cpos, int radius, int color);

//Map Utils
void	set_exit(t_map *map);
bool	valid_map(t_map *map);
t_vtr	spawn(t_map *map, char tile);
void	where_to_next(int *direction);
bool	valid_door(t_map *map, t_vtr pos);
int		in_range(t_map *map, int x, int y);
void	check_map(t_map *map, int x, int y);
int		which_direction(int right, int left, int back);
void	check_path(t_map *map, t_vtr pos, int *direction);
void	move_in_path(t_map *map, t_vtr *pos, int direction);

//Rand Utils
void	init_rand(void);
t_vtr	rand_pos(t_vtr range);
int		pick_rand(int a, int b);
double	pick_range(double min, double max);

//Libft Utils
t_str	ft_joinstr(t_str s1, t_str s2);
void	*ft_calloc(size_t nm, size_t sz);

//Map Methods
void	clean_map(t_map *map);
void	print_map(t_map *map);
void	destroy_map(t_map *map);
void	generate_map(t_map *map, int level);

//Initializors
t_map	*create_map(int level, int fd);
t_obj	*create_door(t_vtr pos);
t_obj	*create_enemy(t_vtr pos);
t_obj	*create_player(t_vtr pos, int level);
void	init_game(int ac, t_str *av);


int     mouse_press(int button, int x, int y, void *arg);
int     exit_game(char *str);
void	clear_image(void);
int     mouse_move(int x, int y, void *arg);
void    draw_screen(t_mlx *mlx);
void	alloc_assets(void);
t_imgs	*new_img(char *name);
int key_press(int key);
int key_unpress(int key);
void	draw_minimap(t_map *map);
int	get_pos(int *pos, char **map, int entity);
unsigned long	get_time(void);
t_vtr	get_dir(int orientation);

#endif
