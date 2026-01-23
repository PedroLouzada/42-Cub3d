#include "cub3d.h"

int	update(void)
{
	draw_screen(game()->mlx);
	usleep(33);
	return (0);
}

void	run(void)
{
	mlx_hook(game()->mlx->win, 17, 0, exit_game, 0);
	mlx_hook(game()->mlx->win, 2, (1L << 0), key_press, game);
	mlx_hook(game()->mlx->win, 3, (1L << 1), key_unpress, game);
	mlx_hook(game()->mlx->win, 6, 1L << 6, mouse_move, NULL);
	mlx_hook(game()->mlx->win, 4, 1L << 2, mouse_press, NULL);
	mlx_loop_hook(game()->mlx->mlx, update, NULL);
	mlx_loop(game()->mlx->mlx);
}

void	init_game(int ac, t_str *av)
{
	static t_eng	eng;

	if (ac != 2)
	{
		fprintf(stderr, "Error\nExpected <fileName> <map.cub>\n");
		exit(0);
	}
	game()->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!game()->mlx)
		parse_exit("Memory Allocation\n", NULL, -1, 0);
	game()->mlx->mlx = mlx_init();
	if (!game()->mlx->mlx)
		parse_exit("Memory Allocation\n", NULL, -1, 0);
	parsing(av);
	game()->mlx->win = mlx_new_window(game()->mlx->mlx, WIN_WIDTH, WIN_HEIGHT,
			TITLE);
	if (!game()->mlx->win)
		parse_exit("Memory Allocation\n", (void *)game()->map[0]->objs, -1, 1);
	game()->mlx->img = new_img(NULL);
	if (!game()->mlx->img)
		exit_game("Error\nMemory Allocation\n");
	game()->eng = &eng;
	alloc_assets();
	run();
}

// fazer função para dar handle aos erros do mlx