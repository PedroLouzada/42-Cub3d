#include "cub3d.h"

void	destroy_map(t_map *map, int level)
{
	int	i;

	i = -1;
	while (++i < map->map_size.y)
		free(map->minimap[level][i]);
	free(map->minimap[level]);
	// free(map);
}
