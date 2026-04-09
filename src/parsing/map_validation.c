/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:10:44 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 22:23:09 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_dimension(char *str);
void	check_characters(char *str, int fd, t_map *map);
int		check_header(char *line, int fd);
char	**copy_map(t_map *src);
void	flood_fill(char **map, int x, int y, int *pos);

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
	if (!get_pos(pos, copy))
	{
		free_double(copy);
		if (!game()->map[0]->map[0])
			parse_exit("Map header incomplete (missing texture or color)\n",
				NULL, -1, 1);
		parse_exit("Map must contain more than empty spaces\n", NULL, -1, 1);
	}
	flood_fill(copy, pos[0], pos[1], pos);
	free_double(copy);
}
