#include "cub3d.h"

void	map_validation(char *str, int *d);
void	check_sintax(char *str);

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

void	init_objs(t_map *map, int d)
{
	map->objs = ft_calloc(d + 3, sizeof(t_obj *));
	if (!map->objs)
		parse_exit("Memory Allocation11\n", NULL, -1, 1);
	change_door(map->map, map->map_size);
	map->objs[0] = create_player(get_vtr(map->map), 0);
	if (!map->objs)
		parse_exit("Memory Allocation\n", NULL, -1, 1);
}

void	parsing(char **av)
{
	int	*d;

	d = 0;
	check_sintax(av[1]);
	map_validation(av[1], d);
	// init_objs(game()->map[0], *d);
	return ;
}

// tratar dois players e info a baixo do mapa