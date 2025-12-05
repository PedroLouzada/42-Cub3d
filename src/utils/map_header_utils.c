#include "cub3d.h"

void	skip_spaces(char **str)
{
	while (**str && **str == ' ')
		(*str)++;
}

char	*get_path(char *str)
{
	int	len;

	str = str + 2;
	skip_spaces(&str);
	len = ft_strlen(str);
	str[len - 1] = 0;
	return (str);
}

void	open_path(char *root, char *str, int fd, t_map *map)
{
	int	spr_fd;

	str = get_path(str);
	spr_fd = open(str, O_RDONLY);
	if (spr_fd < 0)
	{
		free(root);
		parse_exit("Sprite path not valid\n", (void *)map, fd);
	}
	close(spr_fd);
}

void	check_northeast(char *root, char *str, int fd, int *rose, t_map *map)
{
	if (!ft_strncmp(str, "NO ", 3))
	{
		if (rose[0])
		{
			free(root);
			parse_exit("Double definition on NO texture\n", (void *)map, fd);
		}
		open_path(root, str, fd, map);
		rose[0] = 1;
	}
	if (!ft_strncmp(str, "EA ", 3))
	{
		if (rose[1])
		{
			free(root);
			parse_exit("Double definition on EA texture\n", (void *)map, fd);
		}
		open_path(root, str, fd, map);
		rose[1] = 1;
	}
}

void	check_southwest(char *root, char *str, int fd, int *rose, t_map *map)
{
	if (!ft_strncmp(str, "WE ", 3))
	{
		if (rose[2])
		{
			free(root);
			parse_exit("Double definition on WE texture\n", (void *)map, fd);
		}
		open_path(root, str, fd, map);
		rose[2] = 1;
	}
	if (!ft_strncmp(str, "SO ", 3))
	{
		if (rose[3])
		{
			free(root);
			parse_exit("Double definition on SO texture\n", (void *)map, fd);
		}
		open_path(root, str, fd, map);
		rose[3] = 1;
	}
}

void	check_colors(char *root, char *str, int fd, int *colors, t_map *map)
{
	if (str[0] == 'C')
	{
		if (colors[0])
		{
			free(root);
			parse_exit("Double ceiling \'C\' definition:\n", (void *)map, fd);
		}
		colors[0] = 1;
	}
	if (str[0] == 'F')
	{
		if (colors[1])
		{
			free(root);
			parse_exit("Double floor \'F\' definition\n", (void *)map, fd);
		}
		colors[1] = 1;
	}
}

int	all_done(int *rose, int *colors)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!rose[i++])
			return (0);
	}
	i = 0;
	while (i < 2)
	{
		if (!colors[i++])
			return (0);
	}
	fprintf(stderr, "Passa aqui\n");
	return (1);
}

int	check_header(char *line, int fd, t_map *map)
{
	char *str;
	int i;
	static int rose[4];
	static int colors[2];

	i = 0;
	str = line;
	if (all_done(rose, colors))
		return (1);
	skip_spaces(&str);
	check_northeast(line, str, fd, rose, map);
	check_southwest(line, str, fd, rose, map);
	check_colors(line, str, fd, colors, map);
	return (0);
}