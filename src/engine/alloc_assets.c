#include "cub3d.h"

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
	t_mlx		*mlx;
	t_imgs		*new_img;
	static int	index;

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

void	alloc_assets(void)
{
	int		i;
	t_imgs	*img;

	char *const paths[] = {"./assets/imgs/home/homescreen.xpm",
		"./assets/imgs/home/play_butt.xpm",
		"./assets/imgs/home/tutorial_butt.xpm",
		"./assets/imgs/home/controls_butt.xpm",
		"./assets/imgs/home/border_butt.xpm",
		"./assets/imgs/home/wasd_keys.xpm", "./assets/imgs/home/arrow_keys.xpm",
		"./assets/imgs/home/mouse.xpm", "./assets/imgs/home/back_button.xpm",
		"./assets/imgs/home/back_border.xpm", 
		NULL};
	i = 0;
	while (paths[i])
	{
		img = new_img(paths[i++]);
		if (!img || !img->img)
			exit_game("Error\nMemory Allocation\n");
	}
	game()->eng->title[0] = true;
}
