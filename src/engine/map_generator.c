#include "cub3d.h"

t_str	get_file(int level)
{
	t_str	files[5];

	files[0] = "maps/level_1";
	files[1] = "maps/level_2";
	files[2] = "maps/level_3";
	files[3] = "maps/level_4";
	files[4] = "maps/level_5";
	return (ft_joinstr(files[level - 1], ".cub"));
}

void	print_map(t_map *map)
{
	t_str	file;
	int		data[3];

	file = get_file(map->level);
	if (!file)
		return ;
	data[2] = open(file, O_CREAT | O_RDWR | O_TRUNC, PERMISSIONS);
	if (data[2] < 0)
		return ;
	data[0] = -1;
	while (++data[0] < map->map_size.y)
	{
		data[1] = -1;
		while (++data[1] < map->map_size.x)
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
	t_vtr	pos;
	int		moves;

	moves = 0;
	pos = rand_pos(map->map_size);
	if (!in_range(map->map_size, pos.x, pos.y))
		return ;
	while (map->map[pos.y][pos.x] != '0')
	{
		map->map[pos.y][pos.x] = '0';
		check_path(map->map_size, pos, &direction);
		move_in_path(map->map_size, &pos, direction);
		moves++;
		if (moves % (MIN_MOVES + rand() % (MAX_MOVES - MIN_MOVES + 1)) == 0)
			where_to_next(&direction);
	}
}

void	generate_map(t_map *map)
{
	int		data[4];

	map->map = ft_calloc(map->map_size.y + 1, sizeof(t_str));
	if (!map->map)
		return ;
	data[0] = -1;
	while (++data[0] < map->map_size.y)
	{
		map->map[data[0]] = ft_calloc(map->map_size.x + 1, 1);
		if (!map->map[data[0]])
		{
			while (data[0]--)
				free(map->map[data[0]]);
			return ;
		}
		data[1] = -1;
		while (++data[1] < map->map_size.x)
			map->map[data[0]][data[1]] = '1';
	}
	data[2] = MIN_PATHS + rand() % (MAX_PATHS - MIN_PATHS + 1);
	while (data[2]--)
		generate_path(map, NORTH + rand() % (SOUTH - NORTH + 1));
}
