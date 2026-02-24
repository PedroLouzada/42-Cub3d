#include "cub3d.h"

void	ft_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	t_str	pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	if (color == 16711935)
		return ;
	pixel = mlx->img->addr + (y * mlx->img->sline + x * (mlx->img->bpp / 8));
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
				ft_pixel_put(mlx, cpos.x + pos.x, cpos.y + pos.y, color);
			pos.x++;
		}
		pos.y++;
	}	
}

void	draw_tile(t_mlx *mlx, t_vtr tpos, int scale, int color)
{
	t_vtr pos;

	pos.y = -1;
	while (++pos.y < scale)
	{
		pos.x = -1;
		while (++pos.x < scale)
			ft_pixel_put(mlx, tpos.x + pos.x, tpos.y + pos.y, color);
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
		ft_pixel_put(game()->mlx, (int)start.x, (int)start.y, color);
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

void	draw_column(t_ray *r, int column)
{
	double	i;
	t_vtr	draw;
	double	lHeight;

	lHeight = (double)WIN_HEIGHT / r->perp;
	draw.x = -lHeight / 2 + (double)WIN_HEIGHT / 2;
	draw.y = lHeight / 2 + (double)WIN_HEIGHT / 2;
	if (draw.x < 0)
		draw.x = 0;
	if (draw.y > WIN_HEIGHT)
		draw.y = WIN_HEIGHT;
	i = -1;
	while (++i < draw.x)
		ft_pixel_put(game()->mlx, column, (int)i, CEILING);
	while (++i < draw.y)
		ft_pixel_put(game()->mlx, column, (int)i, WALL);
	while (++i < WIN_HEIGHT)
		ft_pixel_put(game()->mlx, column, (int)i, FLOOR);
}
