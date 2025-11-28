#include "cub3d.h"

char	*ft_strtrim(char *s1, char *set);

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

void	get_map_dimention(char *str, t_map **map)
{
	int		width;
	int		height;
	int		fd;
	char	*line;

	width = 0;
	height = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		parse_exit("Could not open the file\n", NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		width = get_width(line);
		height++;
		free(line);
	}
	*map = calloc(1, sizeof(t_map));
	(*map)->width = width;
	(*map)->height = height;
	close(fd);
}

char	get_first_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isempty(str[i]))
			break ;
		i++;
	}
	return (str[i]);
}

char	get_last_char(char *str)
{
	int		i;
	char	*tail;

	i = 0;
	tail = ft_strrchr(str, '1');
	while (tail[i++])
	{
		if (!ft_isempty(tail[i]))
			return (tail[i]);
	}
	return (*tail);
}

void	check_line_border(char *str, int fd, t_map *map)
{
	int		i;
	bool	fail;
	char	first_chr;
	char	last_chr;

	i = -1;
	fail = false;
	while (str[++i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != ' ')
		{
			fail = true;
			break ;
		}
	}
	first_chr = get_first_char(str);
	last_chr = get_last_char(str);
	if (first_chr != '1' || last_chr != '1')
		fail = true;
	if (fail)
	{
		close(fd);
		free(map);
		parse_exit("Map must be surrounded by walls \'1\'\n", (void *)str);
	}
}
