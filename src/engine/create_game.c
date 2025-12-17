#include "cub3d.h"

// void	run(t_game *game)
// {
// 	game->mlx->win = mlx_new_window(game->mlx->mlx, 1920, 1080, "CUB3D");
// 	mlx_hook(game->mlx->win, 17, 0, (void *)exit, 0);
// 	mlx_loop(game->mlx->mlx);
// }

void	init_game(int ac, t_str *av)
{
	t_mlx	*mlx;

	(void)ac;
	(void)av;
	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return ;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, TITLE);
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->data = mlx_get_data_addr(mlx->img,
			&mlx->bpp, &mlx->sline, &mlx->endn);
	game()->mlx = mlx;
	// parsing(game, ac, av);
}

//fazer função para dar handle aos erros do mlx