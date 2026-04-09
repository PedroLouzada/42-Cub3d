/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:55:49 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 17:02:30 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_str	get_file(int level)
{
	t_str	files[5];

	files[0] = "maps/level_1";
	files[1] = "maps/level_2";
	files[2] = "maps/level_3";
	files[3] = "maps/level_4";
	files[4] = "maps/level_5";
	return (ft_joinstr(files[level - 1], ".cub"));
}

void	print_map(t_map *map)
{
	t_str	file;
	int		data[3];

	file = get_file(map->level);
	if (!file)
		return (map->destroy(map));
	data[2] = open(file, O_CREAT | O_RDWR | O_TRUNC, PERMISSIONS);
	if (data[2] < 0)
		return (map->destroy(map));
	data[0] = -1;
	while (++data[0] < map->map_size.y)
	{
		data[1] = -1;
		while (++data[1] < map->map_size.x)
			write(data[2], &map->map[data[0]][data[1]], 1);
		write(data[2], "\n", 1);
	}
	close(data[2]);
	free(file);
}

void	generate_objs(t_map *map)
{
	t_vtr	pos;
	int		data[2];

	data[0] = (int)pick_range(MIN_DOORS, MAX_DOORS);
	map->objs = ft_calloc(data[0] + 3, sizeof(t_obj *));
	if (!map->objs)
		return (map->destroy(map));
	data[1] = P;
	while (data[0])
	{
		pos = spawn(map, '0');
		if (!valid_door(map, pos))
			continue ;
		map->objs[++data[1]] = create_door(map, pos);
		if (!map->objs[data[1]])
			return (map->destroy(map));
		data[0]--;
	}
	map->objs[P] = create_player(spawn(map, '0'));
	if (!map->objs[P])
		parse_exit("Memory Allocation\n", NULL, -1, 1);
	map->objs[E] = create_enemy(spawn(map, '0'));
	if (!map->objs[E])
		parse_exit("Memory Allocation\n", (void *)map->objs[P], -1, 1);
}

void	generate_paths(t_map *map, t_vtr pos, int paths)
{
	int	data[2];

	data[0] = 0;
	data[1] = (int)pick_range(NORTH, SOUTH);
	if (!paths)
		return ;
	while (map->map[(int)pos.y][(int)pos.x] != '.')
	{
		map->map[(int)pos.y][(int)pos.x] = '.';
		check_path(map, pos, &data[1]);
		move_in_path(map, &pos, data[1]);
		data[0]++;
		if (data[0] % (int)pick_range(MIN_MOVES, MAX_MOVES) == 0)
			where_to_next(&data[1]);
	}
	generate_paths(map, rand_pos(map->map_size), --paths);
}

void	set_colors(t_map *map)
{
	map->colors[0][1] = 228;
	map->colors[0][2] = 230;
	map->colors[0][3] = 168;
	map->colors[1][1] = 198;
	map->colors[1][2] = 197;
	map->colors[1][3] = 139;
}
