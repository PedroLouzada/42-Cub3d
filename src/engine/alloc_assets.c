#include "cub3d.h"

t_imgs	*new_img(char *name)
{	t_mlx	*mlx;
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
	return (new_img);
}

void	alloc_assets(void)
{	int		i;
	t_imgs	*img;
	char *const paths[] = {"./assets/imgs/home/homescreen.xpm",
		"./assets/imgs/home/play_butt.xpm",
		"./assets/imgs/home/tutorial_butt.xpm",
		"./assets/imgs/home/controls_butt.xpm",
		"./assets/imgs/home/border_butt.xpm",
		"./assets/imgs/home/wasd_keys.xpm", "./assets/imgs/home/arrow_keys.xpm",
		"./assets/imgs/home/mouse.xpm", "./assets/imgs/home/back_button.xpm",
		"./assets/imgs/home/back_border.xpm", "./assets/imgs/player.xpm", NULL};

	game()->mlx->img = ft_calloc(12, sizeof(t_imgs *));
	game()->mlx->img[0] = new_img(NULL);
	if (!game()->mlx->img[0])
		exit_game("Memory Allocation\n");
	i = 0;
	while (paths[i])
	{
		img = new_img(paths[i]);
		if (!img || !img->img)
			exit_game("Error\nMemory Allocation2\n");
		game()->mlx->img[i + 1] = img;
		i++;
	}
	game()->eng->title[0] = true;
}
