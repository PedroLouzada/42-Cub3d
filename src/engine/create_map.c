#include "cub3d.h"

int	tile_color(t_map *map, t_vtr pos)
{
	int	color;

	color = CLEAR;
	if (pos.y >= 0 && pos.y < map->map_size.y
	&& pos.x >= 0 && pos.x < map->map_size.x)
	{
		color = FLOOR;
		if (map->map[(int)pos.y][(int)pos.x] == '1')
			color = WALL;
		if (map->map[(int)pos.y][(int)pos.x] == 'E')
			color = GREEN;
		if (map->map[(int)pos.y][(int)pos.x] == 'D')
			color = BLUE;
	}
	return (color);
}

void	draw_characters(t_map *map)
{
	t_player	*p;
	t_enemy		*e;
	t_vtr		pos;

	p = (t_player *)map->objs[P];
	e = (t_enemy *)map->objs[E];
	pos.x = CENTER_X;
	pos.y = CENTER_Y;
	draw_fov(map, p->ray, pos);
	draw_circle(game()->mlx, pos, TILE_SZ / 3, BLUE);
	pos.x = e->pos.x - p->pos.x;
	pos.y = e->pos.y - p->pos.y;
	if (pos.x * pos.x + pos.y * pos.y <= RANGE * RANGE)
	{
		pos.x = CENTER_X + pos.x * TILE_SZ;
		pos.y = CENTER_Y + pos.y * TILE_SZ;
		draw_fov(map, e->ray, pos);
		draw_circle(game()->mlx, pos, TILE_SZ / 3, RED);
	}
}

void	draw_minimap(t_map *map)
{
	t_player	*p;
	t_vtr		pos[3];

	p = (t_player *)map->objs[P];
	pos[0].y = (int)p->pos.y - RANGE - 1;
	while (++pos[0].y < (int)p->pos.y + RANGE)
	{
		pos[0].x = (int)p->pos.x - RANGE - 1;
		while (++pos[0].x < (int)p->pos.x + RANGE)
		{
			pos[1].x = pos[0].x - p->pos.x;
			pos[1].y = pos[0].y - p->pos.y;
			pos[2].x = CENTER_X + pos[1].x * TILE_SZ;
			pos[2].y = CENTER_Y + pos[1].y * TILE_SZ;
			draw_tile(game()->mlx, pos[2], tile_color(map, pos[0]));
		}
	}
	draw_characters(map);
}

void	alloc_textures(t_map *map, int level)
{
	int		i;
	bool	index;

	i = -1;
	index = 0;
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
	map->door = new_img("./assets/textures/green_wall/door.xpm");
	if (!map->door)
		exit_game("Memory Allocation\n");
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
	if (level)
	{
		generate_map(map);
		print_map(map);
		alloc_textures(map, level);
	}
	return (map);
}
