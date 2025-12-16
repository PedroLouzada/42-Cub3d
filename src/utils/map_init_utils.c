#include "cub3d.h"

char	*ft_strtrim(char *s1, char *set);
int		is_valid_char(char c);

int	get_width(char *str)
{
	char		*new;
	int			len;
	static int	old_len;

	new = ft_strtrim(str, " ");
	if (!new)
		return (-1);
	if (!old_len)
		old_len = ft_strlen(new);
	else
	{
		len = ft_strlen(new);
		if (len > old_len)
			old_len = len;
	}
	free(new);
	return (old_len);
}

void	get_map_dimension(char *str, t_game *game)
{
	t_vtr	dim;
	int		fd;
	char	*line;

	dim.x = 0;
	dim.y = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		parse_exit("Could not open the file\n", NULL, -1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		dim.x = get_width(line);
		dim.y++;
		free(line);
	}
	game->map[0] = create_map(0);
	game->map[0]->map_size = dim;
	game->map[0]->map = calloc(game->map[0]->map_size.y, sizeof(char *));
	close(fd);
}

// void	check_border(char *str, int fd)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] != ' ' && str[i] != '1' && str[i] != '\n')
// 			parse_exit("Map must be surrounded by walls \'1\'\n", str, fd);
// 	}
// }

int	check_emptyspace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isempty(str[i]))
			return (1);
	}
	return (0);
}

void	check_characters(char *str, int fd, int *d, t_map *map)
{
	int			i;
	static int	n1;
	static int	n2;

	i = -1;
	if (!check_emptyspace(str))
	{
		n2++;
		return ;
	}
	if (!n1 || n1 + n2 == map->map_size.y - 1)
		check_border(str, fd);
	while (str[++i])
	{
		if (str[i] == 'D')
			d++;
		if (!is_valid_char(str[i]))
			parse_exit("Map must only contain the specified characters\n", str,
				fd);
	}
	n1++;
}
