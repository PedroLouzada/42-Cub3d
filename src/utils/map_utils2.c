#include "cub3d.h"

void	spawn(t_map *map, t_obj *obj)
{
	t_vtr	pos;

	pos = rand_pos(map->map_size);
	while (map->map[pos.y][pos.x] != '0')
		pos = rand_pos(map->map_size);
	obj->pos = pos;
}
