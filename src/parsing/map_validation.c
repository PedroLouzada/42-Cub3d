#include "cub3d.h"

void	get_map_dimention(char *str, t_map **map);
void	check_characters(char *str, int fd, t_map *map);

void	skip_spaces(char **str)
{
	while (**str && **str == ' ')
		(*str)++;
}

void	open_path(char *root, char *str, int fd, t_map *map)
{
	int	spr_fd;

	skip_spaces(&str);
	spr_fd = open(str, O_RDONLY);
	if (spr_fd < 0)
	{
		free(root);
		parse_exit("Sprite path not valid\n", (void *)map, fd);
	}
	close(spr_fd);
}

void	check_northeast(char *line, char *str, int fd, int *rose, t_map *map)
{
	if (!ft_strncmp(str, "NO ", 3))
	{
		if (rose[0])
		{
			free(line);
			parse_exit("Double definition on NO texture\n", (void *)map, fd);
		}
		open_path(line, str, fd, map);
		rose[0] = 1;
	}
	if (!ft_strncmp(str, "EA ", 3))
	{
		if (rose[1])
		{
			free(line);
			parse_exit("Double definition on EA texture\n", (void *)map, fd);
		}
		open_path(line, str, fd, map);
		rose[1] = 1;
	}
}

void	check_southwest(char *line, char *str, int fd, int *rose, t_map *map)
{
	if (!ft_strncmp(str, "WE ", 3))
	{
		if (rose[2])
		{
			free(line);
			parse_exit("Double definition on WE texture\n", (void *)map, fd);
		}
		open_path(line, str, fd, map);
		rose[2] = 1;
	}
	if (!ft_strncmp(str, "SO ", 3))
	{
		if (rose[3])
		{
			free(line);
			parse_exit("Double definition on SO texture\n", (void *)map, fd);
		}
		open_path(line, str, fd, map);
		rose[3] = 1;
	}
}

int	check_header(char *line, int fd, t_map *map)
{
	char		*str;
	int			i;
	static int	rose[4];

	if (!line)
		parse_exit("Missing texture/color information\n", (void *)map, fd);
	i = 0;
	str = line;
	skip_spaces(&str);
	check_northeast(line, str, fd, rose, map);
	check_southwest(line, str, fd, rose, map);
	while (i < 4)
	{
		if (!rose[i++])
			return (1);
	}
	return (0);
}

void	check_map_content(int fd, t_map *map)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (check_header(line, fd, map))
			continue ;
		if (!line)
			break ;
		check_characters(line, fd, map);
		free(line);
	}
}

void	map_validation(char *str, t_map *map)
{
	int	fd;

	//get_map_dimention(str, &map);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		parse_exit("Could not open the file\n", (void *)map, -1);
	check_map_content(fd, map);
}
