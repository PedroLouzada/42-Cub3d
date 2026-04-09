/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:12:27 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 16:52:08 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_shade(double dist, int color)
{
	double	shade;

	shade = 1.0 - (dist / RANGE);
	if (shade < 0.0)
		shade = 0.0;
	color = darken_color(dist * (1.0 - shade), 0.375, color, false);
	return (color);
}

double	get_tex(double pos, double size, double s_size, double screen)
{
	double	tex;

	tex = (pos - (-size / 2 + (int)screen)) * s_size / size;
	if (tex < 0)
		tex = 0;
	if (tex >= s_size)
		tex = s_size - 1;
	return (tex);
}

bool	set_sprite_data(t_vtr *size, t_vtr *start, t_vtr *end, t_vtr s_pos)
{
	size->y = abs((int)(WIN_HEIGHT / s_pos.y));
	size->x = size->y;
	if (size->y <= 0 || size->x <= 0)
		return (false);
	start->y = -size->y / 2 + WIN_HEIGHT / 2;
	if (start->y < 0)
		start->y = 0;
	end->y = size->y / 2 + WIN_HEIGHT / 2;
	if (end->y >= WIN_HEIGHT)
		end->y = WIN_HEIGHT - 1;
	start->x = -size->x / 2 + (int)s_pos.x;
	if (start->x < 0)
		start->x = 0;
	end->x = size->x / 2 + (int)s_pos.x;
	if (end->x >= WIN_WIDTH)
		end->x = WIN_WIDTH - 1;
	return (true);
}

void	draw_enemy_sprite(t_enemy *e, t_vtr s_pos, t_imgs *spr, t_map *map)
{
	int		c;
	t_vtr	pos;
	t_vtr	dt[4];

	if (!e || !spr || !set_sprite_data(&dt[0], &dt[1], &dt[2], s_pos))
		return ;
	pos.x = dt[1].x - 1;
	while (++pos.x <= dt[2].x)
	{
		if (s_pos.y >= map->zbuffer[(int)pos.x])
			continue ;
		dt[3].x = get_tex(pos.x, dt[0].x, spr->width, s_pos.x);
		pos.y = dt[1].y - 1;
		while (++pos.y <= dt[2].y)
		{
			dt[3].y = get_tex(pos.y, dt[0].y, spr->height, WIN_HEIGHT / 2);
			c = ft_get_color(spr, dt[3].x, dt[3].y);
			if (game()->eng.key[K_F])
				c = get_shade(s_pos.y, c);
			ft_pixel_put(game()->mlx->img[BUFFER], (int)pos.x, (int)pos.y, c);
		}
	}
}
