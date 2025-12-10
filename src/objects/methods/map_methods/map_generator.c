#include "cub3d.h"

void	print_map(t_map *map)
{
	int	data[3];

	data[2] = open("map.cub", O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC);
	if (data[2] < 0)
		return ;
	data[0] = -1;
	while (++data[0] < map->size.y)
	{
		data[1] = -1;
		while (++data[1] < map->size.x)
			dprintf(data[2], "%c", map->map[data[0]][data[1]]);
		dprintf(data[2], "\n");
	}
	close(data[2]);
}

void	move_in_path(t_vtr range, t_vtr *pos, int direction)
{
	if (direction == NORTH && in_range(range, pos->x, pos->y + 1))
		pos->y++;
	if (direction == EAST && in_range(range, pos->x + 1, pos->y))
		pos->x++;
	if (direction == WEST && in_range(range, pos->x - 1, pos->y))
		pos->x--;
	if (direction == SOUTH && in_range(range, pos->x, pos->y - 1))
		pos->y--;
}

void	generate_path(t_map *map, int direction)
{
	t_vtr 	pos;
	int		moves;
	t_vtr	range;

	moves = 0;
	range.x = 2;
	range.y = 10;
	pos = rand_pos(map->size);
	if (!in_range(map->size, pos.x, pos.y))
		return ;
	while (map->map[pos.y][pos.x] != '0')
	{
		map->map[pos.y][pos.x] = '0';
		check_path(map->size, pos, &direction);
		move_in_path(map->size, &pos, direction);
		moves++;
		if (moves % (range.x + rand() % (range.y - range.x + 1)) == 0)
			where_to_next(&direction);
	}
}

void	generate_map(t_map *map)
{
	int 	data[3];
	t_vtr	range;

	map->map = ft_calloc(map->size.y + 1, sizeof(t_str));
	if (!map->map)
		return ;
	data[0] = -1;
	while (++data[0] < map->size.y)
	{
		map->map[data[0]] = ft_calloc(map->size.x + 1, sizeof(char));
		if (!map->map[data[0]])
		{
			while (data[0]--)
				free(map->map[data[0]]);
			return ;
		}
		data[1] = -1;
		while (++data[1] < map->size.x)
			map->map[data[0]][data[1]] = '1';
	}
	range.x = 200;
	range.y = 500;
	data[2] = range.x + rand() % (range.y - range.x + 1);
	while (data[2]--)
		generate_path(map, NORTH + rand() % (SOUTH - NORTH + 1));
}

void render_map(t_map *map)
{
	(void)map;
	return;
}