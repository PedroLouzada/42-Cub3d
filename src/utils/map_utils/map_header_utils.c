/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_header_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrapp-he <mrapp-he@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:11:14 by mrapp-he          #+#    #+#             */
/*   Updated: 2026/04/09 18:43:23 by mrapp-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strtrim(char *s1, char *set);
int		ft_isdigit(int c);
void	skip_spaces(char **str);
void	check_textures(char *root, char *str, int fd);
int		parse_rgb(char *s);

int	modified_atoi(char *str)
{
	int		i;
	int		n;
	int		j;
	char	*new;

	i = 0;
	n = 0;
	j = 0;
	while (str[i] == ' ' || str[i] == 'C' || str[i] == 'F')
		i++;
	new = ft_strtrim(str, " ");
	if (!new)
		return (-1);
	while (new[i + j])
	{
		if (!ft_isdigit(new[i + j]))
			return (-1);
		j++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		n = n * 10 + (str[i++] - '0');
	free(new);
	return (n);
}

int	set_rgb(int *rgb, char *str)
{
	int		i;
	int		num;
	char	**values;

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
		if (map->colors[0][0])
			parse_exit("Double ceiling \'C\' definition:\n", root, fd, 1);
		if (!set_rgb(map->colors[0], str))
			parse_exit("Wrong RGB on \'C\' definition\n", root, fd, 1);
		map->colors[0][0] = true;
	}
	else if (str[0] == 'F')
	{
		if (map->colors[1][0])
			parse_exit("Double floor \'F\' definition:\n", root, fd, 1);
		if (!set_rgb(map->colors[1], str))
			parse_exit("Wrong RGB on \'F\' definition\n", root, fd, 1);
		map->colors[1][0] = true;
	}
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
		if (!map->colors[i++][0])
			return (0);
	}
	done = 1;
	return (1);
}

int	check_header(char *line, int fd)
{
	char	*str;

	str = line;
	if (all_done(game()->map[0]))
		return (0);
	skip_spaces(&str);
	check_textures(line, str, fd);
	check_colors(line, str, fd, game()->map[0]);
	return (1);
}
