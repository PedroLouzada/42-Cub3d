/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:12:19 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/10 17:29:00 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tile_color(t_map *map, t_vtr pos)
{
	int	color;

	color = CLEAR;
	if (pos.y >= 0 && pos.y < map->map_size.y
		&& pos.x >= 0 && pos.x < map->map_size.x)
	{
		color = FLOOR;
		if (map->map[(int)pos.y][(int)pos.x] == '1')
			color = WALL;
		if (map->map[(int)pos.y][(int)pos.x] == 'D'
			|| map->map[(int)pos.y][(int)pos.x] == 'd')
			color = BLUE;
	}
	return (color);
}

int	ft_get_color(t_imgs *img, int x, int y)
{
	int	offset;

	offset = (y * img->sline) + (x * (img->bpp / 8));
	return (*(unsigned int *)(img->addr + offset));
}

void	draw_img(t_imgs *img, int px, int py)
{
	int		y;
	int		x;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			ft_pixel_put(game()->mlx->img[BUFFER], px + x, py + y,
				ft_get_color(img, x, y));
	}
}

void	titlescreen(void)
{
	t_imgs	**img;

	img = game()->mlx->img;
	game()->eng.in_button[3] = false;
	draw_img(img[BACKGROUND], 0, 0);
	draw_img(img[BUTTON1], 240, 320);
	draw_img(img[BUTTON2], 240, 440);
	draw_img(img[BUTTON3], 240, 560);
	if (game()->eng.in_button[0])
		draw_img(img[BUTTONBORDER], 240, 320);
	if (game()->eng.in_button[1])
		draw_img(img[BUTTONBORDER], 240, 440);
	if (game()->eng.in_button[2])
		draw_img(img[BUTTONBORDER], 240, 560);
}

void	control_screen(void)
{
	int		i;
	t_imgs	**img;

	i = 0;
	img = game()->mlx->img;
	while (i < 3)
		game()->eng.in_button[i++] = false;
	draw_img(img[BACKGROUND], 0, 0);
	draw_img(img[30], 60, 25);
	draw_img(img[BACKBUTTON], 90, 850);
	if (game()->eng.in_button[3])
		draw_img(img[BACKBORDER], 90, 850);
}
