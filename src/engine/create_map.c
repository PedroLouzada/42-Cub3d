#include "cub3d.h"

void	draw_characters(t_map *map)
{
	t_vtr	pos;

	pos.x = (map->objs[E]->pos.x + 0.5) * TILE_SZ;
	pos.y = (map->objs[E]->pos.y + 0.5) * TILE_SZ;
	draw_circle(game()->mlx, pos, TILE_SZ / 2.5, RED);
	pos.x = (map->objs[P]->pos.x + 0.5) * TILE_SZ;
	pos.y = (map->objs[P]->pos.y + 0.5) * TILE_SZ;
	draw_circle(game()->mlx, pos, TILE_SZ / 2.5, BLUE);
}

void	draw_minimap(t_map *map)
{
	int		color;
	t_vtr	data[2];

	data[0].y = -1;
	while (++data[0].y < map->map_size.y)
	{
		data[0].x = -1;
		while (++data[0].x < map->map_size.x)
		{
			data[1].x = data[0].x * TILE_SZ;
			data[1].y = data[0].y * TILE_SZ;
			color = BLACK;
			if (map->map[(int)data[0].y][(int)data[0].x] == '1')
				color = WHITE;
			if (map->map[(int)data[0].y][(int)data[0].x] == 'E')
				color = GREEN;
			draw_tile(game()->mlx, data[1], TILE_SZ, color);
		}
	}
	draw_characters(map);
	draw_fov(map, (t_player *)map->objs[P]);
}

t_map	*create_map(int level, int fd)
{
	t_map *const map = ft_calloc(1, sizeof(t_map));
	if (!map)
		parse_exit("Memory Allocation\n", NULL, fd, 0);
	map->level = level;
	map->clean = clean_map;
	map->destroy = destroy_map;
	map->minimap = draw_minimap;
	map->map_size.x = MAP_WIDTH;
	map->map_size.y = MAP_HEIGHT;
	map->destroy = destroy_map;
	map->minimap = draw_minimap;
	map->rays = ft_calloc(WIN_WIDTH + 1, sizeof(t_ray));
	if (!map->rays)
		parse_exit("Memory Allocation\n", NULL, fd, 1);
	if (level)
	{
		generate_map(map, level);
		print_map(map);
	}
	return (map);
}
