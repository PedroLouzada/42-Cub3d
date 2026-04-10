/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:55:56 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/10 16:53:04 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	in_bounds(char **map, int y, int x);

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

void	door_dda(t_ray *r)
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
}

void	change_door(t_map *map, t_ray *r)
{
	if (r->perp > 1.5)
		return ;
	if (map->map[(int)r->map.y][(int)r->map.x] == '1')
		return ;
	if (map->map[(int)r->map.y][(int)r->map.x] == 'D')
	{
		map->map[(int)r->map.y][(int)r->map.x] = 'd';
		return ;
	}
	if (map->map[(int)r->map.y][(int)r->map.x] == 'd')
	{
		map->map[(int)r->map.y][(int)r->map.x] = 'D';
		return ;
	}
}

void	interact_door(t_map *map, t_player *p)
{
	t_ray	*r;

	r = p->ray;
	init_ray(p->ray, (t_obj *)p, WIN_WIDTH / 2);
	while (1)
	{
		door_dda(r);
		if (!in_bounds(map->map, (int)r->map.y, (int)r->map.x))
			return ;
		if (r->side == 0)
			r->perp = r->s_dist.x - r->dlt_dist.x;
		else
			r->perp = r->s_dist.y - r->dlt_dist.y;
		change_door(map, r);
		if (map->map[(int)r->map.y][(int)r->map.x] == 'L')
		{
			game()->eng.current_map += 1;
			if (game()->eng.current_map >= 5)
			{
				printf("*!CONGRATULATIONS!*\n");
				exit_game(NULL);
			}
		}
	}
}
