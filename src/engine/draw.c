#include "cub3d.h"

int	ft_get_pixel_color(t_imgs *img, int x, int y)
{
	int	offset;

	offset = (y * img->sline) + (x * (img->bpp / 8));
	return (*(unsigned int *)(img->addr + offset));
}

void	draw_img(t_imgs *img, int px, int py)
{
	int		y;
	int		x;
	t_mlx	*mlx;

	y = -1;
	mlx = game()->mlx;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			ft_pixel_put(mlx, px + x, py + y, ft_get_pixel_color(img, x, y));
	}
}

void	titlescreen(void)
{
	t_imgs	*img;

	img = game()->mlx->img->next;
	draw_img(img, 0, 0);
	img = img->next;
	draw_img(img, 240, 320);
	img = img->next;
	draw_img(img, 240, 440);
	img = img->next;
	draw_img(img, 240, 560);
	img = img->next;
	if (game()->eng->in_button[0])
        draw_img(img, 240, 320);
	if (game()->eng->in_button[1])
        draw_img(img, 240, 440);
	if (game()->eng->in_button[2])
        draw_img(img, 240, 560);
}

void draw_screen(t_mlx *mlx)
{
	if (game()->eng->title)
		titlescreen();
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}
