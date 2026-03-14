#include "cub3d.h"

void	clear_image(int n)
{
	int	j;
	int	i;

	j = -1;
	while (++j < n)
	{
		if (j)
		{
			mlx_destroy_image(game()->mlx->mlx, game()->map[j]->door->img);
			free(game()->map[j]->door);
		}
		i = -1;
		while (++i < 4)
		{
			if (game()->map[j])
			{
				mlx_destroy_image(game()->mlx->mlx,
					game()->map[j]->textures[i]->img);
				free(game()->map[j]->textures[i]);
			}
		}
	}
	if (n > 1)
	{
		i = 0;
		while (game()->mlx->img[i])
		{
			mlx_destroy_image(game()->mlx->mlx, game()->mlx->img[i]->img);
			free(game()->mlx->img[i]);
			i++;
		}
	}
	free(game()->mlx->img);
}

void	parse_exit(char *s, char *arg, int fd, bool map)
{
	int	len;

	len = ft_strlen(s);
	write(2, "Error\n", 6);
	write(2, s, len);
	free(arg);
	if (map)
		clear_image(1);
	game()->map[0]->destroy(game()->map[0]);
	if (game()->mlx)
	{
		if (game()->mlx->win)
			mlx_destroy_window(game()->mlx->mlx, game()->mlx->win);
		if (game()->mlx->mlx)
		{
			mlx_destroy_display(game()->mlx->mlx);
			free(game()->mlx->mlx);
		}
		free(game()->mlx);
	}
	if (fd > 0)
		close(fd);
	game()->eng.pool->destroy(game()->eng.pool);
	exit(1);
}

int	exit_game(char *str)
{
	int				i;
	int				j;
	t_thread_plus	*t;

	if (str)
	{
		write(2, "Error\n", 6);
		write(2, str, ft_strlen(str));
	}
	game()->eng.pool->destroy(game()->eng.pool);
	clear_image(6);
	mlx_destroy_window(game()->mlx->mlx, game()->mlx->win);
	i = -1;
	while (++i < 6)
	{
		if (game()->map[i])
			game()->map[i]->destroy(game()->map[i]);
	}
	mlx_destroy_display(game()->mlx->mlx);
	free(game()->mlx->mlx);
	free(game()->mlx);
	exit(0);
	return (0);
}
