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

void	open_path(char *root, char *str, int fd, int n, t_game *game)
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
	if (game->map[0]->textures[n])
		parse_exit("Double definition on wall texture\n", root, fd);
	game->map[0]->textures[n] = mlx_xpm_file_to_image(game->mlx->mlx, str, &x, &y);
	if (!game->map[0]->textures[n])
		parse_exit("Xpm file not valid\n", root, fd);
}

void	check_textures(char *root, char *str, int fd, t_game *game)
{
	if (!ft_strncmp(str, "NO ", 3))
		open_path(root, str, fd, 0, game);
	else if (!ft_strncmp(str, "EA ", 3))
		open_path(root, str, fd, 1, game);
	else if (!ft_strncmp(str, "WE ", 3))
		open_path(root, str, fd, 2, game);
	else if (!ft_strncmp(str, "SO ", 3))
		open_path(root, str, fd, 3, game);
}

void	check_colors(char *root, char *str, int fd, t_map *map)
{
	if (str[0] == 'C')
	{
		if (map->colors[0])
			parse_exit("Double ceiling \'C\' definition:\n", root, fd);
		map->colors[0] = str;
	}
	else if (str[0] == 'F')
	{
		if (map->colors[1])
			parse_exit("Double ceiling \'F\' definition:\n", root, fd);
		map->colors[1] = str;
	}
}

int	all_done(t_map *map)
{
	int	i;
	static bool done;

	if (done)
		return (1);
	i = 0;
	while (i < 4)
	{
		if (!map->textures[i++])
			return (0);
	}
	i = 0;
	while (i < 2)
	{
		if (!map->colors[i++])
			return (0);
	}
	done = 1;
	return (1);
}

int	check_header(char *line, int fd, t_game *game)
{
	char *str;

	str = line;
	if (all_done(game->map[0]))
		return (0);
	skip_spaces(&str);
	check_textures(line, str, fd, game);
	check_colors(line, str, fd, game->map[0]);
	return (1);
}