#include "cub3d.h"

int	run(t_obj **objs)
{
	static double	prev;
	static double	curr;

	curr = get_time();
	game()->eng->dt = curr - prev;
	if (game()->eng->dt > 0.1)
		game()->eng->dt = 0.1;
	prev = curr;
	objs[E]->update(objs[E], game()->map[1]);
	objs[P]->update(objs[P], game()->map[1]);
	draw_screen(game()->mlx);
	return (0);
}

void	declare_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 0, exit_game, 0);
	mlx_hook(mlx->win, 2, (1L << 0), key_press, game);
	mlx_hook(mlx->win, 3, (1L << 1), key_unpress, game);
	mlx_hook(mlx->win, 6, 1L << 6, mouse_move, NULL);
	mlx_hook(mlx->win, 4, 1L << 2, mouse_press, NULL);
	mlx_loop_hook(mlx->mlx, run, game()->map[1]->objs);
	mlx_loop(mlx->mlx);
}

void	init_game(int ac, t_str *av)
{
	static t_eng	eng;
	int				i;

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
	game()->eng->pool = init_tpool(4);
	alloc_assets();
	init_rand();
	i = 0;
	while (++i < 6)
		game()->map[i] = create_map(i, -1);
	declare_hooks(game()->mlx);
}

// fazer função para dar handle aos erros do mlx