/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:11:20 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/07 19:37:21 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	in_range(t_map *map, int x, int y)
{
	if (x < 1 || x > map->map_size.x - 2)
		return (false);
	if (y < 1 || y > map->map_size.y - 2)
		return (false);
	return (true);
}

int	which_direction(int right, int left, int back)
{
	int	which_direction;

	if (back)
		which_direction = rand() % 3;
	else
		which_direction = rand() % 2;
	if (which_direction == 0)
		return (right);
	else if (which_direction == 1)
		return (left);
	else if (which_direction == 2)
		return (back);
	return (-1);
}

void	check_path(t_map *map, t_vtr pos, int *direction)
{
	if (*direction == NORTH && !in_range(map, pos.x, pos.y + 1))
		*direction = which_direction(EAST, WEST, SOUTH);
	if (*direction == SOUTH && !in_range(map, pos.x, pos.y - 1))
		*direction = which_direction(EAST, WEST, NORTH);
	if (*direction == EAST && !in_range(map, pos.x + 1, pos.y))
		*direction = which_direction(SOUTH, NORTH, WEST);
	if (*direction == WEST && !in_range(map, pos.x - 1, pos.y))
		*direction = which_direction(SOUTH, NORTH, EAST);
}

void	move_in_path(t_map *map, t_vtr *pos, int direction)
{
	if (direction == NORTH && in_range(map, pos->x, pos->y + 1))
		pos->y++;
	if (direction == EAST && in_range(map, pos->x + 1, pos->y))
		pos->x++;
	if (direction == WEST && in_range(map, pos->x - 1, pos->y))
		pos->x--;
	if (direction == SOUTH && in_range(map, pos->x, pos->y - 1))
		pos->y--;
}
