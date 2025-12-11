#include "cub3d.h"

t_map	*create_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->size.x = WIDTH;
	map->size.y = HEIGHT;
	map->destroy = destroy_map;	
	map->generate = generate_map;
	map->print = print_map;
	map->render = render_map;
	map->game = get_game_addr(NULL);
	return (map);
}
