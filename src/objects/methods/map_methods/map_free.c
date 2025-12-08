#include "cub3d.h"

void	destroy_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->size.y)
		free(map->map[i]);
	free(map->map);
}
