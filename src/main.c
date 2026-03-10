#include "cub3d.h"

t_game	*game(void)
{
	static t_game	game;

	return (&game);
}

int	main(int ac, char **av)
{
	init_game(ac, av);
	// void *m = mlx_init();
	// mlx_new_window(m, 200, 200, "A");
}
