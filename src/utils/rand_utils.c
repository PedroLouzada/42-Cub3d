/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:11:34 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 18:51:38 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_rand(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return ;
	srand(time.tv_sec ^ time.tv_usec);
}

t_vtr	rand_pos(t_vtr range)
{
	t_vtr	pos;
	double	data[3];

	data[0] = 1;
	data[1] = range.x - 2;
	data[2] = range.y - 2;
	pos.x = floor(pick_range(data[0], data[1]));
	pos.y = floor(pick_range(data[0], data[2]));
	return (pos);
}

void	where_to_next(int *direction)
{
	int	where_to;

	where_to = pick_range(NORTH, SOUTH);
	if (*direction == NORTH && where_to == SOUTH)
		where_to = which_direction(EAST, WEST, 0);
	else if (*direction == EAST && where_to == WEST)
		where_to = which_direction(SOUTH, NORTH, 0);
	else if (*direction == WEST && where_to == EAST)
		where_to = which_direction(SOUTH, NORTH, 0);
	else if (*direction == SOUTH && where_to == NORTH)
		where_to = which_direction(EAST, WEST, 0);
	*direction = where_to;
}

double	pick_rand(double a, double b)
{
	double	pick;

	pick = rand() % 2;
	if (pick)
		return (a);
	return (b);
}

double	pick_range(double min, double max)
{
	return (min + ((double)rand() / RAND_MAX) * (max - min));
}
