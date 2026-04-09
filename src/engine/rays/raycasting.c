/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:55:58 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 19:12:34 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_perp(t_ray r)
{
	if (!r.side)
		return (r.s_dist.x - r.dlt_dist.x);
	else
		return (r.s_dist.y - r.dlt_dist.y);
}

void	init_ray(t_ray *r, t_obj *obj, int column)
{
	double	camera_x;

	camera_x = 2.0 * column / (double)WIN_WIDTH - 1.0;
	r->dir.x = obj->dir.x + obj->plane.x * camera_x;
	r->dir.y = obj->dir.y + obj->plane.y * camera_x;
	r->map.x = floor(obj->pos.x);
	r->map.y = floor(obj->pos.y);
	r->pos = obj->pos;
	r->dlt_dist.x = fabs(1 / r->dir.x);
	r->dlt_dist.y = fabs(1 / r->dir.y);
	r->step.x = (r->dir.x > 0) - (r->dir.x < 0);
	r->step.y = (r->dir.y > 0) - (r->dir.y < 0);
	if (r->dir.x < 0)
		r->s_dist.x = (obj->pos.x - r->map.x) * r->dlt_dist.x;
	else
		r->s_dist.x = (r->map.x + 1.0 - obj->pos.x) * r->dlt_dist.x;
	if (r->dir.y < 0)
		r->s_dist.y = (obj->pos.y - r->map.y) * r->dlt_dist.y;
	else
		r->s_dist.y = (r->map.y + 1.0 - obj->pos.y) * r->dlt_dist.y;
}

void	dda(t_ray *r, t_map *map, bool door)
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
		if (!in_range(map, (int)r->map.x, (int)r->map.y)
			|| is_wall(map->map[(int)r->map.y][(int)r->map.x])
			|| (door && map->map[(int)r->map.y][(int)r->map.x] == 'd'))
		{
			r->hit = map->map[(int)r->map.y][(int)r->map.x];
			break ;
		}
	}
}

void	reduced_ray(void *p)
{
	int			i;
	t_ray		*r;
	t_map		*map;
	const int	*array = p;
	const int	end = array[3];

	map = game()->map[array[0]];
	i = array[2] - 1;
	r = ((t_player *)map->objs[P])->ray;
	while (++i < end)
	{
		init_ray(&r[i], map->objs[P], i);
		dda(&r[i], map, false);
		r[i].perp = get_perp(r[i]);
		map->zbuffer[i] = r[i].perp;
		draw_column(&r[i], i, map);
	}
}

void	cast_rays(int map)
{
	t_thread	*pool;
	int const	args[4][4] = {
	{map, 0, 0, 480},
	{map, 0, 480, 960},
	{map, 0, 960, 1440},
	{map, 0, 1440, 1920},
	};

	pool = game()->eng.pool;
	pool->deploy(pool, reduced_ray, (void *)args[0]);
	pool->deploy(pool, reduced_ray, (void *)args[1]);
	pool->deploy(pool, reduced_ray, (void *)args[2]);
	pool->deploy(pool, reduced_ray, (void *)args[3]);
	pool->wait(pool, 4);
}
