#include "cub3d.h"

int	in_range(t_map *map, int x, int y)
{
	int	out;

	out = 1;
	if (x < 1 || x > map->map_size.x - 2)
		out = 0;
	if (y < 1 || y > map->map_size.y - 2)
		out = 0;
	if (map->map[y][x] == 'E')
		out = 0;
	return (out);
}

int	which_direction(int right, int left, int back)
{
	int	which_direction;

	if (back)
		which_direction = rand() % 3;
	else
		which_direction = rand() % 2;
	if (which_direction == 0)
		return (right);
	else if (which_direction == 1)
		return (left);
	else if (which_direction == 2)
		return (back);
	return (-1);
}

void	check_path(t_map *map, t_vtr pos, int *direction)
{
	if (*direction == NORTH && !in_range(map, pos.x, pos.y + 1))
		*direction = which_direction(EAST, WEST, SOUTH);
	if (*direction == SOUTH && !in_range(map, pos.x, pos.y - 1))
		*direction = which_direction(EAST, WEST, NORTH);
	if (*direction == EAST && !in_range(map, pos.x + 1, pos.y))
		*direction = which_direction(SOUTH, NORTH, WEST);
	if (*direction == WEST && !in_range(map, pos.x - 1, pos.y))
		*direction = which_direction(SOUTH, NORTH, EAST);
}

void	move_in_path(t_map *map, t_vtr *pos, int direction)
{
	if (direction == NORTH && in_range(map, pos->x, pos->y + 1))
		pos->y++;
	if (direction == EAST && in_range(map, pos->x + 1, pos->y))
		pos->x++;
	if (direction == WEST && in_range(map, pos->x - 1, pos->y))
		pos->x--;
	if (direction == SOUTH && in_range(map, pos->x, pos->y - 1))
		pos->y--;
}

static bool	in_bounds(char **map, int y, int x)
{
	size_t	len;

	if (!map || y < 0 || x < 0 || !map[y])
		return (false);
	len = ft_strlen(map[y]);
	if ((size_t)x >= len)
		return (false);
	return (true);
}

bool	valid_door(t_map *map, t_vtr pos)
{
	int		i;
	t_str	*cmap;
	bool	valid;
	int		x;
	int		y;

	if (!map || !map->map || !map->objs)
		return (false);
	cmap = map->map;
	x = (int)pos.x;
	y = (int)pos.y;
	valid = false;
	if (!in_bounds(cmap, y, x))
		return (false);
	/* need all 4 neighbors */
	if (!in_bounds(cmap, y, x + 1) || !in_bounds(cmap, y, x - 1)
		|| !in_bounds(cmap, y + 1, x) || !in_bounds(cmap, y - 1, x))
		return (false);
	if (cmap[y][x] != '0')
		return (false);
	if (cmap[y][x + 1] == '0' && cmap[y][x - 1] == '0' && cmap[y + 1][x] == '1'
		&& cmap[y - 1][x] == '1')
		valid = true;
	if (cmap[y + 1][x] == '0' && cmap[y - 1][x] == '0' && cmap[y][x + 1] == '1'
		&& cmap[y][x - 1] == '1')
		valid = true;
	i = -1;
	while (valid && map->objs[++i])
	{
		if (map->objs[i]->pos.x == pos.x && map->objs[i]->pos.y == pos.y)
			return (false);
	}
	return (valid);
}
