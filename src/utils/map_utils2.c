#include "cub3d.h"

bool	not_door(t_map *map, t_vtr pos)
{	int	i;

	i = -1;
	while (map->objs[++i])
	{
		if (map->objs[i]->pos.x == pos.x && map->objs[i]->pos.y == pos.y)
			return (false);
	}
	return (true);
}

t_vtr	spawn(t_map *map, char tile)
{	t_vtr	pos;

	pos = rand_pos(map->map_size);
	while (map->map[(int)pos.y] && map->map[(int)pos.y][(int)pos.x] != tile)
		pos = rand_pos(map->map_size);
	return (pos);
}

void	check_map(t_map *map, int x, int y)
{	if (map->map[y][x] == '1' || map->map[y][x] == '0')
		return ;
	map->map[y][x] = '0';
	check_map(map, x + 1, y);
	check_map(map, x - 1, y);
	check_map(map, x, y + 1);
	check_map(map, x, y - 1);
}

bool	valid_map(t_map *map)
{	t_vtr	pos;

	pos.y = -1;
	while (map->map[(int)++pos.y])
	{
		pos.x = -1;
		while (map->map[(int)pos.y][(int)++pos.x])
		{
			if (map->map[(int)pos.y][(int)pos.x] == '.')
				return (false);
		}
	}
	return (true);
}

void	set_exit(t_map *map)
{	t_vtr	pos;
	
	pos = spawn(map, '1');
	while (map->map[(int)pos.y][(int)pos.x + 1] != '0'
		&& map->map[(int)pos.y][(int)pos.x - 1] != '0'
		&& map->map[(int)pos.y + 1][(int)pos.x] != '0'
		&& map->map[(int)pos.y - 1][(int)pos.x] != '0')
	{
		pos = spawn(map, '1');
	}
	map->map[(int)pos.y][(int)pos.x] = 'E';
}
