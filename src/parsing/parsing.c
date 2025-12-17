#include "cub3d.h"

void	map_validation(char *str, int *d);
void	check_sintax(char *str);

void change_door(char **map, t_vtr size)
{
	int y;
	int x;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (map[y] && map[y][x] && map[y][x] == 'D')
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}

void init_doors(t_map *map, int d)
{
	map->objs = ft_calloc(d + 3, sizeof(t_obj));
	change_door(map->map, map->map_size);
}

void imprimir_char_duplo(char **strings) {
    if (strings == NULL) return;

    for (int i = 0; strings[i] != NULL; i++) {
        printf("%s\n", strings[i]);
    }
}

void	parsing(int ac, char **av)
{
	int d;
	(void)ac;
	// if (ac != 2)
	// 	parse_exit("Expected <fileName> <map.cub>\n", NULL, -1);
	check_sintax(av[1]);
	map_validation(av[1], &d);
	init_doors(game()->map[0], d);
	imprimir_char_duplo(game()->map[0]->map);
	return ;
}
