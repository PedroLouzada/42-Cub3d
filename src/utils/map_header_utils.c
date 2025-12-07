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

void	open_path(char *root, char *str, int fd, int n, t_map *map)
{
	int	x;
	int	y;
	int	spr_fd;

	x = 0;
	y = 0;
	str = get_path(str);
	spr_fd = open(str, O_RDONLY);
	if (spr_fd < 0)
		parse_exit("Sprite path not valid\n", root, fd);
	close(spr_fd);
	if (map->wall_spr[n])
		parse_exit("Double definition on wall texture\n", root, fd);
	map->wall_spr[n] = mlx_xpm_file_to_image(map->game->mlx, str, &x, &y);
	if (!map->wall_spr[n])
		parse_exit("Xpm file not valid\n", root, fd);
}

void	check_textures(char *root, char *str, int fd, t_map *map)
{
	if (!ft_strncmp(str, "NO ", 3))
		open_path(root, str, fd, 0, map);
	else if (!ft_strncmp(str, "EA ", 3))
		open_path(root, str, fd, 1, map);
	else if (!ft_strncmp(str, "WE ", 3))
		open_path(root, str, fd, 2, map);
	else if (!ft_strncmp(str, "SO ", 3))
		open_path(root, str, fd, 3, map);
}

void	check_colors(char *root, char *str, int fd, t_map *map)
{
	if (str[0] == 'C')
	{
		if (map->color[0])
			parse_exit("Double ceiling \'C\' definition:\n", root, fd);
		map->color[0] = str;
	}
	else if (str[0] == 'F')
	{
		if (map->color[1])
			parse_exit("Double ceiling \'F\' definition:\n", root, fd);
		map->color[1] = str;
	}
}

int	all_done(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!map->wall_spr[i++])
			return (0);
	}
	i = 0;
	while (i < 2)
	{
		if (!map->color[i++])
			return (0);
	}
	fprintf(stderr, "Passa aqui\n");
	return (1);
}

int	check_header(char *line, int fd, t_map *map)
{
	char *str;
	int i;

	i = 0;
	str = line;
	if (all_done(map))
		return (1);
	skip_spaces(&str);
	check_textures(line, str, fd, map);
	check_colors(line, str, fd, map);
	return (0);
}