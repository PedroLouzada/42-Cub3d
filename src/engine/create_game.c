#include "cub3d.h"

void	run(t_game *game)
{
	game->mlx->win = mlx_new_window(game->mlx->mlx, 1920, 1080, "CUB3D");
	mlx_hook(game->mlx->win, 17, 0, (void *)exit, 0);
	mlx_loop(game->mlx->mlx);
}

t_game	*create_game(int ac, t_str *av)
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx = calloc(1, sizeof(t_mlx));
	game->mlx->mlx = mlx_init();
	if (!game->mlx)
		parse_exit(MLX_ERR, NULL, -1);
	parsing(game, ac, av);
	return (game);
}