#include "cub3d.h"

void	run(t_game *game)
{
	game->mlx->win = mlx_new_window(game->mlx->mlx, 1920, 1080, "CUB3D");
	mlx_hook(game->mlx->win, 17, 0, (void *)exit, 0);
	mlx_loop(game->mlx->mlx);
}

void	init_game(t_game *game, int ac, t_str *av)
{
	t_mlx	*mlx;

	(void)ac;
	(void)av;
	mlx->mlx = mlx_init();
	if (!mlx)
		return (fprintf(stderr, MLX_ERR), free(game), NULL);
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, TITLE);
	game->mlx = mlx;
	// parsing(game, ac, av);
}

//fazer função para dar handle aos erros do mlx