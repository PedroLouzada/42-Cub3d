#include "cub3d.h"

void	map_validation(char *str);
void	check_sintax(char *str);

static bool	get_player_pos(t_map *map, t_vtr *pos)
{
	int		y;
	int		x;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (map->map[y][x] == 'P')
			{
				map->map[y][x] = '0';
				pos->x = x + 0.3;
				pos->y = y + 0.3;
				return (true);
			}
		}
	}
	return (false);
}

static int	count_doors(t_map *map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
			if (map->map[y][x] == 'D')
				count++;
	}
	return (count);
}

static void	create_parsed_objs(t_map *map, t_vtr player_pos)
{
	int	x;
	int	y;
	int	i;

	map->objs = ft_calloc(count_doors(map) + 2, sizeof(t_obj *));
	if (!map->objs)
		parse_exit("Memory Allocation\n", NULL, -1, 1);
	map->objs[E] = malloc(1);
	if (!map->objs[E])
		parse_exit("Memory Allocation\n", NULL, -1, 1);
	map->objs[P] = create_player(player_pos);
	if (!map->objs[P])
		parse_exit("Memory Allocation\n", NULL, -1, 1);
	i = P;
	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
			if (map->map[y][x] == 'D')
				map->objs[++i] = create_door(map, (t_vtr){x, y});
	}
}

void	parsing(char **av)
{
	t_vtr	pos;

	check_sintax(av[1]);
	map_validation(av[1]);
	if (!get_player_pos(game()->map[0], &pos))
		parse_exit("Should have one player\n", NULL, -1, 1);
	create_parsed_objs(game()->map[0], pos);
	return ;
}

// tratar dois players e info a baixo do mapa