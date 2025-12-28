#include "cub3d.h"

void	ft_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	t_str	pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
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
			pos.y++;
		}
		pos.x++;
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