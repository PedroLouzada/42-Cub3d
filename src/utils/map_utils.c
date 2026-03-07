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

bool	valid_door(t_map *map, t_vtr pos)
{
	int		i;
	t_str	*cmap;
	bool	valid;
	int		psx[2];

	i = -1;
	valid = false;
	cmap = map->map;
	psx[0] = (int)pos.x;
	psx[1] = (int)pos.y;
	if (!cmap || !cmap[psx[1]] || !cmap[psx[1]][psx[0]])
		return (false);
	if (cmap[psx[1]][psx[0]] == '0')
	{
		if (cmap[psx[1]][psx[0] + 1] == '0' && cmap[psx[1]][psx[0] - 1] == '0'
			&& cmap[psx[1] + 1][psx[0]] == '1' && cmap[psx[1]
			- 1][psx[0]] == '1')
			valid = true;
		if (cmap[psx[1] + 1][psx[0]] == '0' && cmap[psx[1] - 1][psx[0]] == '0'
			&& cmap[psx[1]][psx[0] + 1] == '1' && cmap[psx[1]][psx[0]
			- 1] == '1')
			valid = true;
		while (map->objs[++i])
		{
			if (map->objs[i]->pos.x == pos.x && map->objs[i]->pos.y == pos.y)
				valid = false;
		}
	}
	return (valid);
}
