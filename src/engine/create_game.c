#include "cub3d.h"

void	run()
{
	mlx_hook(game()->mlx->win, 17, 0, (void *)exit, 0);
	mlx_loop(game()->mlx->mlx);
}

void	init_game(int ac, t_str *av)
{
	t_mlx	*mlx;

	if (ac != 2)
	{
		fprintf(stderr, "Error\nExpected <fileName> <map.cub>\n");
		exit(0);
	}
	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return ;
	mlx->mlx = mlx_init();
	game()->mlx = mlx;
	parsing(av);
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, TITLE);
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->data = mlx_get_data_addr(mlx->img,
			&mlx->bpp, &mlx->sline, &mlx->endn);
	game()->mlx = mlx;
	run();
}

//fazer função para dar handle aos erros do mlx