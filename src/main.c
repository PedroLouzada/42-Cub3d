#include "cub3d.h"

t_game	*game(void)
{
	static t_game	game;

	return (&game);
}

void f1(void *arg)
{
	(void)arg;
	printf("1\n");
}

void f2(void *arg)
{
	(void)arg;
	printf("2\n");
}

int	main(int ac, char **av)
{
    init_game(ac, av);
}
