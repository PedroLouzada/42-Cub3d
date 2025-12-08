#include "cub3d.h"

t_map	*create_map(void)
{
	t_map	*map;
	t_mlx	*mlx;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (free(map), NULL);
	map->size.x = WIDTH;
	map->size.y = HEIGHT;
	// mlx->mlx = mlx_init();
	// mlx->win = mlx_new_window(mlx->mlx, map->width, map->height, TITLE);
	// mlx->img = mlx_new_image(mlx->mlx, map->width, map->height);
	// mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sline, &mlx->endn);
	map->mlx = mlx;
	map->destroy = destroy_map;
	map->generate = generate_map;
	map->print = print_map;
	return (map);
}
