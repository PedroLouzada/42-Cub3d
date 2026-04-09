/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:12:22 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 19:10:03 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_imgs *img, int x, int y, int color)
{
	t_str	pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	if (color == CLEAR)
		return ;
	pixel = img->addr + (y * img->sline + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	draw_circle(t_mlx *mlx, t_vtr cpos, int radius, int color)
{
	t_vtr	pos;

	pos.y = radius * -1;
	while (pos.y <= radius)
	{
		pos.x = radius * -1;
		while (pos.x <= radius)
		{
			if (pos.x * pos.x + pos.y * pos.y <= radius * radius)
				ft_pixel_put(mlx->img[BUFFER], cpos.x + pos.x, cpos.y + pos.y,
					color);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_tile(t_mlx *mlx, t_vtr tpos, int color)
{
	t_vtr	pos[3];
	int		radius;

	pos[0].y = -1;
	radius = RANGE * TILE_SZ;
	color = darken_color(0, 0, color, true);
	while (++pos[0].y < TILE_SZ)
	{
		pos[0].x = -1;
		while (++pos[0].x < TILE_SZ)
		{
			pos[1].x = tpos.x + pos[0].x;
			pos[1].y = tpos.y + pos[0].y;
			pos[2].x = pos[1].x - (WIN_WIDTH - 150);
			pos[2].y = pos[1].y - CENTER_Y;
			if (pos[2].x * pos[2].x + pos[2].y * pos[2].y <= radius * radius)
				ft_pixel_put(mlx->img[BUFFER], pos[1].x, pos[1].y, color);
			else
				ft_pixel_put(mlx->img[BUFFER], pos[1].x, pos[1].y, CLEAR);
		}
	}
}

void	draw_line(t_vtr s, t_vtr e, int color)
{
	t_vtr	data[3];

	round_vtrs(&s, &e);
	data[0].x = fabs(e.x - s.x);
	data[0].y = fabs(e.y - s.y);
	data[1].x = (s.x < e.x) - (s.x > e.x);
	data[1].y = (s.y < e.y) - (s.y > e.y);
	data[2].x = data[0].x - data[0].y;
	while (1)
	{
		ft_pixel_put(game()->mlx->img[BUFFER], (int)s.x, (int)s.y, color);
		if (s.x == e.x && s.y == e.y)
			break ;
		data[2].y = data[2].x * 2;
		if (data[2].y > -data[0].y)
		{
			data[2].x -= data[0].y;
			s.x += data[1].x;
		}
		if (data[2].y < data[0].x)
		{
			data[2].x += data[0].x;
			s.y += data[1].y;
		}
	}
}

int	texture_dir(t_ray *r)
{
	if (r->side == 0)
	{
		if (r->dir.x > 0)
			return (1);
		else
			return (2);
	}
	else
	{
		if (r->dir.y > 0)
			return (3);
		else
			return (0);
	}
	return (-1);
}
