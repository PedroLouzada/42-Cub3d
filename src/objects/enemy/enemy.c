/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:10:25 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 17:30:07 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	e_update(t_obj *this, t_map *map)
{
	t_enemy			*e;
	static t_vtr	prev;
	static double	prev_angle;

	if (!game()->eng.current_map)
		return ;
	e = (t_enemy *)this;
	attack_player(e, map, prev, prev_angle);
	prev = e->pos;
	prev_angle = e->angle;
	enemy_los(e, map);
	if (e->chase)
		e_chase(e, map);
	else
		e_walk(e, map);
	if (!e_is_stuck(e, prev, prev_angle))
		e_timer(true, STUCK);
	e->frame++;
}

t_obj	*create_enemy(t_vtr pos)
{
	int			i;
	t_enemy		*e;

	e = ft_calloc(1, sizeof(t_enemy));
	if (!e)
		return (NULL);
	e->ray = ft_calloc(WIN_WIDTH + 1, sizeof(t_ray));
	if (!e->ray)
		exit_game(ALLOC_ERR);
	i = -1;
	while (++i < 6)
		e->textures[i] = game()->mlx->img[i + 23];
	e->pos = pos;
	e->update = e_update;
	e->get_texture = enemy_get_texture;
	e->chase = false;
	e->frame = 0;
	e->angle = pick_rand(pick_rand(M_PI_2, 0), pick_rand(M_PI, 3 * M_PI_2));
	set_e_orientation(e);
	return ((t_obj *)e);
}
