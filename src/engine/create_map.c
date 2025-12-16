#include "cub3d.h"

void	draw_minimap(t_map *map)
{
	t_mlx	*mlx;
	t_str	addrs;

	mlx = game()->mlx;
	mlx->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img)
		return (map->destroy(map));
	addrs = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sline, &mlx->endn);
	if (!addrs)
		return (map->destroy(map));
	mlx->data = addrs;
	
}

t_map	*create_map(int level)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->level = level;
	map->map_size.x = MAP_WIDTH;
	map->map_size.y = MAP_HEIGHT;
	map->destroy = destroy_map;	
	generate_map(map);
	print_map(map);
	return (map);
}

//Implementar draw utils como pixel_put para desenhar minimap