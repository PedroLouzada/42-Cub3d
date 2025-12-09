#include "cub3d.h"
void	clear_image(t_game *game);

t_game *get_game_addr(t_game *src)
{
    static t_game *game;

    if (src)
        game = src;
    return (game);
}

int main(int ac, char **av)
{
    static t_game game;

    get_game_addr(&game);
    game.mlx = mlx_init();
    if (!game.mlx)
        parse_exit("Error on mlx initialization\n", NULL, -1);
    parsing(ac, av, &game);


    // dar handle direito depois
    clear_image(&game);
	free_double(game.map->coordinate);
	free(game.map);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
}