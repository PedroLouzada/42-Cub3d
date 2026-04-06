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

bool	in_bounds(char **map, int y, int x)
{
	int	len;

	if (!map || y < 0 || x < 0 || !map[y])
		return (false);
	len = ft_strlen(map[y]);
	if (x >= len)
		return (false);
	return (true);
}
