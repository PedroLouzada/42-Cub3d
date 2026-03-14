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
	size_t	len;

	if (!map || y < 0 || x < 0 || !map[y])
		return (false);
	len = ft_strlen(map[y]);
	if (x >= len)
		return (false);
	return (true);
}

static bool	is_floor(char c)
{
	return (c == '0' || c == 'E' || c == 'N' || c == 'W' || c == 'S'
		|| c == 'P');
}

static bool	is_wall(char c)
{
	return (c == '1' || c == 'D');
}

static bool	check_horizontal(char **map, int x, int y)
{
	if (is_wall(map[y + 1][x]) && is_wall(map[y - 1][x]) && 
		is_floor(map[y][x + 1]) && is_floor(map[y][x - 1]))
		return (true);
	return (false);
}

static bool	check_vertical(char **map, int x, int y)
{
	if (is_wall(map[y][x + 1]) && is_wall(map[y][x - 1]) && 
		is_floor(map[y + 1][x]) && is_floor(map[y - 1][x]))
		return (true);
	return (false);
}

static bool	check_hallway(char **map, int x, int y)
{
	bool	ver;
	bool	hor;

	ver = check_vertical(map, x, y);
	hor = check_horizontal(map, x, y);
	return (ver || hor);
}

bool	valid_door(t_map *map, t_vtr pos)
{
	int		i;
	t_str	*cmap;
	int		x;
	int		y;

	if (!map || !map->map || !map->objs)
		return (false);
	cmap = map->map;
	x = (int)pos.x;
	y = (int)pos.y;
	if (!in_bounds(cmap, y, x))
		return (false);
	if (!in_bounds(cmap, y, x + 2) || !in_bounds(cmap, y, x - 2)
		|| !in_bounds(cmap, y + 2, x) || !in_bounds(cmap, y - 2, x))
		return (false);
	if (cmap[y][x] != '0' || !check_hallway(cmap, x, y))
		return (false);
	i = -1;
	while (map->objs[++i])
	{
		if (map->objs[i]->pos.x == pos.x && map->objs[i]->pos.y == pos.y)
			return (false);
	}
	return (true);
}
