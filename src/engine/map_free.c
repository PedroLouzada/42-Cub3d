#include "cub3d.h"

void	destroy_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->map_size.y)
	{
		if (map->map[i])
			free(map->map[i]);
	}
	if (map->map)
		free(map->map);
	i = -1;
	while (map->objs[++i])
		free(map->objs[i]);
	if (map->objs)
		free(map->objs);
	if (map)	
		free(map);
}

void	clean_map(t_map *map)
{
	int	i;

	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
}
