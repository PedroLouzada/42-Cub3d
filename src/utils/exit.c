/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbongiov <pbongiov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:11:08 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/10 17:36:33 by pbongiov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_textures(int level)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game()->map[level])
		{
			if (game()->map[level]->textures[i]
				&& game()->map[level]->textures[i]->img)
			{
				mlx_destroy_image(game()->mlx->mlx,
					game()->map[level]->textures[i]->img);
				free(game()->map[level]->textures[i]);
			}
		}
	}
}

void	clear_image(int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (i && game()->map[i] && game()->map[i]->door)
		{
			mlx_destroy_image(game()->mlx->mlx, game()->map[i]->door->img);
			free(game()->map[i]->door);
		}
		clear_textures(i);
	}
	if (n > 1)
	{
		i = -1;
		while (++i <= N_ASSETS)
		{
			if (game()->mlx->img[i])
			{
				mlx_destroy_image(game()->mlx->mlx, game()->mlx->img[i]->img);
				free(game()->mlx->img[i]);
			}
		}
	}
	free(game()->mlx->img);
}

void	parse_exit(char *s, char *arg, int fd, bool map)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	free(arg);
	if (map)
		clear_image(1);
	else if (game()->map[0] && game()->mlx && game()->mlx->mlx)
		clear_textures(0);
	if (game()->map[0])
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
	if (game()->eng.pool)
		game()->eng.pool->destroy(game()->eng.pool);
	exit(1);
}

int	exit_game(t_str message)
{
	int	i;

	if (message)
		write(2, message, ft_strlen(message));
	if (game()->eng.pool)
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
