#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "cub3d.h"

//Time Utils
void	set_time(long *time);

//Map Utils
void	where_to_next(int *direction);
int		which_direction(int right, int left);
int		in_range(t_vtr range, int x, int y);
void	check_path(t_vtr range, t_vtr pos, int *direction);

//Rand Utils
void	init_rand(void);
t_vtr	rand_pos(t_vtr range);

//Libft Utils
t_str	ft_joinstr(t_str s1, t_str s2);
void	*ft_calloc(size_t nm, size_t sz);

//Map Methods
void    render_map(t_map *map);
void	print_map(t_map *map, int level);
void	destroy_map(t_map *map, int level);
void	generate_map(t_map *map, int level);

//Create Objects
t_map	*create_map(void);

#endif
