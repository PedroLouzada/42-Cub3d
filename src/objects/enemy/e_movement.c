/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_movement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:10:18 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 17:15:17 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_e_orientation(t_enemy *e)
{
	e->dir.x = cos(e->angle);
	e->dir.y = sin(e->angle);
	e->plane.x = -e->dir.y * FOV;
	e->plane.y = e->dir.x * FOV;
}

void	e_rotate(t_enemy *e, double speed)
{
	e->angle += speed * game()->eng.dt;
	if (e->angle < 0)
		e->angle = 2 * M_PI;
	if (e->angle > 2 * M_PI)
		e->angle = 0;
	set_e_orientation(e);
}

double	check_sides(t_enemy *e, t_map *map, double radius, double speed)
{
	double	dt;
	double	dir;
	double	offset;
	t_vtr	look[2];

	dir = M_PI_4;
	offset = M_PI / 8;
	dt = game()->eng.dt;
	look[0].x = e->pos.x + cos(e->angle + dir) * (radius + speed * dt);
	look[0].y = e->pos.y + sin(e->angle + dir) * (radius + speed * dt);
	look[1].x = e->pos.x + cos(e->angle - dir) * (radius + speed * dt);
	look[1].y = e->pos.y + sin(e->angle - dir) * (radius + speed * dt);
	if (e_can_walk(map, look[0]) && e_can_walk(map, look[1]))
		return (pick_rand(offset, -offset));
	else if (e_can_walk(map, look[0]))
		return (offset);
	else if (e_can_walk(map, look[1]))
		return (-offset);
	return (M_PI);
}

void	e_chase(t_enemy *e, t_map *map)
{
	double	dt;
	t_vtr	walk;
	t_vtr	look;
	double	speed;
	double	radius;

	speed = 3.5;
	radius = 0.6;
	dt = game()->eng.dt;
	look.x = e->pos.x + cos(e->angle) * (radius + speed * dt);
	look.y = e->pos.y + sin(e->angle) * (radius + speed * dt);
	if (!e_can_walk(map, look))
		e_rotate(e, check_sides(e, map, radius, speed));
	walk.x = e->pos.x + cos(e->angle) * speed * dt;
	walk.y = e->pos.y + sin(e->angle) * speed * dt;
	if (e_can_walk(map, (t_vtr){walk.x, e->pos.y}))
		e->pos.x = walk.x;
	if (e_can_walk(map, (t_vtr){e->pos.x, walk.y}))
		e->pos.y = walk.y;
}

void	e_walk(t_enemy *e, t_map *map)
{
	double	dt;
	t_vtr	look;
	t_vtr	walk;
	double	speed;
	double	radius;

	speed = 2.0;
	radius = 0.6;
	dt = game()->eng.dt;
	look.x = e->pos.x + cos(e->angle) * (radius + speed * dt);
	look.y = e->pos.y + sin(e->angle) * (radius + speed * dt);
	if (!e_can_walk(map, look))
		e_rotate(e, check_sides(e, map, radius, speed));
	walk.x = e->pos.x + cos(e->angle) * speed * dt;
	walk.y = e->pos.y + sin(e->angle) * speed * dt;
	if (e_can_walk(map, (t_vtr){walk.x, e->pos.y}))
		e->pos.x = walk.x;
	if (e_can_walk(map, (t_vtr){e->pos.x, walk.y}))
		e->pos.y = walk.y;
}
