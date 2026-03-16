#include "cub3d.h"

void	ft_pixel_put(t_imgs *img, int x, int y, int color)
{
	t_str	pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	if (color == 16711935)
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

void	draw_tile(t_mlx *mlx, t_vtr tpos, int scale, int color)
{
	t_vtr	pos;

	pos.y = -1;
	while (++pos.y < scale)
	{
		pos.x = -1;
		while (++pos.x < scale)
			ft_pixel_put(mlx->img[BUFFER], tpos.x + pos.x, tpos.y + pos.y,
				color);
	}
}

void	draw_line(t_vtr start, t_vtr end, int color)
{
	t_vtr	data[3];

	round_vtrs(&start, &end);
	data[0].x = fabs(end.x - start.x);
	data[0].y = fabs(end.y - start.y);
	data[1].x = (start.x < end.x) - (start.x > end.x);
	data[1].y = (start.y < end.y) - (start.y > end.y);
	data[2].x = data[0].x - data[0].y;
	while (1)
	{
		ft_pixel_put(game()->mlx->img[BUFFER], (int)start.x, (int)start.y,
			color);
		if (start.x == end.x && start.y == end.y)
			break ;
		data[2].y = data[2].x * 2;
		if (data[2].y > -data[0].y)
		{
			data[2].x -= data[0].y;
			start.x += data[1].x;
		}
		if (data[2].y < data[0].x)
		{
			data[2].x += data[0].x;
			start.y += data[1].y;
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

t_imgs	*set_tex(t_ray *ray, double start, double lheight, t_map *map)
{
	t_imgs	*img;

	if (ray->hit == 'D')
		img = map->door;
	else if (ray->hit == 'S')
		img = game()->mlx->img[EXIT];
	else
	{
		ray->tex.txt_id = texture_dir(ray);
		img = map->textures[ray->tex.txt_id];
	}
	set_tx(ray, img->width);
	ray->tex.tex_step = (double)img->height / lheight;
	ray->tex.tex_pos = (start - (WIN_HEIGHT / 2) + (lheight / 2))
		* ray->tex.tex_step;
	return (img);
}

int rgb(int r, int g, int b)
{
    return (r << 16 | g << 8 | b);
}

void	draw_column(t_ray *r, int column, t_map *map)
{
	double	i;
	t_vtr	draw;
	double	lheight;
	t_imgs	*img;

	lheight = (double)WIN_HEIGHT / r->perp;
	draw.x = -lheight / 2 + (double)WIN_HEIGHT / 2;
	draw.y = lheight / 2 + (double)WIN_HEIGHT / 2;
	if (draw.x < 0)
		draw.x = 0;
	if (draw.y > WIN_HEIGHT)
		draw.y = WIN_HEIGHT;
	i = -1;
	img = set_tex(r, draw.x, lheight, map);
	int *color = map->colors[0];
	while (++i < draw.x)
		ft_pixel_put(game()->mlx->img[BUFFER], column, (int)i, rgb(color[1], color[2], color[3]));
	while (++i < draw.y)
	{
		set_ty(r, img->height);
		ft_pixel_put(game()->mlx->img[BUFFER], column, (int)i, ft_get_color(img,
				r->tex.tex_x, r->tex.tex_y));
	}
	color = map->colors[1];
	while (++i < WIN_HEIGHT)
		ft_pixel_put(game()->mlx->img[BUFFER], column, (int)i, rgb(color[1], color[2], color[3]));
}
