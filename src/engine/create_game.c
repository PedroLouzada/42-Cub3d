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

void	put_onlist(t_imgs *img)
{
	t_imgs	*curr;

	if (!game()->mlx->img)
		return ;
	curr = game()->mlx->img;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = img;
}

t_imgs	*new_img(char *name)
{
	t_mlx	*mlx;
	t_imgs	*new_img;

	new_img = ft_calloc(1, sizeof(t_imgs));
	if (!new_img)
		return (NULL);
	mlx = game()->mlx;
	if (name)
		new_img->img = mlx_xpm_file_to_image(mlx->mlx, name, &new_img->width,
				&new_img->height);
	else
		new_img->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!new_img->img)
		return (NULL);
	new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bpp,
			&new_img->sline, &new_img->endian);
	new_img->next = NULL;
	put_onlist(new_img);
	return (new_img);
}

void	titlescreen(t_mlx *mlx)
{
	t_imgs	*img;

	img = new_img("./assets/imgs/homescreen.xpm");
	if (!img || !img->img)
		parse_exit("Image Allocation\n", NULL, -1, 1);
	draw_img(img, 0, 0);
	img = new_img("./assets/imgs/button_test.xpm");
	if (!img || !img->img)
		parse_exit("Image Allocation\n", NULL, -1, 1);
	draw_img(img, 240, 320);
	draw_img(img, 240, 440);
	draw_img(img, 240, 560);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}

void	run(void)
{
	mlx_hook(game()->mlx->win, 17, 0, (void *)exit, 0); // corrigir o exit();
	mlx_hook(game()->mlx->win, 4, 1L << 2, mouse_press, NULL);
	titlescreen(game()->mlx);
	mlx_loop(game()->mlx->mlx);
}

void	init_game(int ac, t_str *av)
{
	if (ac != 2)
	{
		fprintf(stderr, "Error\nExpected <fileName> <map.cub>\n");
		exit(0);
	}
	game()->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!game()->mlx)
		return ;
	game()->mlx->mlx = mlx_init();
	parsing(av);
	game()->mlx->win = mlx_new_window(game()->mlx->mlx, WIN_WIDTH, WIN_HEIGHT,
			TITLE);
	game()->mlx->img = new_img(NULL);
	run();
}

// fazer função para dar handle aos erros do mlx