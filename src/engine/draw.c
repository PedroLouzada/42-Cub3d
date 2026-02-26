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

	game()->eng->in_button[3] = false;
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

void	control_screen(void)
{
	int		i;
	t_imgs	*img;

	i = 0;
	while (i < 3)
		game()->eng->in_button[i++] = false;
	img = game()->mlx->img->next;
	draw_img(img, 0, 0); // background
	while (img->index < 6)
		img = img->next;
	draw_img(img, 320, 190); // WASD
	img = img->next;
	draw_img(img, 1070, 315); // arrows
	img = img->next;
	draw_img(img, 1270, 150); // mouse
	img = img->next;
	draw_img(img, 90, 850); // back_button
	img = img->next;
	if (game()->eng->in_button[3])
		draw_img(img, 90, 850); // back_border
}

void	game_scene(void)
{
	t_vtr	size;

	size.x = WIN_WIDTH;
	size.y = WIN_HEIGHT;
	cast_rays(game()->map[1], game()->map[1]->rays[E], game()->map[1]->objs[E], E);
	cast_rays(game()->map[1], game()->map[1]->rays[P], game()->map[1]->objs[P], P);
	draw_flashlight(size, size.y / 20, VIEW);
	game()->map[1]->minimap(game()->map[1]);
}

void	draw_screen(t_mlx *mlx)
{
	if (game()->eng->title[0])
		titlescreen();
	else if (game()->eng->title[1])
		control_screen();
	else
		game_scene();
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}
