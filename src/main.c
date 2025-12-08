#include "cub3d.h"

int	main(void)
{
	t_map *map = create_map();

	init_rand();
	map->generate(map);
	map->print(map);
	map->destroy(map);
	return (0);
}
