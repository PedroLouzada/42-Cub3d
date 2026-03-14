#include "cub3d.h"

void	get_map_dimension(char *str);
void	check_characters(char *str, int fd, t_map *map);
int		check_header(char *line, int fd);
char	*ft_strdup_newline(char *s);

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isempty(line[i]) && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	check_map_content(int fd)
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
		if (check_header(line, fd) || empty_line(line))
			continue ;
		check_characters(line, fd, game()->map[0]);
		game()->map[0]->map[i] = ft_strdup_newline(line);
		if (!game()->map[0]->map[i++])
			parse_exit("Memory Allocation\n", line, fd, 1);
	}
	game()->map[0]->map[i] = NULL;
	close(fd);
}

char	**copy_map(t_map *src)
{
	int		i;
	char	**copy;

	i = -1;
	copy = ft_calloc(src->map_size.y + 1, sizeof(char *));
	if (!copy)
		parse_exit("Memory Allocation\n", NULL, -1, 1);
	while (src->map[++i])
	{
		copy[i] = ft_strdup_newline(src->map[i]);
		if (!copy[i])
		{
			free_double(copy);
			parse_exit("Memory Allocation\n", NULL, -1, 1);
		}
	}
	copy[i] = NULL;
	return (copy);
}

int	get_pos(int *pos, char **map, int entity)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	if (!entity)
		c = '0';
	else
		c = 'P';
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
			{
				pos[0] = j;
				pos[1] = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	flood_fill(char **map, int x, int y, int *pos)
{
	if (!map || !map[y] || !map[y][x] || map[y][x] == ' ' || map[y][x] == '\n')
	{
		free_double(map);
		parse_exit("Map must be closed by walls \'1\'\n", NULL, -1, 1);
	}
	if (map[y][x] == '.' || map[y][x] == '1')
		return ;
	map[y][x] = '.';
	flood_fill(map, x + 1, y, pos);
	flood_fill(map, x - 1, y, pos);
	flood_fill(map, x, y + 1, pos);
	flood_fill(map, x, y - 1, pos);
	if (get_pos(pos, map, 0))
		flood_fill(map, pos[0], pos[1], pos);
}

void	map_validation(char *str)
{
	int		fd;
	int		pos[2];
	char	**copy;

	get_map_dimension(str);
	fd = open(str, O_RDONLY);
	if (!game()->map[0]->map || fd < 0)
		parse_exit("Memory Allocation\n", NULL, fd, 0);
	check_map_content(fd);
	copy = copy_map(game()->map[0]);
	get_pos(pos, copy, 0);
	flood_fill(copy, pos[0], pos[1], pos);
	free_double(copy);
}
