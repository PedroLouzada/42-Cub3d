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

int		avoid_wall(int right, int left)
{
	int	which_direction;

	which_direction = rand() % 2;
	if (which_direction == 0)
		return (right);
	else if (which_direction == 1)
		return (left);
}
