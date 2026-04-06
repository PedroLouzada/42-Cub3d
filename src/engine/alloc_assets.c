#include "cub3d.h"

static void	remove_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = 0;
			return ;
		}
		i++;
	}
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
	{
		remove_newline(name);
		new_img->img = mlx_xpm_file_to_image(mlx->mlx, name, &new_img->width,
				&new_img->height);
	}
	else
		new_img->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!new_img->img)
		return (NULL);
	new_img->addr = mlx_get_data_addr(new_img->img, &new_img->bpp,
			&new_img->sline, &new_img->endian);
	return (new_img);
}

void	alloc_assets(void)
{
	int			i;
	char		*str;
	t_imgs		*img;
	const int	fd = open("./assets/paths.txt", O_RDONLY);

	if (fd < 0)
		parse_exit("Invalid Fd", NULL, -1, 1);
	game()->mlx->img = ft_calloc(29, sizeof(t_imgs *));
	if (!game()->mlx->img)
		parse_exit("Memory Allocation\n", NULL, fd, 1);
	game()->mlx->img[0] = new_img(NULL);
	if (!game()->mlx->img[0])
		parse_exit("Memory Allocation\n", NULL, fd, 1);
	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		img = new_img(str);
		if (!img || !img->img)
		{
			(free(str), close(fd));
			exit_game("Memory Allocation\n");
		}
		game()->mlx->img[i + 1] = img;
		i++;
		free(str);
	}
	game()->eng.screen[0] = true;
	close(fd);
}
