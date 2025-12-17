#include "cub3d.h"

void	clear_image(t_game *game);

t_game	*game(void)
{
	static t_game	game;

	return (&game);
}

int	main(int ac, char **av)
{
    init_game(ac, av);
	if (ac == 1)
	{
		init_rand();
		for (int i = 1; i < 6; ++i)
			game()->map[i] = create_map(i);
		game()->map[1]->minimap(game()->map[1]);
		mlx_put_image_to_window(game()->mlx->mlx, game()->mlx->win, game()->mlx->img, 0 , 0);
		mlx_loop(game()->mlx->mlx);
		return (0);
	}  
	parsing(ac, av);
}