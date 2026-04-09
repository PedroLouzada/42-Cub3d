/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:11:23 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 18:50:17 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vtr	spawn(t_map *map, char tile)
{
	t_vtr	pos;

	pos = rand_pos(map->map_size);
	while (map->map[(int)pos.y] && map->map[(int)pos.y][(int)pos.x] != tile)
		pos = rand_pos(map->map_size);
	pos.x = floor(pos.x) + 0.3;
	pos.y = floor(pos.y) + 0.3;
	return (pos);
}

void	check_map(t_map *map, int x, int y)
{
	if (map->map[y][x] == '1' || map->map[y][x] == '0')
		return ;
	map->map[y][x] = '0';
	check_map(map, x + 1, y);
	check_map(map, x - 1, y);
	check_map(map, x, y + 1);
	check_map(map, x, y - 1);
}

bool	valid_map(t_map *map)
{
	t_vtr	pos;

	pos.y = -1;
	while (map->map[(int)++pos.y])
	{
		pos.x = -1;
		while (map->map[(int)pos.y][(int)++pos.x])
		{
			if (map->map[(int)pos.y][(int)pos.x] == '.')
				return (false);
		}
	}
	return (true);
}

static bool	valid_exit(char **map, int x, int y)
{
	if (is_floor(map[y][x + 1]) || is_floor(map[y][x - 1]))
	{
		if (is_floor(map[y + 1][x]) || is_floor(map[y - 1][x]))
			return (false);
		return (true);
	}
	else if (is_floor(map[y + 1][x]) || is_floor(map[y - 1][x]))
	{
		if (is_floor(map[y][x + 1]) || is_floor(map[y][x + 1]))
			return (false);
		return (true);
	}
	return (false);
}

void	set_exit(t_map *map)
{
	t_vtr	pos;

	pos = spawn(map, '1');
	while (!valid_exit(map->map, (int)pos.x, (int)pos.y))
		pos = spawn(map, '1');
	map->map[(int)pos.y][(int)pos.x] = 'L';
}
