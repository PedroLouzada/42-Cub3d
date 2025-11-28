#include "cub3d.h"

void	map_validation(char *str, t_map *map);
void	check_sintax(char *str);

void	parsing(int ac, char **av, t_game *game)
{
	if (ac != 2)
		parse_exit("Expected <fileName> <map.cub>\n", NULL);
	check_sintax(av[1]);
	map_validation(av[1], game->map);
	return ;
}