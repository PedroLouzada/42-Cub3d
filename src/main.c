#include "cub3d.h"

void	clear_image(t_game *game);

t_game	*game(void)
{
	static t_game	game;

	return (&game);
}

int	main(int ac, char **av)
{
    init_game(game(), ac, av);
	if (ac == 1)
	{
		init_rand();
		for (int i = 1; i < 6; ++i) {
			game()->map[i] = create_map(i);
			game()->map[i]->destroy(game()->map[i]);
		}
		return (0);
	}
//     game->map = calloc(1, sizeof(t_map));
// 	game->parsing(game, ac, av);
// // game->run(game);
    
// 	// dar handle direito depois
// 	clear_image(game);
// 	free_double(game->map[0]->map);
// 	free(game->map);
// 	mlx_destroy_display(game->mlx->mlx);
// 	free(game->mlx->mlx);
// 	free(game->mlx);
}