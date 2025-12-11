#include "cub3d.h"

void	run(t_game *game)
{
	game->mlx->win = mlx_new_window(game->mlx->mlx, 1080, 900, "CUB3D");
	mlx_hook(game->mlx->win, 17, 0, (void *)exit, 0);
	mlx_loop(game->mlx->mlx);
}

t_game	*game_init(void)
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx = calloc(1, sizeof(t_mlx));
	game->mlx->mlx = mlx_init();
	if (!game->mlx)
		parse_exit("Error on mlx initialization\n", NULL, -1);
	game->parsing = parsing;
	game->run = run;
	return (game);
}