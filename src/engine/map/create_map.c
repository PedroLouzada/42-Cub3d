/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:55:22 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 17:02:44 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	generate_map(t_map *map)
{
	t_vtr	pos;

	map->map = ft_calloc(map->map_size.y + 1, sizeof(t_str));
	if (!map->map)
		exit_game(ALLOC_ERR);
	pos.x = -1;
	while (++pos.x < map->map_size.y)
	{
		map->map[(int)pos.x] = ft_calloc(map->map_size.x + 1, 1);
		if (!map->map[(int)pos.x])
			exit_game(ALLOC_ERR);
		pos.y = -1;
		while (++pos.y < map->map_size.x)
			map->map[(int)pos.x][(int)pos.y] = '1';
	}
	generate_paths(map, rand_pos(map->map_size), pick_range(MIN_P, MAX_P));
	pos = spawn(map, '.');
	check_map(map, pos.x, pos.y);
	if (!valid_map(map))
		return (map->clean(map), generate_map(map));
	generate_objs(map);
	set_exit(map);
	set_colors(map);
}

void	alloc_textures(t_map *map)
{
	int		i;
	bool	index;
	t_imgs	*texture;

	i = -1;
	index = false;
	while (++i < 4)
	{
		if (!index)
			texture = new_img("./assets/textures/green_wall/wall1.xpm");
		else
			texture = new_img("./assets/textures/green_wall/wall2.xpm");
		if (!texture)
			exit_game(ALLOC_ERR);
		index = !index;
		map->textures[i] = texture;
	}
	map->door = new_img("./assets/textures/green_wall/door.xpm");
	if (!map->door)
		exit_game(ALLOC_ERR);
}

t_map	*create_map(int level, int fd)
{
	t_map *const	map = ft_calloc(1, sizeof(t_map));

	if (!map)
		parse_exit("Memory Allocation\n", NULL, fd, 0);
	map->level = level;
	map->clean = clean_map;
	map->destroy = destroy_map;
	map->minimap = draw_minimap;
	map->map_size.x = MAP_WIDTH;
	map->map_size.y = MAP_HEIGHT;
	if (level)
	{
		generate_map(map);
		print_map(map);
		alloc_textures(map);
	}
	return (map);
}
