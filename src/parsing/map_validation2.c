/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:45:00 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 18:28:04 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_map(t_map *src)
{
	int		i;
	char	**copy;

	i = -1;
	copy = ft_calloc(src->map_size.y + 1, sizeof(char *));
	if (!copy)
		parse_exit("Memory Allocation\n", NULL, -1, 1);
	while (src->map[++i])
	{
		copy[i] = ft_strdup_newline(src->map[i]);
		if (!copy[i])
		{
			free_double(copy);
			parse_exit("Memory Allocation\n", NULL, -1, 1);
		}
	}
	copy[i] = NULL;
	return (copy);
}

int	get_pos(int *pos, char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				pos[0] = j;
				pos[1] = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	flood_fill(char **map, int x, int y, int *pos)
{
	if (!map || !map[y] || !map[y][x] || map[y][x] == ' ' || map[y][x] == '\n')
	{
		free_double(map);
		parse_exit("Map must be closed by walls \'1\'\n", NULL, -1, 1);
	}
	if (map[y][x] == '.' || map[y][x] == '1')
		return ;
	map[y][x] = '.';
	flood_fill(map, x + 1, y, pos);
	flood_fill(map, x - 1, y, pos);
	flood_fill(map, x, y + 1, pos);
	flood_fill(map, x, y - 1, pos);
	if (get_pos(pos, map))
		flood_fill(map, pos[0], pos[1], pos);
}
