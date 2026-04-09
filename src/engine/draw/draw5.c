/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:18:54 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 19:09:51 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_characters(t_map *map)
{
	t_player	*p;
	t_enemy		*e;
	t_vtr		pos;

	p = (t_player *)map->objs[P];
	e = (t_enemy *)map->objs[E];
	pos.x = (WIN_WIDTH - 150);
	pos.y = CENTER_Y;
	draw_fov(p->ray, pos);
	draw_circle(game()->mlx, pos, TILE_SZ / 3, BLUE);
	pos.x = e->pos.x - p->pos.x;
	pos.y = e->pos.y - p->pos.y;
	if (pos.x * pos.x + pos.y * pos.y <= RANGE * RANGE)
	{
		pos.x = (WIN_WIDTH - 150) + pos.x * TILE_SZ;
		pos.y = CENTER_Y + pos.y * TILE_SZ;
		draw_fov(e->ray, pos);
		draw_circle(game()->mlx, pos, TILE_SZ / 3, RED);
	}
}

void	draw_minimap(t_map *map)
{
	t_player	*p;
	t_vtr		pos[3];

	p = (t_player *)map->objs[P];
	pos[0].y = (int)p->pos.y - RANGE - 1;
	while (++pos[0].y < (int)p->pos.y + RANGE)
	{
		pos[0].x = (int)p->pos.x - RANGE - 1;
		while (++pos[0].x < (int)p->pos.x + RANGE)
		{
			pos[1].x = pos[0].x - p->pos.x;
			pos[1].y = pos[0].y - p->pos.y;
			pos[2].x = (WIN_WIDTH - 150) + pos[1].x * TILE_SZ;
			pos[2].y = CENTER_Y + pos[1].y * TILE_SZ;
			draw_tile(game()->mlx, pos[2], tile_color(map, pos[0]));
		}
	}
	draw_characters(map);
}

void	draw_fov(t_ray *r, t_vtr pos)
{
	double	len;
	t_vtr	end;
	int		left;
	int		right;
	t_vtr	start;

	left = (WIN_WIDTH / 4) - 1;
	right = (WIN_WIDTH / 4) * 3;
	while (++left < right)
	{
		if (r[left].perp < 0)
			continue ;
		len = ft_min(r[left].perp, RANGE);
		start = pos;
		end.x = pos.x + (r[left].dir.x * len) * TILE_SZ;
		end.y = pos.y + (r[left].dir.y * len) * TILE_SZ;
		draw_line(start, end, FLOOR);
	}
}

int	darken_color(double distance, double radius, int color, bool minimap)
{
	int		rgb[3];
	double	max_dist;
	double	intensity;
	double	brightness;

	if (color < 0)
		return (-1);
	if (color == CLEAR)
		return (color);
	max_dist = radius * TILE_SZ;
	intensity = distance / (max_dist * max_dist);
	if (intensity > 1.0)
		intensity = 1.0;
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
	brightness = 1.0 - intensity;
	if (brightness < 0.125)
		brightness = 0.125;
	if (minimap)
		brightness = 0.225;
	rgb[0] = (int)(rgb[0] * brightness);
	rgb[1] = (int)(rgb[1] * brightness);
	rgb[2] = (int)(rgb[2] * brightness);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	draw_flashlight(t_vtr size, int radius, bool minimap)
{
	int		c;
	t_vtr	pos;
	t_vtr	draw;
	double	distance;

	pos.y = -1;
	while (++pos.y < size.y)
	{
		pos.x = -1;
		while (++pos.x < size.x)
		{
			draw.x = pos.x - (size.x / 2);
			draw.y = pos.y - (size.y / 2);
			distance = draw.x * draw.x + draw.y * draw.y;
			if (distance < radius * radius)
				continue ;
			c = ft_get_color(game()->mlx->img[BUFFER], (int)pos.x, (int)pos.y);
			c = darken_color(distance, radius, c, minimap);
			if (c < 0)
				continue ;
			ft_pixel_put(game()->mlx->img[BUFFER], (int)pos.x, (int)pos.y, c);
		}
	}
}
