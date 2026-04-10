/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:11:53 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/10 16:49:49 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec + time.tv_usec / 1000000.0);
}

bool	in_bounds(char **map, int y, int x)
{
	int	len;

	if (!map || y < 0 || x < 0 || !map[y])
		return (false);
	len = ft_strlen(map[y]);
	if (x >= len)
		return (false);
	return (true);
}
