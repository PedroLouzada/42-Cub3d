#include "cub3d.h"

void	clear_image(t_game *game);

t_game	*get_game_addr(t_game *src)
{
	static t_game	*game;

	if (src)
		game = src;
	return (game);
}

int	main(int ac, char **av)
{
	t_game *game;

    game = game_init();
    get_game_addr(game);
	if (ac == 1)
	{
		game->map = create_map();
		init_rand();
		game->map->generate(game->map);
		game->map->print(game->map);
		game->map->destroy(game->map);
		return (0);
	}
    game->map = calloc(1, sizeof(t_map));
	game->parsing(game, ac, av);
    game->run(game);
    
	// dar handle direito depois
	clear_image(game);
	free_double(game->map->map);
	free(game->map);
	mlx_destroy_display(game->mlx->mlx);
	free(game->mlx->mlx);
	free(game->mlx);
}