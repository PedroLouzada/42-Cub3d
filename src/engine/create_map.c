#include "cub3d.h"

t_map	*create_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->map_size.x = MAP_WIDTH;
	map->map_size.y = MAP_HEIGHT;
	map->destroy = destroy_map;	
	map->generate = generate_map;
	map->print = print_map;
	return (map);
}
