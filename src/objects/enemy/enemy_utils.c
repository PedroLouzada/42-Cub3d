/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:40:00 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 17:28:43 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	e_timer(bool reset, int timer)
{
	static double	start[3];

	if (reset)
		start[timer] = 0;
	if (!start[timer])
		start[timer] = get_time();
	return (get_time() - start[timer]);
}

bool	e_is_stuck(t_enemy *e, t_vtr prev, double prev_angle)
{
	if ((int)prev.x == (int)e->pos.x && (int)prev.y == (int)e->pos.y
		&& prev_angle == e->angle)
		return (true);
	return (false);
}

void	attack_player(t_enemy *e, t_map *map, t_vtr prev, double prev_angle)
{
	t_player	*p;

	p = (t_player *)map->objs[P];
	if (e_hits_player(e, p))
	{
		p->lives--;
		if (p->lives <= 0)
			exit_game(GAME_OVER);
		e->chase = false;
		e->pos = spawn(map, '0');
		e_timer(true, RESPAWN);
		e_timer(true, STUCK);
	}
	else if ((e_timer(false, STUCK) > 10.0 && e_is_stuck(e, prev, prev_angle))
		|| e_timer(false, RESPAWN) > 120.0)
	{
		e->chase = false;
		e->pos = spawn(map, '0');
		e_timer(true, RESPAWN);
		e_timer(true, STUCK);
	}
}

void	*enemy_get_texture(t_obj *this, double dir)
{
	t_enemy	*e;

	(void)dir;
	e = (t_enemy *)this;
	return ((void *)e->textures[e->frame % 6]);
}
