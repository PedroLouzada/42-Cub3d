#include "cub3d.h"

t_str	get_file(int level)
{
	t_str	files[5];

	files[0] = "level_1";
	files[1] = "level_2";
	files[2] = "level_3";
	files[3] = "level_4";
	files[4] = "level_5";
	return (ft_joinstr(files[level], ".cub"));
}

void	print_map(t_map *map, int level)
{
	t_str	file;
	int		data[3];

	file = get_file(level);
	if (!file)
		return ;
	data[2] = open(file, O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC);
	if (data[2] < 0)
		return ;
	data[0] = -1;
	while (++data[0] < map->map_size.y)
	{
		data[1] = -1;
		while (++data[1] < map->map_size.x)
			dprintf(data[2], "%c", map->minimap[level][data[0]][data[1]]);
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

void	generate_path(t_map *map, int direction, int level)
{
	t_vtr 	pos;
	int		moves;
	t_vtr	range;

	moves = 0;
	range.x = 2;
	range.y = 10;
	pos = rand_pos(map->map_size);
	if (!in_range(map->map_size, pos.x, pos.y))
		return ;
	while (map->minimap[level][pos.y][pos.x] != '0')
	{
		map->minimap[level][pos.y][pos.x] = '0';
		check_path(map->map_size, pos, &direction);
		move_in_path(map->map_size, &pos, direction);
		moves++;
		if (moves % (range.x + rand() % (range.y - range.x + 1)) == 0)
			where_to_next(&direction);
	}
}

void	generate_map(t_map *map, int level)
{
	int 	data[3];
	t_vtr	range;

	map->minimap[level] = ft_calloc(map->map_size.y + 1, sizeof(t_str));
	if (!map->minimap[level])
		return ;
	data[0] = -1;
	while (++data[0] < map->map_size.y)
	{
		map->minimap[level][data[0]] = ft_calloc(map->map_size.x + 1, sizeof(char));
		if (!map->minimap[level][data[0]])
		{
			while (data[0]--)
				free(map->minimap[level][data[0]]);
			return ;
		}
		data[1] = -1;
		while (++data[1] < map->map_size.x)
			map->minimap[level][data[0]][data[1]] = '1';
	}
	range.x = 200;
	range.y = 500;
	data[2] = range.x + rand() % (range.y - range.x + 1);
	while (data[2]--)
		generate_path(map, NORTH + rand() % (SOUTH - NORTH + 1), level);
}

 //adicionar conversor de chars para t_asset/t_wall

void render_map(t_map *map)
{
	(void)map;
	return;
}