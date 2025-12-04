#include "cub3d.h"

void	get_map_dimention(char *str, t_map **map);
void	check_characters(char *str, int fd, t_map *map);
int		check_header(char *line, int fd, t_map *map);

void	check_map_content(int fd, t_map *map)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (check_header(line, fd, map))
			continue ;
		check_characters(line, fd, map);
		free(line);
	}
}

void	map_validation(char *str, t_map *map)
{
	int	fd;

	get_map_dimention(str, &map);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		parse_exit("Could not open the file\n", (void *)map, -1);
	check_map_content(fd, map);
}
