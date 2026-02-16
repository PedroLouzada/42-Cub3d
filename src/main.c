#include "cub3d.h"

t_game	*game(void)
{
	static t_game	game;

	return (&game);
}

int	main(int ac, char **av)
{
    init_game(ac, av);
}
