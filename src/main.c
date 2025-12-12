#include "cub3d.h"

void	clear_image(t_game *game);

int	main(int ac, char **av)
{
	t_game 	*game;

    game = game_init();
	if (ac == 1)
	{
		init_rand();
		for (int i = 1; i < 6; ++i) {
			game->map[i] = create_map(i);
			game->map[i]->generate(game->map[i]);
			game->map[i]->print(game->map[i]);
			game->map[i]->destroy(game->map[i]);
		}
		return (0);
	}
    
// 	// dar handle direito depois
// 	clear_image(game);
// 	free_double(game->map[0]->map);
// 	free(game->map);
// 	mlx_destroy_display(game->mlx->mlx);
// 	free(game->mlx->mlx);
// 	free(game->mlx);
}