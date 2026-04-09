/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_view.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:10:21 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 19:12:55 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	e_can_walk(t_map *map, t_vtr pos)
{
	int	x;
	int	y;
	int	width;
	int	height;

	x = (int)pos.x;
	y = (int)pos.y;
	width = (int)map->map_size.x;
	height = (int)map->map_size.y;
	if (x < 0 || y < 0 || x >= width || y >= height)
		return (false);
	return (map->map[y][x] == '0' || map->map[y][x] == 'd');
}

bool	e_hits_player(t_enemy *e, t_player *p)
{
	t_vtr	diff;

	diff.x = e->pos.x - p->pos.x;
	diff.y = e->pos.y - p->pos.y;
	if (diff.x * diff.x + diff.y * diff.y <= RADIUS * RADIUS)
		return (true);
	return (false);
}

bool	e_sees_p(t_vtr pos, t_map *map, bool memory)
{
	t_enemy		*e;
	t_player	*p;
	t_vtr		diff;

	e = (t_enemy *)map->objs[E];
	p = (t_player *)map->objs[P];
	if (((int)pos.x == (int)p->pos.x && (int)pos.y == (int)p->pos.y) || memory)
	{
		diff.x = p->pos.x - e->pos.x;
		diff.y = p->pos.y - e->pos.y;
		e->chase = true;
		e->angle = atan2(diff.y, diff.x);
		set_e_orientation(e);
		return (true);
	}
	return (false);
}

void	e_dda(t_ray *r, t_map *map)
{
	while (1)
	{
		if (r->s_dist.x < r->s_dist.y)
		{
			r->s_dist.x += r->dlt_dist.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->s_dist.y += r->dlt_dist.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if (e_sees_p(r->map, map, false))
			return ;
		if (!in_range(map, (int)r->map.x, (int)r->map.y)
			|| is_wall(map->map[(int)r->map.y][(int)r->map.x]))
			return ;
	}
}

void	enemy_los(t_enemy *e, t_map *map)
{
	int		i;
	bool	had_los;

	had_los = e->chase;
	e->chase = false;
	i = -1;
	while (++i < WIN_WIDTH)
	{
		init_ray(&e->ray[i], (t_obj *)e, i);
		e_dda(&e->ray[i], map);
		e->ray[i].perp = get_perp(e->ray[i]);
	}
	if (had_los && e_timer(false, MEMORY) < 8.0)
		e_sees_p(e->pos, map, true);
	else if (had_los)
		e_timer(true, MEMORY);
}
