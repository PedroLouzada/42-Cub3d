#include "cub3d.h"

void	init_rand(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		return ;
	srand(time.tv_sec ^ time.tv_usec);
}

t_vtr	rand_pos(t_vtr range)
{
	t_vtr	pos;
	int		data[3];

	data[0] = 1;
	data[1] = range.x - 2;
	data[2] = range.y - 2;
	pos.x = data[0] + rand() % (data[1] - data[0] + 1);
	pos.y = data[0] + rand() % (data[2] - data[0] + 1);
	return (pos);
}

void	where_to_next(int *direction)
{
	int	where_to;

	where_to = NORTH + rand() % (SOUTH - NORTH + 1);
	if (*direction == NORTH && where_to == SOUTH)
		where_to--;
	else if (*direction == EAST && where_to == WEST)
		where_to++;
	else if (*direction == WEST && where_to == EAST)
		where_to--;
	else if (*direction == SOUTH && where_to == NORTH)
		where_to++;
	*direction = where_to;
}
