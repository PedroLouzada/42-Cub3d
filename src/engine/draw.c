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
	draw_img(img[WASDIMG], 320, 190);
	draw_img(img[ARROWS], 1070, 315);
	draw_img(img[MOUSEIMG], 1270, 150);
	draw_img(img[BACKBUTTON], 90, 850);
	if (game()->eng.in_button[3])
		draw_img(img[BACKBORDER], 90, 850);
}

void	draw_stamina(t_vtr xy, t_vtr wh, double stamina)
{
	int	fill_w;
	int	start_x;
	int	i;
	int	j;

	if (stamina <= 5 || stamina >= 100)
		return ;
	fill_w = (int)(wh.x * stamina);
	start_x = (xy.x + wh.x / 2) - fill_w / 2;
	j = 0;
	while (j < wh.y)
	{
		i = 0;
		while (i < fill_w)
		{
			ft_pixel_put(game()->mlx->img[BUFFER], start_x + i, (int)xy.y + j, WHITE);
			i++;
		}
		j++;
	}
}

void	draw_hud(void)
{
	const t_player	*p = (t_player *)game()->map[game()->eng.current_map]->objs[P];

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
	draw_enemy_sprite(e, v[1], sprite);
}

void	game_scene(void)
{
	t_player	*p;
	t_enemy		*e;
	t_vtr		size;

	p = (t_player *)game()->map[game()->eng.current_map]->objs[P];
	e = (t_enemy *)game()->map[game()->eng.current_map]->objs[E];
	size.x = WIN_WIDTH;
	size.y = WIN_HEIGHT;
	cast_rays(game()->eng.current_map, P);
	if (game()->eng.current_map)
		draw_enemy_in_scene(p, e);
	draw_img(game()->mlx->img[PLAYERIMG], 1470, 711);
	if (game()->eng.key[K_F] == true && p->battery > 10)
	{
		draw_flashlight(size, size.y / 20, false);
		draw_img(game()->mlx->img[PLAYERIMG], 1470, 711);
		if (game()->eng.current_map)
			game()->map[game()->eng.current_map]->minimap(game()->map[game()->eng.current_map]);
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
		game_scene();
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img[0]->img, 0, 0);
}
