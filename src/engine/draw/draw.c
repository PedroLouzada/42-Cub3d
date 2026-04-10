/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:55:25 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/10 16:25:25 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_stamina(t_vtr xy, t_vtr wh, double stamina)
{
	int		i;
	int		j;
	t_vtr	p;
	int		fill_w;
	int		start_x;

	if (stamina <= 5 || stamina >= 100)
		return ;
	fill_w = (int)(wh.x * stamina);
	start_x = (xy.x + wh.x / 2) - fill_w / 2;
	j = -1;
	while (++j < wh.y)
	{
		i = -1;
		while (++i < fill_w)
		{
			p.x = start_x + i;
			p.y = (int)xy.y + j;
			ft_pixel_put(game()->mlx->img[BUFFER], (int)p.x, (int)p.y, WHITE);
		}
	}
}

void	draw_hud(void)
{
	const t_player	*p;

	p = (t_player *)game()->map[game()->eng.current_map]->objs[P];
	if (p->battery >= 66.00)
		game()->eng.battery = 12;
	else if (p->battery >= 33.00)
		game()->eng.battery = 13;
	else if (p->battery >= 10)
		game()->eng.battery = 14;
	else
		game()->eng.battery = 15;
	draw_img(game()->mlx->img[game()->eng.battery], 80, 850);
	if (game()->eng.current_map)
		draw_img(game()->mlx->img[game()->eng.current_map + 17], 1820, 20);
	if (p->lives > 0)
	{
		draw_img(game()->mlx->img[HEART], 0, 0);
		if (p->lives > 1)
		{
			draw_img(game()->mlx->img[HEART], 100, 0);
			if (p->lives > 2)
				draw_img(game()->mlx->img[HEART], 200, 0);
		}
	}
}

static void	draw_enemy_in_scene(t_player *p, t_enemy *e)
{
	t_vtr		v[2];
	double		inv_det;
	t_imgs		*sprite;

	v[0].x = e->pos.x - p->pos.x;
	v[0].y = e->pos.y - p->pos.y;
	inv_det = 1.0 / (p->plane.x * p->dir.y - p->dir.x * p->plane.y);
	v[1].x = (p->dir.y * v[0].x - p->dir.x * v[0].y) * inv_det;
	v[1].y = (-p->plane.y * v[0].x + p->plane.x * v[0].y) * inv_det;
	if (v[1].y <= 0)
		return ;
	v[1].x = (WIN_WIDTH / 2.0) * (1 + (v[1].x / v[1].y));
	sprite = (t_imgs *)e->get_texture((t_obj *)e, p->angle);
	draw_enemy_sprite(e, v[1], sprite, game()->map[game()->eng.current_map]);
}

void	game_scene(int level)
{
	t_player	*p;
	t_enemy		*e;
	t_vtr		size;

	p = (t_player *)game()->map[level]->objs[P];
	e = (t_enemy *)game()->map[level]->objs[E];
	size.x = WIN_WIDTH;
	size.y = WIN_HEIGHT;
	cast_rays(level);
	if (level && e)
		draw_enemy_in_scene(p, e);
	draw_img(game()->mlx->img[PLAYERIMG], 1470, 711);
	if (game()->eng.key[K_F] == true && p->battery > 10)
	{
		draw_flashlight(size, size.y / 20, false);
		draw_img(game()->mlx->img[PLAYERIMG], 1470, 711);
		if (level)
			game()->map[level]->minimap(game()->map[level]);
	}
	else
		draw_flashlight(size, 0, false);
	draw_hud();
	draw_stamina((t_vtr){960, 900}, (t_vtr){3, 5}, p->stamina);
	if (game()->eng.screen[2])
		draw_img(game()->mlx->img[Q_KEYIMG], 20, 20);
}

void	draw_screen(t_mlx *mlx)
{
	if (game()->eng.screen[0])
		titlescreen();
	else if (game()->eng.screen[1])
		control_screen();
	else
		game_scene(game()->eng.current_map);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img[0]->img, 0, 0);
}
