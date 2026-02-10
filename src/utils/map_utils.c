#include "cub3d.h"

int		in_range(t_vtr range, int x, int y)
{
	int out;

	out = 1;
	if (x < 1 || x > range.x - 2)
		out = 0;
	if (y < 1 || y > range.y - 2)
		out = 0;
	return (out);
}

int		which_direction(int right, int left)
{
	int	which_direction;

	which_direction = rand() % 2;
	if (which_direction == 0)
		return (right);
	else if (which_direction == 1)
		return (left);
	return (-1);
}

void	check_path(t_vtr range, t_vtr pos, int *direction)
{
	if (*direction == NORTH || *direction == SOUTH)
	{
		if (!in_range(range, pos.x, pos.y + 1) || !in_range(range, pos.x, pos.y - 1))
			*direction = which_direction(EAST, WEST);
	}
	if (*direction == EAST || *direction == WEST)
	{
		if (!in_range(range, pos.x - 1, pos.y) || !in_range(range, pos.x + 1, pos.y))
			*direction = which_direction(SOUTH, NORTH);
	}
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
bool	valid_door(t_map *map, t_vtr pos)
{
	int		i;
	t_str	*cmap;
	bool	valid;

	i = -1;
	valid = false;
	cmap = map->map;
	if (cmap[pos.y][pos.x] == '0')
	{
		if (cmap[pos.y][pos.x + 1] == '0' && cmap[pos.y][pos.x - 1] == '0'
		&& cmap[pos.y + 1][pos.x] == '1' && cmap[pos.y - 1][pos.x] == '1')
			valid = true;
		if (cmap[pos.y + 1][pos.x] == '0' && cmap[pos.y - 1][pos.x] == '0'
		&& cmap[pos.y][pos.x + 1] == '1' && cmap[pos.y][pos.x - 1] == '1')
			valid = true;
		while (map->objs[++i])
		{
			if (map->objs[i]->pos.x == pos.x && map->objs[i]->pos.y == pos.y)
				valid = false;
		}
	}
	return (valid);
}
