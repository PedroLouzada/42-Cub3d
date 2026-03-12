#include "cub3d.h"

void	map_validation(char *str);
void	check_sintax(char *str);
void	generate_objs(t_map *map);

t_vtr	get_vtr(char **map)
{
	int		y;
	int		x;
	t_vtr	pos;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'P')
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
		}
	}
	pos.x = 0;
	pos.y = 0;
	return (pos);
}

void	parsing(char **av)
{
	check_sintax(av[1]);
	map_validation(av[1]);
	game()->map[0]->player_pos = get_vtr(game()->map[0]->map);
	generate_objs(game()->map[0]);
	return ;
}

// tratar dois players e info a baixo do mapa