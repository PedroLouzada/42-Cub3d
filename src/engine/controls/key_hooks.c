/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:55:56 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/10 16:33:26 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key)
{
	if (key == K_ESC)
		exit_game(NULL);
	if (key == K_E)
	{
		if (!game()->eng.current_map)
			return (0);
	}
	if (key == K_F || key == K_TAB || key == K_Q)
	{
		if (key == K_Q && !game()->eng.screen[2] && game()->map[0])
			return (0);
		game()->eng.key[key] = !game()->eng.key[key];
	}
	else
		game()->eng.key[key] = true;
	return (0);
}

int	key_unpress(int key)
{
	if (key == K_F || key == K_TAB)
		return (0);
	game()->eng.key[key] = false;
	return (0);
}

void	interact_door(t_map *map, t_player *p)
{
	t_ray	r;

	init_ray(&r, (t_obj *)p, WIN_WIDTH / 2);
	dda(&r, map, true);
	printf("perp: %f\n", r.perp);
	if (r.perp < 1.5)
	{
		if (r.hit == 'D')
			map->map[(int)r.map.y][(int)r.map.x] = 'd';
		else if (r.hit == 'd')
			map->map[(int)r.map.y][(int)r.map.x] = 'D';
		else if (map->map[(int)r.map.y][(int)r.map.x] == 'L')
		{
			if (game()->eng.current_map++ >= 5)
				exit_game(GAME_WON);
		}
	}
}
