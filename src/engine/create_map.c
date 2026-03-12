#include "cub3d.h"

int	tile_color(t_map *map, t_vtr pos)
{
	int	color;

	color = BLACK;
	if (pos.y >= 0 && pos.y < map->map_size.y && pos.x >= 0
		&& pos.x < map->map_size.x)
	{
		if (map->map[(int)pos.y][(int)pos.x] == '1')
			color = WHITE;
		if (map->map[(int)pos.y][(int)pos.x] == 'E')
			color = GREEN;
	}
	return (color);
}

void	draw_characters(t_map *map)
{
	t_player	*p;
	t_vtr		pos;

	p = (t_player *)map->objs[P];
	// draw_fov(map->rays[P], map->objs[P]->pos, P);
	// draw_fov(map->rays[E], map->objs[E]->pos, E);
	// pos.x = map->objs[P]->pos.x * TILE_SZ;
	// pos.y = map->objs[P]->pos.y * TILE_SZ;
	// draw_circle(game()->mlx, pos, TILE_SZ / 2.5, BLUE);
	// pos.x = map->objs[E]->pos.x * TILE_SZ;
	// pos.y = map->objs[E]->pos.y * TILE_SZ;
	// draw_circle(game()->mlx, pos, TILE_SZ / 2.5, RED);
	pos.x = map->map_size.x / 4;
	pos.y = map->map_size.y / 4;
	draw_fov(map->rays[P], pos, P);
	pos.x *= TILE_SZ;
	pos.y *= TILE_SZ;
	draw_circle(game()->mlx, pos, TILE_SZ / 2.5, BLUE);
	pos.x = (map->map_size.x / 2) * TILE_SZ;
	pos.y = (map->map_size.y / 2) * TILE_SZ;
	draw_flashlight(pos, pos.y / 36, MINIMAP);
}

// void	draw_minimap(t_map *map)
// {
// 	t_vtr	data[2];

// 	data[0].y = -1;
// 	while (++data[0].y < map->map_size.y)
// 	{
// 		data[0].x = -1;
// 		while (++data[0].x < map->map_size.x)
// 		{
// 			data[1].x = data[0].x * TILE_SZ;
// 			data[1].y = data[0].y * TILE_SZ;
// 			draw_tile(game()->mlx, data[1], TILE_SZ, tile_color(map, data[0]));
// 		}
// 	}
// 	draw_characters(map);
// }

void	draw_minimap(t_map *map)
{
	t_vtr	data[4];

	data[0].y = -1;
	data[1].y = map->objs[P]->pos.y - (map->map_size.y / 4);
	data[2].x = (map->objs[P]->pos.x - (int)map->objs[P]->pos.x) * TILE_SZ;
	data[2].y = (map->objs[P]->pos.y - (int)map->objs[P]->pos.y) * TILE_SZ;
	while (++data[0].y < map->map_size.y / 2)
	{
		data[0].x = -1;
		data[1].x = map->objs[P]->pos.x - (map->map_size.x / 4);
		while (++data[0].x < map->map_size.x / 2)
		{
			data[3].x = data[0].x * TILE_SZ - data[2].x;
			data[3].y = data[0].y * TILE_SZ - data[2].y;
			draw_tile(game()->mlx, data[3], TILE_SZ, tile_color(map, data[1]));
			data[1].x++;
		}
		data[1].y++;
	}
	draw_characters(map);
}

void	alloc_textures(t_map *map, int level)
{
	int		i;
	bool	index;

	i = -1;
	index = 0;
	if (level % 2)
	{
		while (++i < 4)
		{
			if (!index)
			{
				map->textures[i] = new_img("./assets/textures/green_wall/wall1.xpm");
				index = !index;
			}
			else
			{
				map->textures[i] = new_img("./assets/textures/green_wall/wall2.xpm");
				index = !index;
			}
			if (!map->textures[i])
				exit_game("Memory Allocation\n");
	
			}
	}
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
	map->rays[E] = ft_calloc(WIN_WIDTH + 1, sizeof(t_ray));
	if (!map->rays[E])
		parse_exit("Memory Allocation\n", NULL, fd, 1);
	map->rays[P] = ft_calloc(WIN_WIDTH + 1, sizeof(t_ray));
	if (!map->rays[P])
		parse_exit("Memory Allocation\n", NULL, fd, 1);
	if (level)
	{
		generate_map(map);
		print_map(map);
		alloc_textures(map, level);
	}
	return (map);
}
