/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:55:29 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 16:57:48 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_objs(t_map *m)
{
	int			i;
	t_player	*p;
	t_enemy		*e;

	if (m->objs)
	{
		p = (t_player *)m->objs[P];
		e = (t_enemy *)m->objs[E];
		free(p->ray);
		if (m->level > 0)
			free(e->ray);
		i = -1;
		while (m->objs[++i])
			free(m->objs[i]);
		free(m->objs);
	}
}

void	destroy_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->map_size.y)
	{
		if (map->map && map->map[i])
			free(map->map[i]);
	}
	if (map->map)
		free(map->map);
	free_objs(map);
	if (map)
		free(map);
}

void	clean_map(t_map *map)
{
	int	i;

	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
}
