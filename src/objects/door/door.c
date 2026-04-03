#include "cub3d.h"

t_obj	*create_door(t_map *map, t_vtr pos)
{
	t_door	*door;

	door = ft_calloc(1, sizeof(t_door));
	if (!door)
		return (NULL);
	door->pos = pos;
	map->map[(int)pos.y][(int)pos.x] = 'D';
	return ((t_obj *)door);
}
