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
	static int index;

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
	new_img->index = index++;
	put_onlist(new_img);
	return (new_img);
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
}

void draw_screen(t_mlx *mlx)
{
	if (game()->eng->title)
		titlescreen();
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}

int update()
{
	draw_screen(game()->mlx);
	usleep(33);
	return (0);
}

void	run(void)
{
	mlx_hook(game()->mlx->win, 17, 0, exit_game, 0);
	mlx_hook(game()->mlx->win, 6, 1L << 6, mouse_move, NULL);
	mlx_hook(game()->mlx->win, 4, 1L << 2, mouse_press, NULL);
	mlx_loop_hook(game()->mlx->mlx, update, NULL);
	mlx_loop(game()->mlx->mlx);
}
void alloc_assets()
{
	t_mlx *mlx;
	t_imgs *img;

	mlx = game()->mlx;
	img = new_img("./assets/imgs/homescreen.xpm");
	if (!img || !img->img)
		parse_exit("Image Allocation\n", NULL, -1, 1);
	img = new_img("./assets/imgs/play_butt.xpm");
	if (!img || !img->img)
	parse_exit("Image Allocation\n", NULL, -1, 1);
	img = new_img("./assets/imgs/tutorial_butt.xpm");
	if (!img || !img->img)
		parse_exit("Image Allocation\n", NULL, -1, 1);
	img = new_img("./assets/imgs/controls_butt.xpm");
	if (!img || !img->img)
		parse_exit("Image Allocation\n", NULL, -1, 1);
	img = new_img("./assets/imgs/border_butt.xpm");
	if (!img || !img->img)
		parse_exit("Image Allocation\n", NULL, -1, 1);
	game()->eng->title = true;
}

void	init_game(int ac, t_str *av)
{
	static t_eng eng;

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
	game()->eng = &eng;
	alloc_assets();
	run();
}

// fazer função para dar handle aos erros do mlx