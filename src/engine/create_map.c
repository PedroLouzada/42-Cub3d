#include "cub3d.h"

void	draw_minimap(t_map *map)
{	
	// t_vtr	data[3];
	// int		color;
	// int		scale;

	// data[0].y = -1;
	// data[1].x = WIN_WIDTH / map->map_size.x;
	// data[1].y = WIN_HEIGHT / map->map_size.y;
	// scale = ft_min(data[1].x, data[1].y);
	// while (++data[0].y < map->map_size.y)
	// {
	// 	data[0].x = -1;
	// 	while (++data[0].x < map->map_size.x)
	// 	{
	// 		color = WHITE;
	// 		if (map->map[data[0].y][data[0].x] == '1')
	// 			color = BLACK;
	// 		data[2].x = data[0].x * scale;
	// 		data[2].y = data[0].y * scale;
	// 		draw_tile(game()->mlx, data[2], scale, color);
	// 	}
	// }
	int x ,px, py;
	int y = 0;
	int color;
	
	while (y < map->map_size.y)
	{
		x = 0;
		while (x < map->map_size.x)
		{
			color = BLACK;
			if (map->map[y] && map->map[y][x] && map->map[y][x] == '1')
				color = WHITE;
			else if (map->map[y] && map->map[y][x] && map->map[y][x] != '0' && !ft_isempty(map->map[y][x]))
				color = BLUE;
			py = 0;
			while (py < 64)
			{
				px = 0;
				while (px < 64)
				{
					ft_pixel_put(game()->mlx, x * 64 + px, y * 64 + py, color);
					px++;
				}
				py++;
			}
			x++;
		}
		y++;
	}
}

t_map	*create_map(int level, int fd)
{
	t_map	*const map = ft_calloc(1, sizeof(t_map));

	if (!map)
		parse_exit("Memory Allocation\n", NULL, fd, 0);
	map->level = level;
	map->map_size.x = MAP_WIDTH;
	map->map_size.y = MAP_HEIGHT;
	map->destroy = destroy_map;
	map->minimap = draw_minimap;
	if (level)
	{
		generate_map(map);
		print_map(map);
	}
	return (map);
}
