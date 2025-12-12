#include "cub3d.h"

void	map_validation(char *str, int *d, t_game *game);
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
			if (map[y][x] == 'D')
				map[y][x] == '0';
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

void printDoublePointer(int **ptr, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%d ", ptr[i][j]);  // acessa o valor no ponteiro duplo
        }
        printf("\n");
    }
}

void	parsing(t_game *game, int ac, char **av)
{
	int d;
	(void)ac;
	// if (ac != 2)
	// 	parse_exit("Expected <fileName> <map.cub>\n", NULL, -1);
	check_sintax(av[1]);
	map_validation(av[1], &d, game);
	init_doors(game->map[0], d);
	print_map(game->map[0]->map);
	return ;
}
