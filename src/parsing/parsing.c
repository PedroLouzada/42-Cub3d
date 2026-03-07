#include "cub3d.h"

void	map_validation(char *str);
void	check_sintax(char *str);
void	generate_objs(t_map *map);

void	change_door(char **map, t_vtr size)
{
	int	y;
	int	x;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (map[y] && map[y][x])
		{
			if (map[y][x] == 'D')
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}

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
			if (map[y][x] == 'N' || map[y][x] == 'E' || map[y][x] == 'W'
				|| map[y][x] == 'S')
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
		}
	}
	pos.x = 0;
	return (pos);
}

void	parsing(char **av)
{
	check_sintax(av[1]);
	map_validation(av[1]);
	generate_objs(game()->map[0]);
	return ;
}

// tratar dois players e info a baixo do mapa