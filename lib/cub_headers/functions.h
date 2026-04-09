/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 19:06:11 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 21:31:49 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "cub3d.h"
# include "types.h"

// Player Movement
void	set_p_orientation(t_player *p);
void	p_rotate(t_eng *eng, t_player *p);
void	p_walk(t_eng *eng, t_player *p, t_map *map);

// Enemy Movement
void	set_e_orientation(t_enemy *e);
double	e_timer(bool reset, int timer);
void	e_walk(t_enemy *e, t_map *map);
void	e_chase(t_enemy *e, t_map *map);
void	e_rotate(t_enemy *e, double speed);
void	*enemy_get_texture(t_obj *this, double dir);
bool	e_is_stuck(t_enemy *e, t_vtr prev, double prev_angle);
void	attack_player(t_enemy *e, t_map *map, t_vtr prev, double prev_angle);

// Enemy View
bool	e_can_walk(t_map *map, t_vtr pos);
void	enemy_los(t_enemy *e, t_map *map);
bool	e_hits_player(t_enemy *e, t_player *p);

// Raycasting
double	get_perp(t_ray r);
void	cast_rays(int map);
void	dda(t_ray *r, t_map *map, bool door);
void	init_ray(t_ray *r, t_obj *obj, int column);

// Data
t_game	*game(void);

// Time Utils
double	get_time(void);

// Math Utils
double	ft_min(double a, double b);
void	round_vtrs(t_vtr *a, t_vtr *b);

// Draw Utils
void	titlescreen(void);
void	control_screen(void);
int		texture_dir(t_ray *r);
void	draw_screen(t_mlx *mlx);
void	draw_fov(t_ray *r, t_vtr pos);
int		tile_color(t_map *map, t_vtr pos);
int		get_shade(double dist, int color);
void	draw_img(t_imgs *img, int px, int py);
int		ft_get_color(t_imgs *img, int x, int y);
void	draw_line(t_vtr start, t_vtr end, int color);
void	draw_tile(t_mlx *mlx, t_vtr tpos, int color);
void	draw_column(t_ray *r, int column, t_map *map);
void	ft_pixel_put(t_imgs *img, int x, int y, int color);
void	draw_flashlight(t_vtr size, int radius, bool minimap);
void	draw_circle(t_mlx *mlx, t_vtr cpos, int radius, int color);
void	draw_enemy_sprite(t_enemy *e, t_vtr s_pos, t_imgs *spr, t_map *map);
int		darken_color(double distance, double radius, int color, bool minimap);

// Map Utils
void	set_exit(t_map *map);
bool	valid_map(t_map *map);
void	set_colors(t_map *map);
void	generate_objs(t_map *map);
t_vtr	spawn(t_map *map, char tile);
void	where_to_next(int *direction);
bool	valid_door(t_map *map, t_vtr pos);
bool	in_range(t_map *map, int x, int y);
void	check_map(t_map *map, int x, int y);
void	interact_door(t_map *map, t_player *p);
int		which_direction(int right, int left, int back);
void	generate_paths(t_map *map, t_vtr pos, int paths);
void	check_path(t_map *map, t_vtr pos, int *direction);
void	move_in_path(t_map *map, t_vtr *pos, int direction);

// Rand Utils
void	init_rand(void);
t_vtr	rand_pos(t_vtr range);
double	pick_rand(double a, double b);
double	pick_range(double min, double max);

// Libft Utils
int		ft_isempty(char c);
int		ft_strlen(char *s);
char	*get_next_line(int fd);
char	**ft_split(char *s, char c);
char	*ft_strrchr(char *str, int c);
t_str	ft_joinstr(t_str s1, t_str s2);
void	*ft_calloc(size_t nm, size_t sz);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strdup_newline(char *s);

// Map Methods
void	clean_map(t_map *map);
void	print_map(t_map *map);
void	destroy_map(t_map *map);
void	draw_minimap(t_map *map);
void	generate_map(t_map *map);

// Initializors
void	alloc_assets(void);
t_imgs	*new_img(char *name);
t_obj	*create_enemy(t_vtr pos);
t_obj	*create_player(t_vtr pos);
void	init_game(int ac, t_str *av);
t_map	*create_map(int level, int fd);
t_obj	*create_door(t_map *map, t_vtr pos);

// Key/Mouse Handlers
int		key_press(int key);
int		key_unpress(int key);
int		mouse_move(int x, int y);
int		mouse_press(int button, int x, int y);

//Map Checks
bool	is_wall(char c);
bool	is_floor(char c);
int		get_pos(int *pos, char **map);

//Parsing
void	parsing(char **av);

//Exit
int		exit_game(t_str message);
void	parse_exit(char *s, char *arg, int fd, bool map);

//Free
void	free_double(char **str);

#endif
