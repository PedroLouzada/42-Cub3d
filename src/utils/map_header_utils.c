#include "cub3d.h"

char	*ft_strtrim(char *s1, char *set);
int	ft_isdigit(int c);

void	skip_spaces(char **str)
{
	while (**str && **str == ' ')
		(*str)++;
}

char	*get_path(char *str)
{
	int	len;

	str = str + 2;
	len = ft_strlen(str);
	str = ft_strtrim(str, " ");
	return (str);
}

void	open_path(char *root, char *str, int fd, int n)
{
	int	x;
	int	y;
	int	spr_fd;

	x = 0;
	y = 0;
	str = get_path(str);
	if (!str)
		parse_exit("Memory Allocation\n\n", root, fd, 0);
	spr_fd = open(str, O_RDONLY);
	if (spr_fd < 0)
		parse_exit("Texture path not valid\n", root, fd, 0);
	close(spr_fd);
	if (game()->map[0]->textures[n])
		parse_exit("Double definition on wall texture\n", root, fd, 0);
	game()->map[0]->textures[n] = new_img(str);
	if (!game()->map[0]->textures[n] || !game()->map[0]->textures[n]->img)
		parse_exit("Xpm file not valid\n", root, fd, 0);
	free(str);
}

void	check_textures(char *root, char *str, int fd)
{
	if (!ft_strncmp(str, "NO ", 3))
		open_path(root, str, fd, 0);
	else if (!ft_strncmp(str, "EA ", 3))
		open_path(root, str, fd, 1);
	else if (!ft_strncmp(str, "WE ", 3))
		open_path(root, str, fd, 2);
	else if (!ft_strncmp(str, "SO ", 3))
		open_path(root, str, fd, 3);
}

int	ft_isdigit_modified(int c)
{	if ((c >= '0' && c <= '9') || c == ',')
		return (1);
	return (0);
}

int	parse_rgb(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[++i])
	{
		if (!ft_isdigit_modified(s[i]) && !ft_isempty(s[i]))
			return (0);
		if (s[i] == ',')
			j++;
	}
	if (j != 2)
		return (0);
	return (1);
}

int	modified_atoi(char *str)
{
	int	i;
	int	n;
	char *new;

	i = -1;
	n = 0;
	new = ft_strtrim(str, " ");
	if (!new)
		return (-1);
	while (new[++i])
	{
		if (!ft_isdigit(new[i]) && (!new [i + 1] && new[i] != '\n'))
			return (-1);
	}
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n);
}

int	set_rgb(int *rgb, char *str)
{
	int i;
	int	num;
	char **values;

	i = -1;
	if (!parse_rgb(str))
		return (0);
	values = ft_split(str, ',');
	if (!values)
		return (0);
	while (values[++i])
	{
		num = modified_atoi(values[i]);
		if (num < 0)
			return (free_double(values), 0);
		rgb[i + 1] = num;
	}
	free_double(values);
	rgb[0] = 1;
	return (1);
	
}

void	check_colors(char *root, char *str, int fd, t_map *map)
{
	if (str[0] == 'C')
	{
		// if (map->colors[0][0])
		// 	parse_exit("Double ceiling \'C\' definition:\n", root, fd, 1);
		if (!set_rgb(map->colors[0], str))
			parse_exit("Wrong RGB on \'C\' definition\n", root, fd, 1);
		for(int i = 0; i < 4; i++)
			fprintf(stderr, "%d\n", map->colors[0][i]);
		// map->colors[0] = str;
	}
	// else if (str[0] == 'F')
	// {
	// 	if (map->colors[1][0])
	// 		parse_exit("Double ceiling \'F\' definition:\n", root, fd, 1);
		// map->colors[1] = str;
	// 	set_rgb();
	// }
}

int	all_done(t_map *map)
{
	int			i;
	static bool	done;

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

int	check_header(char *line, int fd)
{
	char *str;

	str = line;
	if (all_done(game()->map[0]))
		return (0);
	skip_spaces(&str);
	check_textures(line, str, fd);
	check_colors(line, str, fd, game()->map[0]);
	return (1);
}