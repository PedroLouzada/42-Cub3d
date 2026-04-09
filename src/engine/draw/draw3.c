/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:12:25 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 16:44:49 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_tx(t_ray *ray, int width)
{
	int		tx;
	double	wall_x;

	if (ray->side == 0)
		wall_x = ray->pos.y + ray->perp * ray->dir.y;
	else
		wall_x = ray->pos.x + ray->perp * ray->dir.x;
	wall_x -= floor(wall_x);
	tx = (int)(wall_x * width);
	if (tx < 0)
		tx = 0;
	if (tx >= width)
		tx = width - 1;
	if (ray->side == 0 && ray->dir.x < 0)
		tx = width - tx - 1;
	if (ray->side == 1 && ray->dir.y > 0)
		tx = width - tx - 1;
	ray->tex.tex_x = tx;
}

void	set_ty(t_ray *ray, int height)
{
	int	ty;

	ty = (int)ray->tex.tex_pos;
	ray->tex.tex_pos += ray->tex.tex_step;
	if (ty < 0)
		ty = 0;
	if (ty >= height)
		ty = height - 1;
	ray->tex.tex_y = ty;
}

t_imgs	*set_tex(t_ray *r, t_vtr *limits, t_map *map)
{
	t_imgs	*img;
	double	lheight;

	lheight = (double)WIN_HEIGHT / r->perp;
	limits->x = -lheight / 2 + (double)WIN_HEIGHT / 2;
	limits->y = lheight / 2 + (double)WIN_HEIGHT / 2;
	if (limits->x < 0)
		limits->x = 0;
	if (limits->y > WIN_HEIGHT)
		limits->y = WIN_HEIGHT;
	if (r->hit == 'D')
		img = map->door;
	else if (r->hit == 'L')
		img = game()->mlx->img[EXIT];
	else
	{
		r->tex.txt_id = texture_dir(r);
		img = map->textures[r->tex.txt_id];
	}
	set_tx(r, img->width);
	r->tex.tex_step = (double)img->height / lheight;
	r->tex.tex_pos = (limits->x - (WIN_HEIGHT / 2) + (lheight / 2))
		* r->tex.tex_step;
	return (img);
}

int	rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_column(t_ray *r, int column, t_map *map)
{
	int		i;
	t_imgs	*img;
	int		color;
	t_vtr	limits;

	i = -1;
	img = set_tex(r, &limits, map);
	color = rgb(map->colors[0][1], map->colors[0][2], map->colors[0][3]);
	while (++i < limits.x)
		ft_pixel_put(game()->mlx->img[BUFFER], column, (int)i, color);
	while (++i < limits.y)
	{
		set_ty(r, img->height);
		color = ft_get_color(img, r->tex.tex_x, r->tex.tex_y);
		if (game()->eng.key[K_F])
			color = get_shade(r->perp, color);
		ft_pixel_put(game()->mlx->img[BUFFER], column, (int)i, color);
	}
	color = rgb(map->colors[1][1], map->colors[1][2], map->colors[1][3]);
	while (++i < WIN_HEIGHT)
		ft_pixel_put(game()->mlx->img[BUFFER], column, (int)i, color);
}
