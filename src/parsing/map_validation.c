#include "cub3d.h"

void	get_map_dimension(char *str, t_game *game);
void	check_characters(char *str, int fd, int d, t_map *map);
int		check_header(char *line, int fd, t_game *game);
char	*ft_strdup_newline(char *s);

// int	empty_line(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (!ft_isempty(line[i]) && line[i] != '\n')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

void	check_map_content(int fd, int *d, t_game *game)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (check_header(line, fd, game) || empty_line(line))
			continue ;
		check_characters(line, fd, d, game->map[0]);
		game->map[0]->map[i++] = ft_strdup_newline(line);
	}
	game->map[0]->map[i] = NULL;
	close(fd);
}

// void	print_map_copy(char **arr)
// {
// 	for (int i = 0; arr[i] != NULL; i++)
// 	{
// 		printf("%s\n", arr[i]);
// 	}
// }

	i = -1;
	copy = ft_calloc(src->map_size.y + 1, sizeof(char *));
	if (!copy)
		parse_exit("Memory allocation\n", NULL, -1);
	while (src->map[++i])
		copy[i] = ft_strdup_newline(src->map[i]);
	copy[i] = NULL;
	return (copy);
}

// 	i = -1;
// 	copy = ft_calloc(src->map_size.y + 1, sizeof(char *));
// 	if (!copy)
// 		parse_exit("Memory allocation\n", NULL, -1);
// 	while (src->map[++i])
// 		copy[i] = ft_strdup_newline(src->map[i]);
// 	copy[i] = NULL;
// 	return (copy);
// }

// int	get_pos(int *pos, char **map)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			if (map[i][j] == '0')
// 			{
// 				pos[0] = j;
// 				pos[1] = i;
// 				return (1);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

void	map_validation(char *str, int *d, t_game *game)
{
	int		fd;
	int		pos[2];
	char	**copy;

	get_map_dimension(str, game);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		parse_exit("Could not open the file\n", NULL, -1);
	check_map_content(fd, d, game);
	copy = copy_map(game->map[0]);
	get_pos(pos, copy);
	flood_fill(copy, pos[0], pos[1], pos);
	free_double(copy);
}

// 	get_map_dimention(str, game);
// 	fd = open(str, O_RDONLY);
// 	if (fd == -1)
// 		parse_exit("Could not open the file\n", NULL, -1);
// 	check_map_content(fd, game);
// 	copy = copy_map(game->map[0]);
// 	get_pos(pos, copy);
// 	flood_fill(copy, pos[0], pos[1], pos);
// 	//print_map_copy(copy);
// 	free_double(copy);
// }
