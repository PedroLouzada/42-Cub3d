/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:11:17 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 18:49:18 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	get_map_dimension(char *str)
{
	int				fd;
	char			*line;
	static t_vtr	dim;

	dim.y = 0;
	fd = open(str, O_RDONLY);
	if (fd < 0)
		parse_exit("Could not open the file\n", NULL, -1, 0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		dim.x = get_width(line);
		if (dim.x == -1)
			parse_exit("Memory Allocation\n", line, fd, 0);
		dim.y++;
		free(line);
	}
	if (!dim.y)
		parse_exit("Map should have more than 1 line\n", NULL, fd, 0);
	(game()->map)[0] = create_map(0, fd);
	(game()->map[0])->map_size = dim;
	(game()->map[0])->map = ft_calloc(dim.y + 1, sizeof(char *));
	close(fd);
}

void	check_border(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '\n')
			parse_exit("Map must be surrounded by walls \'1\'\n", str, fd, 1);
	}
}

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

void	check_characters(char *str, int fd, t_map *map)
{
	int			i;
	static int	n1;
	static int	n2;
	static bool	flag;

	i = -1;
	if (!check_emptyspace(str))
		return ((void)n2++);
	if (!n1 || n1 + n2 == map->map_size.y - 1)
		check_border(str, fd);
	while (str[++i])
	{
		if (!is_valid_char(str[i]))
			parse_exit("Map must contain the specified chars\n", str, fd, 1);
		if (str[i] == 'N' || str[i] == 'E' || str[i] == 'W' || str[i] == 'S')
		{
			if (flag)
				parse_exit("Should only contain one player\n", str, fd, 1);
			game()->map[0]->direction = str[i];
			str[i] = 'P';
			flag = true;
		}
	}
	n1++;
}
