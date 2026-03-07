#include "cub3d.h"

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
	t_mlx	*mlx;

	y = -1;
	mlx = game()->mlx;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			ft_pixel_put(game()->mlx->img[BUFFER], px + x, py + y,
				ft_get_color(img, x, y));
	}
}

void	titlescreen(void)
{	t_imgs	**img;

	img = game()->mlx->img;
	game()->eng->in_button[3] = false;
	draw_img(img[BACKGROUND], 0, 0);
	draw_img(img[BUTTON1], 240, 320);
	draw_img(img[BUTTON2], 240, 440);
	draw_img(img[BUTTON3], 240, 560);
	if (game()->eng->in_button[0])
		draw_img(img[BUTTONBORDER], 240, 320);
	if (game()->eng->in_button[1])
		draw_img(img[BUTTONBORDER], 240, 440);
	if (game()->eng->in_button[2])
		draw_img(img[BUTTONBORDER], 240, 560);
}

void	control_screen(void)
{	int		i;
	t_imgs	**img;

	i = 0;
	img = game()->mlx->img;
	while (i < 3)
		game()->eng->in_button[i++] = false;
	draw_img(img[BACKGROUND], 0, 0);
	draw_img(img[WASDIMG], 320, 190);
	draw_img(img[ARROWS], 1070, 315);
	draw_img(img[MOUSEIMG], 1270, 150);
	draw_img(img[BACKBUTTON], 90, 850);
	if (game()->eng->in_button[3])
		draw_img(img[BACKBORDER], 90, 850);
}

void	game_scene(void)
{	t_player	*p;
	t_vtr		size;

	p = (t_player *)game()->map[game()->eng->current_map]->objs[P];
	size.x = WIN_WIDTH;
	size.y = WIN_HEIGHT;
	cast_rays(1, E);
	cast_rays(1, P);
	draw_img(game()->mlx->img[PLAYERIMG], 1470, 711);
	if (game()->eng->key[K_F] == true && p->battery > 0)
	{
		draw_flashlight(size, size.y / 20, LIGHT_ON);
		draw_img(game()->mlx->img[PLAYERIMG], 1470, 711);
		game()->map[game()->eng->current_map]->minimap(game()->map[game()->eng->current_map]);
	}
	else
		draw_flashlight(size, 0, LIGHT_OFF);
}

void	draw_screen(t_mlx *mlx)
{
	if (game()->eng->title[0])
		titlescreen();
	else if (game()->eng->title[1])
		control_screen();
	else
		game_scene();
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img[0]->img, 0, 0);
}
