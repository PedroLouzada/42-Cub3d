#include "cub3d.h"

void	map_validation(char *str, t_game *game);
void	check_sintax(char *str);

void	parsing(t_game *game, int ac, char **av)
{
	(void)ac;
	// if (ac != 2)
	// 	parse_exit("Expected <fileName> <map.cub>\n", NULL, -1);
	check_sintax(av[1]);
	map_validation(av[1], game);
	return ;
}