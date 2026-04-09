/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:57:12 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 17:08:24 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_obj	*create_door(t_map *map, t_vtr pos)
{
	t_door	*door;

	door = ft_calloc(1, sizeof(t_door));
	if (!door)
		return (NULL);
	door->pos = pos;
	map->map[(int)pos.y][(int)pos.x] = 'D';
	return ((t_obj *)door);
}

static bool	check_horizontal(char **map, int x, int y)
{
	if (is_wall(map[y + 1][x]) && is_wall(map[y - 1][x]) && is_floor(map[y][x
			+ 1]) && is_floor(map[y][x - 1]))
		return (true);
	return (false);
}

static bool	check_vertical(char **map, int x, int y)
{
	if (is_wall(map[y][x + 1]) && is_wall(map[y][x - 1]) && is_floor(map[y
			+ 1][x]) && is_floor(map[y - 1][x]))
		return (true);
	return (false);
}

static bool	check_hallway(char **map, int x, int y)
{
	bool	ver;
	bool	hor;

	ver = check_vertical(map, x, y);
	hor = check_horizontal(map, x, y);
	return (ver || hor);
}

bool	valid_door(t_map *map, t_vtr pos)
{
	int		i;
	int		x;
	int		y;
	t_str	*cmap;

	if (!map || !map->map || !map->objs)
		return (false);
	cmap = map->map;
	x = (int)pos.x;
	y = (int)pos.y;
	if (!in_range(map, x, y))
		return (false);
	if (!in_range(map, x + 2, y) || !in_range(map, x - 2, y)
		|| !in_range(map, x, y + 2) || !in_range(map, x, y - 2))
		return (false);
	if (cmap[y][x] != '0' || !check_hallway(cmap, x, y))
		return (false);
	i = -1;
	while (map->objs[++i])
	{
		if (map->objs[i]->pos.x == pos.x && map->objs[i]->pos.y == pos.y)
			return (false);
	}
	return (true);
}
