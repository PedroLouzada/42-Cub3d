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
