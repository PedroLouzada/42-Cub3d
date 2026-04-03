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
			ft_pixel_put(mlx, px + x, py + y, ft_get_color(img, x, y));
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
	t_vtr		v[1];

	p = (t_player *)game()->map[1]->objs[P];
	e = (t_enemy *)game()->map[1]->objs[E];
	v[0].x = WIN_WIDTH;
	v[0].y = WIN_HEIGHT;
	enemy_los(e, game()->map[1]);
	cast_rays(game()->map[1], p->ray, game()->map[1]->objs[P]);
	draw_enemy_in_scene(p, e);
	if (game()->eng->key[K_F] == true && p->battery > 0)
	{
		draw_flashlight(v[0], v[0].y / 20, false);
		game()->map[1]->minimap(game()->map[1]);
	}
	else
		draw_flashlight(v[0], 0, false);
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
