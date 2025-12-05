#include "cub3d.h"

void	get_map_dimention(char *str, t_map **map);
void	check_characters(char *str, int fd, t_map *map);
int		check_header(char *line, int fd, t_map *map);

int empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isempty(line[i] && line[i] != '\n'))
			return (0);
		i++;
	}
	return (1);
}

void	check_map_content(int fd, t_map *map)
{
	char	*line;

	line = NULL;
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		if (check_header(line, fd, map) || empty_line(line))
			continue ;
		check_characters(line, fd, map);
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
